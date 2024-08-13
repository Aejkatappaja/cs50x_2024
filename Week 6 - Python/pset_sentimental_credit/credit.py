
from cs50 import get_string, get_int

AMEX = "AMEX"
MASTERCARD = "MASTERCARD"
VISA = "VISA"
INVALID = "INVALID"

cards_types = {
    "amex": "AMEX",
    "mastercard": "MASTERCARD",
    "visa": "VISA",
    "invalid": "INVALID"
}


def main():
    credit_card_input = get_int("Number: ")
    credit_card_length = len(str(credit_card_input))
    check = luhn_check(credit_card_input)
    get_credit_card_type(credit_card_length, credit_card_input, check)


def get_credit_card_type(len, input, check):
    if check:
        prefix = int(str(input)[:2])
        card = ""
        if len == 15 and (prefix == 34 or prefix == 37):
            card = "amex"
        elif len == 16 and (prefix >= 51 and prefix <= 55):
            card = "mastercard"
        elif (len == 13 or len == 16) and ((prefix // 10) == 4):
            card = "visa"
        else:
            card = "invalid"

    else:
        card = "invalid"
    print(cards_types[card])


def luhn_check(input):
    sum = 0
    alternate = False

    while input > 0:
        digit = input % 10
        if alternate:
            digit *= 2
            if digit > 9:
                digit -= 9

        sum += digit
        input //= 10
        alternate = not alternate
    return (sum % 10) == 0


if __name__ == "__main__":
    main()
