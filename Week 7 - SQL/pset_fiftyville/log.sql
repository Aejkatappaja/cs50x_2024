-- -- Keep a log of any SQL queries you execute as you solve the mystery.

-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Looking for a crime scene report that matches the date and the location of the crime
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2023
AND street = 'Humphrey Street';

-- Checking Their Interview Transcripts
SELECT transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2023

-- Look through security footage to look for cars that left parking
SELECT *
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND hour = 10
AND minute BETWEEN 15 AND 25;

-- Find the Names of the people with the same License Plate
SELECT p.name from people p
JOIN bakery_security_logs ON p.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND bakery_security_logs.year = 2023
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 15 AND 25;
                                                              |
-- Find All withdraws from the specific ATM referenced in 2nd Witness Transcript
SELECT * FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';

-- Finds the Name of the people associated with the ATM account Number
SELECT people.name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';
                                                                                             |
-- Check Phone Calls
SELECT caller FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration <= 60;

-- Find the Names of the Callers
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2023
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60;

-- Flights From Airport in Fiftyville
SELECT * FROM airports
WHERE city = 'Fiftyville';

-- Find Earliest Flight That Day
SELECT * FROM flights
WHERE origin_airport_id = 8
AND flights.year = 2023
AND flights.month = 7
AND flights.day = 29;

-- Find Passenger Names for the flight
SELECT people.name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.year = 2023
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20;

-- Find Flight Arrival Location
SELECT airports.city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = 8
AND flights.year = 2023
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20;

-- Find Phone of Bruce
SELECT phone_number FROM people
WHERE name = 'Bruce';

-- Check the Phone Call of Bruce to find other suspect
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2023
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
AND phone_calls.caller = '(367) 555-5533';
