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
    system("clear");
    printf("Welcome to the Flight Reservation System (FRS).\n");
    int choice;
    printf("Please select your mode: -\n1. Flight Management\n2. Booking "
           "Management\n3. Quit\n: ");
    while (1) {
        scanf("%d", &choice);
        if (choice == 1) {
            system("clear");
            printf(
                "Please select an operation: -\n1. Create a new flight "
                "entry\n2. "
                "Delete an existing flight entry (by flight ID).\n3. Modify an "
                "existing flight entry (by flight ID)\n4. List all bookings "
                "under a flight (by flight ID)\n5. List all flight "
                "entries\n: ");
            scanf("%d", &choice);
            Flight buffer;
            switch (choice) {
            case 1:
                system("clear");
                printf(
                    "Enter your flight's availability for booking (0 or 1): ");
                scanf("%d", &buffer.available);
                printf("Enter your flight's name (20 characters or under): ");
                scanf(" %[^\n]s", buffer.name);
                printf("Enter number of seats: ");
                scanf("%d", &buffer.seats);
                buffer.freeSeats = buffer.seats;
                printf("Enter flight source (3 characters): ");
                scanf(" %[^\n]s", buffer.source);
                printf("Enter flight destination (3 characters): ");
                scanf(" %[^\n]s", buffer.destination);
                appendFlight(flights, &numberOfFlights, buffer);
                system("clear");
                printf("Your flight ID is: %d\n", numberOfFlights);
                break;
            case 2:
                system("clear");
                int id;
                printf("Enter flight ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid flight ID.\n");
                    break;
                }
                if (id >= numberOfFlights) {
                    printf("Could not find flight with flight ID %d.", id);
                    printf("Press enter to continue...");
                    getchar();
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
                    deleteFlight(flights, &numberOfFlights, id);
                    for (int i = 0; i < numberOfBookings; i++) {
                        if (bookings[i].flightId == id) {
                            deleteBooking(bookings, &numberOfBookings, i);
                            i--;
                        }
                    }
                    printf("Deleted flight and corresponding bookings.\n");
                } else if (choice != 0)
                    printf("Invalid input.\n");
                break;
            case 3:
                system("clear");
                int id;
                printf("Enter flight ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid flight ID.\n");
                    printf("Press enter to continue...");
                    getchar();
                    break;
                }
                if (id >= numberOfFlights) {
                    printf("Could not find flight with flight ID %d.", id);
                    printf("Press enter to continue...");
                    getchar();
                    break;
                }
                printf("Flight availability: %s\nFlight name: %s\nTotal Seats: "
                       "%d\nFree seats: %d\nSource: %s\nDestination: %s\n",
                       (flights[id].available) ? "Yes" : "No", flights[id].name,
                       flights[id].seats, flights[id].freeSeats,
                       flights[id].source, flights[id].destination);
                printf("Do you wish to change everything or modify individual "
                       "fields? "
                       "(0 or 1): ");
                scanf("%d", &choice);
                system("clear");
                if (!choice) {
                    printf("Enter your flight's availability for booking (0 or "
                           "1): ");
                    scanf("%d", &flights[id].available);
                    printf(
                        "Enter your flight's name (20 characters or under): ");
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
                    printf("Which parameter would you like to change?");
                    printf(
                        "1. Flight availability\n2. Flight name\n3. Total Seats"
                        "\n4.Free seats\n5. Source\n6. Destination\n: ");
                    scanf("%d", &choice);
                    switch (choice) {
                    case 1:
                        printf("Enter your flight's availability for booking "
                               "(0 or 1): ");
                        scanf("%d", &(flights[id].available));
                        break;
                    case 2:
                        printf("Enter your flight's name (20 characters or "
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
                for (int i = 0; i < numberOfBookings; i++)
                    if (bookings[i].flightId == choice)
                        printf(
                            "Flight availability: %s\nFlight name: %s\nTotal "
                            "Seats: "
                            "%d\nFree seats: %d\nSource: %s\nDestination: "
                            "%s\n\n",
                            (flights[i].available) ? "Yes" : "No",
                            flights[i].name, flights[i].seats,
                            flights[i].freeSeats, flights[i].source,
                            flights[i].destination);
                break;
            case 5:
                for (int i = 0; i < numberOfFlights; i++)
                    printf(
                        "Flight availability: %s\nFlight name: %s\nTotal "
                        "Seats: "
                        "%d\nFree seats: %d\nSource: %s\nDestination: %s\n\n",
                        (flights[i].available) ? "Yes" : "No", flights[i].name,
                        flights[i].seats, flights[i].freeSeats,
                        flights[i].source, flights[i].destination);
                break;
            default:
                printf("Invalid input.\n");
                break;
            }
            printf("Press enter to continue...");
            getchar();
        } else if (choice == 2) {
            system("clear");
            printf("Please select an operation: -\n1. Book a new flight\n2. "
                   "Cancel a booking (by booking ID).\n3. Modify passenger "
                   "details on an "
                   "existing booking (by booking ID)\n: ");
            scanf("%d", &choice);
            Flight buffer;
            switch (choice) {
            case 1:
                system("clear");
                printf("Here's a list of all the flights currently available "
                       "to book.");
                for (int i = 0; i < numberOfFlights; i++)
                    if (flights[i].available)
                        printf("Flight name: %s\nTotal "
                               "Seats: "
                               "%d\nFree seats: %d\nSource: %s\nDestination: "
                               "%s\n\n",
                               flights[i].name, flights[i].seats,
                               flights[i].freeSeats, flights[i].source,
                               flights[i].destination);
                printf(
                    "Enter the flight ID for the flight you'd like to book: ");
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
                appendBooking(bookings, &numberOfBookings, buffer);
                printf("Your booking ID is: %d\n", numberOfBookings);
                printf("Press enter to continue...");
                getchar();
                break;
            case 2:
                system("clear");
                int id;
                printf("Enter the booking ID for the booking you'd like to "
                       "delete: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid booking ID.\n");
                    break;
                }
                if (id >= numberOfBookings) {
                    printf("Could not find booking with booking ID %d.", id);
                    printf("Press enter to continue...");
                    getchar();
                    break;
                }
                printf("Passenger Name: %s\nFlight ID: %d\nNumber of Seats: "
                       "%d\nAge: %d\nPhone Number: %d\nSource: "
                       "%s\nDestination: %s\n",
                       bookings[id].passengerName, bookings[id].flightId,
                       bookings[id].seats, bookings[id].age,
                       bookings[id].phoneNumber,
                       flights[bookings[id].flightId].source,
                       flights[bookings[id].flightId].destination);
                printf(
                    "Are you sure you want to delete this booking? (0 or 1): ");
                scanf("%d", &choice);
                if (choice) {
                    deleteBooking(bookings, &numberOfBookings, id);
                    printf("Booking deleted.\n");
                } else if (choice != 0)
                    printf("Invalid input.\n");
                break;
            case 3:
                system("clear");
                int id;
                printf("Enter booking ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid booking ID.\n");
                    break;
                }
                if (id >= numberOfBookings) {
                    printf("Could not find booking with booking ID %d.", id);
                    printf("Press enter to continue...");
                    getchar();
                    break;
                }
                printf("Passenger Name: %s\nFlight ID: %d\nNumber of Seats: "
                       "%d\nAge: %d\nPhone Number: %d\nSource: "
                       "%s\nDestination: %s\n",
                       bookings[id].passengerName, bookings[id].flightId,
                       bookings[id].seats, bookings[id].age,
                       bookings[id].phoneNumber,
                       flights[bookings[id].flightId].source,
                       flights[bookings[id].flightId].destination);
                printf("Do you wish to change everything or modify individual "
                       "fields? "
                       "(0 or 1): ");
                scanf("%d", &choice);
                system("clear");
                if (!choice) {
                    printf("Enter your name (50 characters or below): ");
                    scanf(" %[^\n]s", bookings[id].passengerName);
                    printf("Enter age: ");
                    scanf("%d", &bookings[id].age);
                    printf("Enter your phone number (must strictly be a "
                           "number): ");
                    scanf("%d", &bookings[id].phoneNumber);
                } else if (choice == 1) {
                    printf("Which passenger detail would you like to change?");
                    printf("1. Passenger Name\n2. Age\n3. Phone Number\n: ");
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
            default:
                printf("Invalid input.\n");
                break;
            }
            printf("Press enter to continue...");
            getchar();
        } else if (choice == 3) {
            printf("Saving...");
            writeBookings(BOOKINGS_LOCATION, bookings, numberOfBookings);
            writeFlights(FLIGHTS_LOCATION, flights, numberOfFlights);
            printf("Saved successfully.");
            break;
        } else if (choice == 4)
            break;
        else {
            printf("Invalid input. Please enter valid input.\n\n");
            break;
        }
        system("clear");
        printf("Please select your mode: -\n1. Flight Management\n2. Booking "
               "Management\n3. Quit\n4. Save and Quit\n: ");
    }
    printf("Quitting...");
    return 0;
}
