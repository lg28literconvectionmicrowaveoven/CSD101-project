#include "structs.h"
#include "utils.h"
#include <stdio.h>

void flightManagement(int *choice) {
    printf("Please select an operation: -\n1. Create a new flight entry\n2. "
           "Delete an existing flight entry (by flight ID).\n3. Modify an "
           "existing flight entry (by flight ID)\n: ");
    scanf("%d", choice);
}

void bookingManagement() {}

int main() {
    FILE *flights = fopen("./flights.txt", "rw");
    FILE *bookings = fopen("./bookings.txt", "rw");
    printf("Welcome to the Flight Reservation System (FRS).\n");
    int choice;
    while (1) {
        printf("Please select your mode: -\n1. Flight Management\n2. Booking "
               "Management\n3. Quit\n: ");
        scanf("%d", &choice);
        if (choice == 1)
            flightManagement(&choice);
        else if (choice == 2)
            bookingManagement();
        else if (choice == 3)
            break;
        else
            printf("Invalid input. Please enter valid input.\n\n");
    }
    return 0;
}
