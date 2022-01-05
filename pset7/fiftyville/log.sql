-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Analise the description of the crime to gather some clues about who is can be
-- the thief and what were his nexts steps.
SELECT description FROM crime_scene_reports
WHERE (year = 2020 AND day = 28 AND month = 7) AND street = "Chamberlin Street";

/*
    Description:

    Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
    Interviews were conducted today with three witnesses who were present at
    the time — each of their interview transcripts mentions the courthouse.
*/

-- Try to get information about the crime from the witnesses interviews.
SELECT name, id, transcript FROM interviews
WHERE (year = 2020 AND day = 28 AND month = 7) AND transcript LIKE "%courthouse%";

/*
    Name: Ruth
    id: 161
    Transcript: Sometime within ten minutes of the theft, I saw the thief get
                into a car in the courthouse parking lot and drive away.
                If you have security footage from the courthouse parking
                lot, you might want to look for cars that left the parking
                lot in that time frame.

    Name: Eugene
    id: 162
    Transcript: I don't know the thief's name, but it was someone I recognized.
                Earlier this morning, before I arrived at the courthouse,
                I was walking by the ATM on Fifer Street and saw the thief
                there withdrawing some money.

    Name: Raymond
    id: 163
    Transcript: As the thief was leaving the courthouse, they called someone
                who talked to them for less than a minute. In the call,
                I heard the thief say that they were planning to take the
                earliest flight out of Fiftyville tomorrow. The thief then
                asked the person on the other end of the phone to purchase
                the flight ticket.
*/

-- Based on the Ruth interview, analise the security log of the courthouse
-- to note the cars that left the place around 10 minutes after the crime.
SELECT people.name, people.license_plate, courthouse_security_logs.activity
FROM courthouse_security_logs
JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE
(
courthouse_security_logs.year = 2020
AND courthouse_security_logs.day = 28
AND courthouse_security_logs.month = 7
AND courthouse_security_logs.hour = 10
AND courthouse_security_logs.minute <= 25
);

/*
    name        | license_plate | activity
    Brandon     | R3G7486       | entrance
    Sophia      | 13FNH73       | entrance
    Patrick     | 5P2BI95       | exit
    Ernest      | 94KL13X       | exit
    Amber       | 6P58WS2       | exit
    Danielle    | 4328GD8       | exit
    Roger       | G412CB7       | exit
    Elizabeth   | L93JTIZ       | exit
    Russell     | 322W7JE       | exit
    Evelyn      | 0NTHK55       | exit
*/

-- Based on the Eugene interview, analise the ATM withdraws on Fifer Street
-- that were done in the the same day of the crime.
SELECT people.name, bank_accounts.account_number, atm_transactions.amount
FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE (year = 2020 AND day = 28 AND month = 7) AND atm_location = "Fifer Street" AND transaction_type = "withdraw";

/*
    Ernest      | 49610011 | 50
    Russell     | 26013199 | 35
    Roy         | 16153065 | 80
    Bobby       | 28296815 | 20
    Elizabeth   | 25506511 | 20
    Danielle    | 28500762 | 48
    Madison     | 76054385 | 60
    Victoria    | 81061156 | 30
*/

-- Based on the Raymond interview, analise the people data of the persons that
-- made short phone calls and leave out the courthouse in the morning of the day
-- that the crime happened
SELECT people.name, people.phone_number, people.passport_number, people.license_plate
FROM people JOIN phone_calls ON (people.phone_number = phone_calls.caller)
WHERE (phone_calls.year = 2020 AND phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration <= 60)
AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE (year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute <= 25));

/*
    name    | phone_number      | passport_number   | license_plate
    Roger   | (130) 555-0289    | 1695452385        | G412CB7
    Evelyn  | (499) 555-9472    | 8294398571        | 0NTHK55
    Ernest  | (367) 555-5533    | 5773159633        | 94KL13X
    Evelyn  | (499) 555-9472    | 8294398571        | 0NTHK55
    Russell | (770) 555-1861    | 3592750733        | 322W7JE
*/

-- Search for the person name that match the last three querys
SELECT DISTINCT people.name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE people.name IN
(
SELECT people.name
FROM people JOIN phone_calls ON (people.phone_number = phone_calls.caller)
WHERE (phone_calls.year = 2020 AND phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration <= 60)
AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE (year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute <= 25))
)
AND bank_accounts.account_number IN
(
SELECT account_number
FROM atm_transactions
WHERE (year = 2020 AND day = 28 AND month = 7) AND atm_location = "Fifer Street" AND transaction_type = "withdraw"
);

/*
    Names: Ernest and Russell
*/

-- Find the destination of Ernest and Russell.
SELECT people.name, airports.city, flights.hour FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE people.name = "Ernest" OR people.name = "Russell"
AND (flights.year = 2020 AND flights.day = 29 AND month = 7)
AND flights.origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY flights.hour;

/*
    name    | city      | hour
    Ernest  | London    | 8
    Russell | Boston    | 16

    The thief therefore is Ernest, since he took the earliest flight from Fiftyville,
    and he is going to London.
*/

-- Find the name of the accomplice from the receiver of the phonecall Ernest did after the crime.
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller IN (SELECT phone_number FROM people WHERE name = "Ernest")
AND (phone_calls.year = 2020 AND phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration <= 60);

/*
    The accomplice is therefore Berthold.
*/
