import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    user = db.execute(
        "SELECT username FROM users WHERE id = ?", (user_id,))
    if not user:
        return apology("USER NOT FOUND")

    username = user[0]["username"]

    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) as shares, price FROM purchases WHERE username = ? GROUP BY symbol", username)
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = round(cash_db[0]["cash"], 2)

    return render_template("index.html", database=transactions_db, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("MISSING SYMBOL")

        if not shares:
            return apology("MISSING SHARES")

        try:
            shares = int(shares)
        except ValueError:
            return apology("INVALID SHARES")

        if shares < 1:
            return apology("INVALID SHARES NUMBER")

        stock = lookup(symbol.upper())

        if stock is None:
            return apology("INVALID SYMBOL")

        user_id = session["user_id"]

        user = db.execute(
            "SELECT username FROM users WHERE id = ?", (user_id,))
        if not user:
            return apology("USER NOT FOUND")

        username = user[0]["username"]

        transaction_value = shares * stock["price"]

        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < transaction_value:
            return apology("Not Enough Cash to complete transaction")
        uptd_cash = user_cash - transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   uptd_cash, user_id)
        db.execute("INSERT INTO purchases (username, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   username, stock["symbol"], shares, stock["price"])

        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    user = db.execute(
        "SELECT username FROM users WHERE id = ?", (user_id,))
    if not user:
        return apology("USER NOT FOUND")

    username = user[0]["username"]

    transactions_db = db.execute(
        "SELECT * FROM purchases WHERE username = ?", username)
    print(transactions_db)
    return render_template("history.html", purchases=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("MISSING SYMBOL")

        response = lookup(symbol)
        if response is None:
            return apology("INVALID SYMBOL")
        price = usd(response['price'])
        return render_template("quoted.html", symbol=response['symbol'], price=price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm your password", 400)

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if password != confirmation:
            return apology("password doesn't match", 400)

        hash = generate_password_hash(
            password, method='pbkdf2:sha256', salt_length=16)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check if username already exists
        if len(rows) > 0:
            return apology("username already exists", 400)

        # Insert the new user into the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]

        user = db.execute(
            "SELECT username FROM users WHERE id = ?", (user_id,))
        if not user:
            return apology("USER NOT FOUND")

        username = user[0]["username"]
        symbols_user = db.execute(
            "SELECT symbol FROM purchases WHERE username = ? GROUP BY symbol HAVING SUM(shares) > 0", username)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Must Give Symbol")

        if not shares:
            return apology("Must Give Shares")

        try:
            shares = int(shares)
        except ValueError:
            return apology("Invalid Share Count")

        if shares < 1:
            return apology("Negative Shares Not Allowed")

        stock = lookup(symbol.upper())
        if stock is None:
            return apology("Symbol Does Not Exist")

        user_id = session["user_id"]
        user = db.execute(
            "SELECT username FROM users WHERE id = ?", (user_id,))
        if not user:
            return apology("USER NOT FOUND")

        username = user[0]["username"]

        user_shares = db.execute(
            "SELECT SUM(shares) as total_shares FROM purchases WHERE username = ? AND symbol = ?", username, symbol)
        if user_shares[0]["total_shares"] is None:
            user_shares[0]["total_shares"] = 0

        if shares > user_shares[0]["total_shares"]:
            return apology("You Do Not Have Enough Shares")

        transaction_value = shares * stock["price"]
        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]
        uptd_cash = user_cash + transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   uptd_cash, user_id)
        db.execute("INSERT INTO purchases (username, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   username, stock["symbol"], -shares, stock["price"])

        flash("Sold!")
        return redirect("/")
