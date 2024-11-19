// TODO: custom flights and bookings path with cmd arguments
#include "structs.h"
#include "utils.h"
#include <stdio.h>

void flightManagement(int *choice, int *numberOfFlights, Flight flights[]) {
    printf("Please select an operation: -\n1. Create a new flight entry\n2. "
           "Delete an existing flight entry (by flight ID).\n3. Modify an "
           "existing flight entry (by flight ID)\n: ");
    scanf("%d", choice);
    Flight buffer;
    switch (*choice) {
    case 1:
        printf("Enter your flight's availability for booking (0 or 1): ");
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
        flights[*(numberOfFlights)++] = buffer;
        printf("Your flight ID is: %d\n", *numberOfFlights);
        break;
    case 2:
        int id;
        printf("Enter flight ID: ");
        scanf("%d", &id);
        if (id >= *numberOfFlights) {
            printf("Could not find flight with flight ID %d.", id);
            break;
        }
        Flight buffer = flights[id];
        printf("Flight availability: %d\nFlight name: %s\nTotal Seats: "
               "%d\nFree seats: %d\nSource: %s\nDestination: %s\n",
               buffer.available, buffer.name, buffer.seats, buffer.freeSeats,
               buffer.source, buffer.destination);
    }
}

void bookingManagement() {}

int main() {
    int numberOfFlights, numberOfBookings;
    Flight *flights = readFlights("./flights.json", &numberOfFlights);
    Booking *bookings = readBookings("./bookings.json", &numberOfBookings);
    printf("Welcome to the Flight Reservation System (FRS).\n");
    int choice;
    while (1) {
        printf("Please select your mode: -\n1. Flight Management\n2. Booking "
               "Management\n3. Quit\n4. Save and Quit\n: ");
        scanf("%d", &choice);
        if (choice == 1)
            flightManagement(&choice, &numberOfFlights, flights);
        else if (choice == 2)
            bookingManagement();
        else if (choice == 3)
            break;
        else
            printf("Invalid input. Please enter valid input.\n\n");
    }
    return 0;
}
