#include "lib/structs.h"
#include "lib/utils.h"
#include <stdio.h>
#include <stdlib.h>

#define BOOKINGS_LOCATION "./bookings.json"
#define FLIGHTS_LOCATION "./flights.json"

int main() {
    int numberOfFlights, numberOfBookings;
    Flight *flights = readFlights(FLIGHTS_LOCATION, &numberOfFlights);
    Booking *bookings = readBookings(BOOKINGS_LOCATION, &numberOfBookings);
    printf("\nWelcome to the Flight Reservation System (FRS).\n");
    int choice;
    while (1) {
        printf(
            "Please select your mode: -\n\t1. Flight Management\n\t2. Booking "
            "Management\n\t3. Save\n\t4. Save and Quit\n\t5. Quit without "
            "Saving\n: ");
        scanf("%d", &choice);
        int id;
        if (choice == 1) {
            printf(
                "\nPlease select an operation: -\n\t1. Create a new flight "
                "entry\n\t2. "
                "Delete an existing flight entry (by flight ID)\n\t3. Modify "
                "an "
                "existing flight entry (by flight ID)\n\t4. List all bookings "
                "under a flight (by flight ID)\n\t5. List all flight "
                "entries\n\t6. Return to main menu\n: ");
            scanf("%d", &choice);
            Flight buffer;
            switch (choice) {
            case 1:
                printf(
                    "Enter your flight's availability for booking (0 or 1): ");
                scanf("%d", &buffer.available);
                printf("Enter your flight's name (50 characters or under): ");
                scanf(" %[^\n]s", buffer.name);
                printf("Enter number of seats: ");
                scanf("%d", &buffer.seats);
                buffer.freeSeats = buffer.seats;
                printf("Enter flight source (3 characters): ");
                scanf(" %[^\n]s", buffer.source);
                printf("Enter flight destination (3 characters): ");
                scanf(" %[^\n]s", buffer.destination);
                appendFlight(&flights, &numberOfFlights, buffer);
                printf("Your flight ID is: %d\n\n", numberOfFlights - 1);
                break;
            case 2:
                printf("Enter flight ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid flight ID.\n");
                    break;
                }
                if (id >= numberOfFlights) {
                    printf("Could not find flight with flight ID %d.", id);
                    break;
                }
                printf("Flight availability: %s\nFlight name: %s\nTotal Seats: "
                       "%d\nFree seats: %d\nSource: %s\nDestination: %s\n",
                       (flights[id].available) ? "Yes" : "No", flights[id].name,
                       flights[id].seats, flights[id].freeSeats,
                       flights[id].source, flights[id].destination);
                printf("Are you sure you want to delete this flight (this will "
                       "delete "
                       "all bookings on the flight)? (0 or 1): ");
                scanf("%d", &choice);
                if (choice) {
                    deleteFlight(&flights, &numberOfFlights, id);
                    for (int i = 0; i < numberOfBookings; i++) {
                        if (bookings[i].flightId == id) {
                            deleteBooking(&bookings, &numberOfBookings, i);
                            i--;
                        }
                    }
                    printf("Deleted flight and corresponding bookings.\n");
                } else if (choice != 0)
                    printf("Invalid input.\n");
                break;
            case 3:
                printf("\nEnter flight ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid flight ID.\n");
                    break;
                }
                if (id >= numberOfFlights) {
                    printf("Could not find flight with flight ID %d.", id);
                    break;
                }
                printf(
                    "\nFlight availability: %s\nFlight name: %s\nTotal Seats: "
                    "%d\nFree seats: %d\nSource: %s\nDestination: %s\n",
                    (flights[id].available) ? "Yes" : "No", flights[id].name,
                    flights[id].seats, flights[id].freeSeats,
                    flights[id].source, flights[id].destination);
                printf("Do you wish to change everything or modify individual "
                       "fields? "
                       "(0 or 1): ");
                scanf("%d", &choice);
                if (!choice) {
                    printf(
                        "\nEnter your flight's availability for booking (0 or "
                        "1): ");
                    scanf("%d", &flights[id].available);
                    printf(
                        "Enter your flight's name (50 characters or under): ");
                    scanf(" %[^\n]s", flights[id].name);
                    printf("Enter number of seats: ");
                    scanf("%d", &flights[id].seats);
                    printf("Enter number of available seats: ");
                    scanf("%d", &flights[id].freeSeats);
                    printf("Enter flight source (3 characters): ");
                    scanf(" %[^\n]s", flights[id].source);
                    printf("Enter flight destination (3 characters): ");
                    scanf(" %[^\n]s", flights[id].destination);
                } else if (choice == 1) {
                    printf("\nWhich parameter would you like to change?");
                    printf(
                        "\n\t1. Flight availability\n\t2. Flight name\n\t3. "
                        "Total Seats"
                        "\n\t4. Free seats\n\t5. Source\n\t6. Destination\n: ");
                    scanf("%d", &choice);
                    switch (choice) {
                    case 1:
                        printf("Enter your flight's availability for booking "
                               "(0 or 1): ");
                        scanf("%d", &(flights[id].available));
                        break;
                    case 2:
                        printf("Enter your flight's name (50 characters or "
                               "under): ");
                        scanf(" %[^\n]s", flights[id].name);
                        break;
                    case 3:
                        printf("Enter number of seats: ");
                        scanf("%d", &(flights[id].seats));
                        break;
                    case 4:
                        printf("Enter number of available seats: ");
                        scanf("%d", &(flights[id].freeSeats));
                        break;
                    case 5:
                        printf("Enter flight source (3 characters): ");
                        scanf(" %[^\n]s", flights[id].source);
                        break;
                    case 6:
                        printf("Enter flight destination (3 characters): ");
                        scanf(" %[^\n]s", flights[id].destination);
                        break;
                    default:
                        printf("Invalid input.\n");
                        break;
                    }
                    printf("Modification complete.\n");
                } else
                    printf("Invalid input.\n");
                break;
            case 4:
                printf("Enter flight ID: ");
                scanf("%d", &choice);
                printf("\n");
                int n = 0;
                for (int i = 0; i < numberOfBookings; i++)
                    if (bookings[i].flightId == choice) {
                        printf("Passenger Name: %s\nFlight ID: %d\nNumber of "
                               "Seats: "
                               "%d\nAge: %d\nPhone Number: %d\nSource: "
                               "%s\nDestination: %s\n",
                               bookings[i].passengerName, bookings[i].flightId,
                               bookings[i].seats, bookings[i].age,
                               bookings[i].phoneNumber,
                               flights[bookings[i].flightId].source,
                               flights[bookings[i].flightId].destination);
                        n++;
                    }
                if (n == 0)
                    printf("We could not find any bookings under flight ID %d.",
                           choice);
                printf("\n");
                break;
            case 5:
                for (int i = 0; i < numberOfFlights; i++)
                    printf(
                        "Flight ID: %d\nFlight availability: %s\nFlight name: "
                        "%s\nTotal "
                        "Seats: "
                        "%d\nFree seats: %d\nSource: %s\nDestination: %s\n\n",
                        i, (flights[i].available) ? "Yes" : "No",
                        flights[i].name, flights[i].seats, flights[i].freeSeats,
                        flights[i].source, flights[i].destination);
                break;
            case 6:
                break;
            default:
                printf("Invalid input.\n");
                break;
            }
        } else if (choice == 2) {
            printf(
                "\nPlease select an operation: -\n\t1. Book a new flight\n\t2. "
                "Cancel a booking (by booking ID)\n\t3. Modify passenger "
                "details on an "
                "existing booking (by booking ID)\n\t4. List all "
                "bookings\n\t5. Return to main "
                "menu\n: ");
            scanf("%d", &choice);
            Flight buffer;
            int id;
            switch (choice) {
            case 1:
                printf("Here's a list of all the flights currently available "
                       "to book.\n");
                for (int i = 0; i < numberOfFlights; i++)
                    if (flights[i].available)
                        printf("\n\tFlight ID: %d\n\tFlight name: %s\n\tTotal "
                               "Seats: "
                               "%d\n\tFree seats: %d\n\tSource: "
                               "%s\n\tDestination: "
                               "%s\n",
                               i, flights[i].name, flights[i].seats,
                               flights[i].freeSeats, flights[i].source,
                               flights[i].destination);
                printf("\nEnter the flight ID for the flight you'd like to "
                       "book: ");
                scanf("%d", &choice);
                if (!flights[choice].available) {
                    printf("That flight's not available. Sorry.\n");
                    break;
                }
                Booking buffer;
                buffer.flightId = choice;
                printf("Enter your name (50 characters or below): ");
                scanf(" %[^\n]s", buffer.passengerName);
                printf("Enter the number of seats you'd like to book: ");
                scanf("%d", &buffer.seats);
                printf("Enter your age: ");
                scanf("%d", &buffer.age);
                printf("Enter your phone number (must strictly be a number): ");
                scanf("%d", &buffer.phoneNumber);
                appendBooking(&bookings, &numberOfBookings, buffer);
                flights[choice].freeSeats -= buffer.seats;
                printf("Your booking ID is: %d\n\n", numberOfBookings - 1);
                break;
            case 2:
                printf("\nEnter the booking ID for the booking you'd like to "
                       "delete: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid booking ID.\n");
                    break;
                }
                if (id >= numberOfBookings) {
                    printf("Could not find booking with booking ID %d.", id);
                    break;
                }
                printf("\nPassenger Name: %s\nFlight ID: %d\nNumber of Seats: "
                       "%d\nAge: %d\nPhone Number: %d\nSource: "
                       "%s\nDestination: %s\n\n",
                       bookings[id].passengerName, bookings[id].flightId,
                       bookings[id].seats, bookings[id].age,
                       bookings[id].phoneNumber,
                       flights[bookings[id].flightId].source,
                       flights[bookings[id].flightId].destination);
                printf(
                    "Are you sure you want to delete this booking? (0 or 1): ");
                scanf("%d", &choice);
                if (choice) {
                    flights[bookings[id].flightId].freeSeats +=
                        bookings[id].seats;
                    deleteBooking(&bookings, &numberOfBookings, id);
                    printf("Booking deleted.\n");
                } else if (choice != 0)
                    printf("Invalid input.\n");
                break;
            case 3:
                printf("\nEnter booking ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid booking ID.\n");
                    break;
                }
                if (id >= numberOfBookings) {
                    printf("Could not find booking with booking ID %d.", id);
                    break;
                }
                printf("\nPassenger Name: %s\nFlight ID: %d\nNumber of Seats: "
                       "%d\nAge: %d\nPhone Number: %d\nSource: "
                       "%s\nDestination: %s\n\n",
                       bookings[id].passengerName, bookings[id].flightId,
                       bookings[id].seats, bookings[id].age,
                       bookings[id].phoneNumber,
                       flights[bookings[id].flightId].source,
                       flights[bookings[id].flightId].destination);
                printf("Do you wish to change everything or modify individual "
                       "fields? "
                       "(0 or 1): ");
                scanf("%d", &choice);
                if (!choice) {
                    printf("\nEnter your name (50 characters or below): ");
                    scanf(" %[^\n]s", bookings[id].passengerName);
                    printf("Enter age: ");
                    scanf("%d", &bookings[id].age);
                    printf("Enter your phone number (must strictly be a "
                           "number): ");
                    scanf("%d", &bookings[id].phoneNumber);
                } else if (choice == 1) {
                    printf("\nWhich passenger detail would you like to change?"
                           "\n1. Passenger Name\n2. Age\n3. Phone Number\n: ");
                    scanf("%d", &choice);
                    switch (choice) {
                    case 1:
                        printf("Enter new passenger name: ");
                        scanf(" %[^\n]s", bookings[id].passengerName);
                        break;
                    case 2:
                        printf("Enter age: ");
                        scanf("%d", &bookings[id].age);
                        break;
                    case 3:
                        printf("Enter your phone number (must strictly be a "
                               "number): ");
                        scanf("%d", &bookings[id].phoneNumber);
                        break;
                    default:
                        printf("Invalid input.\n");
                        break;
                    }
                    printf("Modification complete.\n");
                } else
                    printf("Invalid input.\n");
                break;
            case 4:
                printf("\n");
                for (int id = 0; id < numberOfBookings; id++)
                    printf(
                        "Passenger Name: %s\nFlight ID: %d\nNumber of Seats: "
                        "%d\nAge: %d\nPhone Number: %d\nSource: "
                        "%s\nDestination: %s\n",
                        bookings[id].passengerName, bookings[id].flightId,
                        bookings[id].seats, bookings[id].age,
                        bookings[id].phoneNumber,
                        flights[bookings[id].flightId].source,
                        flights[bookings[id].flightId].destination);
                printf("\n");
                break;
            case 5:
                break;
            default:
                printf("Invalid input.\n");
                break;
            }
        } else if (choice == 3) {
            printf("\nSaving...\n");
            writeBookings(BOOKINGS_LOCATION, bookings, numberOfBookings);
            writeFlights(FLIGHTS_LOCATION, flights, numberOfFlights);
            printf("Saved successfully.\n\n");
        } else if (choice == 4) {
            printf("\nSaving...\n");
            writeBookings(BOOKINGS_LOCATION, bookings, numberOfBookings);
            writeFlights(FLIGHTS_LOCATION, flights, numberOfFlights);
            printf("Saved successfully.\n");
            break;
        } else if (choice == 5)
            break;
        else
            printf("Invalid input. Please enter valid input.\n\n");
    }
    printf("Quitting...\n");
    free(flights);
    free(bookings);
    return 0;
}
