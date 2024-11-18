#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Booking {
    char passengerName[50];
    int flightId;
    int seats;
    int age;
    int phoneNumber;
} Booking;

typedef struct Flight {
    int id;
    short int available;
    char name[20];
    int seats;
    int freeSeats;
    char source[3];
    char destination[3];
    Booking *bookings;
} Flight;

#endif
