# Flight Reservation System (FRS) by Sabarigirish Manikandan (2410110283), and Ishaan Prakash (2410110429)
Flight Reservation System made in C that uses JSON to write and retrieve flight and booking records.

## Problem Statement
A Flight Reservation System (HMS) is a real-time problem of a person relatable getting the
tension to book the flight tickets at the cheapest price to book tickets for their journey.
Your task is to write a C application that:
1. Store the Flight Details: such as Flight name, from where to where its flying, no. of
seats etc.
2. Book the flight ticket:
3. Cancel the flight ticket
4. Update the passenger information on Booking (such as name, age, phone number, etc)
5. View the passengers that are travelling in the flight

## Build
`gcc main.c ./lib/structs.c ./lib/utils.c ./lib/cJSON.c -o main`

## Run
`./main`

## Credits
- David Gamble for cJSON, a JSON parser for C
