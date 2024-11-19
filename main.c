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
                "existing flight entry (by flight ID)\n: ");
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
                printf("Your flight ID is: %d\n", numberOfFlights);
                getchar();
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
                    break;
                }
                if (id >= numberOfFlights) {
                    printf("Could not find flight with flight ID %d.", id);
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
                       "(0 or 1)");
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
                        "\n4.Free seats\n5. Source\n6. Destination\n");
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
                } else
                    printf("Invalid input.\n");
                break;
            default:
                printf("Invalid input.\n");
                break;
            }
        } else if (choice == 2)
            bookingManagement();
        else if (choice == 3) {
            writeBookings(BOOKINGS_LOCATION, bookings, numberOfBookings);
            writeFlights(FLIGHTS_LOCATION, flights, numberOfFlights);
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
