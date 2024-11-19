#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct {
    char passengerName[50];
    int flightId;
    int seats;
    int age;
    int phoneNumber;
} Booking;

typedef struct {
    int available;
    char name[20];
    int seats;
    int freeSeats;
    char source[3];
    char destination[3];
} Flight;

Flight *appendFlight(Flight *array, int size, Flight element);
Booking *appendBooking(Booking *array, int size, Booking element);
Flight *readFlights(char *path, int *numberOfFlights);
Booking *readBookings(char *path, int *numberOfBookings);

#endif // STRUCTS_H_
