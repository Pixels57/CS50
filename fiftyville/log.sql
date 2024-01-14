-- Keep a log of any SQL queries you execute as you solve the mystery.
-- to get crime scene reports
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street";

-- to get witnesses' interviews
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- to get potential license plates
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28;

-- to get potenial atm transactions and account numbers
SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- to get potential phone calls by the thief
SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;

-- to get potential suspects
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    )
INTERSECT
SELECT name FROM people WHERE
id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"
        )
    )
INTERSECT
SELECT name FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE
    day = 28
    AND month = 7
    AND year = 2021
    AND duration < 60
    );

-- to get potetnial aiders
SELECT name FROM people WHERE
phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE name IN (
            SELECT name FROM people WHERE
            license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE
                year = 2021
                AND month = 7
                AND day = 28
                )
            INTERSECT
            SELECT name FROM people
            WHERE id IN (
                SELECT person_id FROM bank_accounts
                WHERE account_number IN (
                    SELECT account_number FROM atm_transactions WHERE
                    day = 28
                    AND month = 7
                    AND year = 2021
                    AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
                    )
                )
            INTERSECT
            SELECT name FROM people WHERE
            phone_number IN (
                SELECT caller FROM phone_calls WHERE
                day = 28
                AND month = 7
                AND year = 2021
                AND duration < 60
                )
            )
        )
        AND year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60
    );

-- to get potential flight
SELECT * FROM flights
WHERE id IN (
    SELECT flight_id FROM passengers
    WHERE passport_number IN (
        SELECT passport_number FROM people
        WHERE name IN (
            SELECT name FROM people
            WHERE license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                )
            INTERSECT
            SELECT name FROM people WHERE
            id IN (
                SELECT person_id FROM bank_accounts
                WHERE account_number IN (
                    SELECT account_number FROM atm_transactions WHERE
                    day = 28
                    AND month = 7
                    AND year = 2021
                    AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
                    )
                )
            INTERSECT
            SELECT name FROM people
            WHERE phone_number IN (
                SELECT caller FROM phone_calls WHERE
                day = 28 AND
                month = 7
                AND year = 2021
                AND duration < 60
                )
            )
        )
    )
;