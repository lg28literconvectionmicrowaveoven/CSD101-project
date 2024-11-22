#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct {
    char passengerName[51];
    int flightId;
    int seats;
    int age;
    int phoneNumber;
} Booking;

typedef struct {
    int available;
    char name[51];
    int seats;
    int freeSeats;
    char source[4];
    char destination[4];
} Flight;

void appendFlight(Flight **array, int *size, Flight element);
void deleteFlight(Flight **array, int *size, int index);
void appendBooking(Booking **array, int *size, Booking element);
void deleteBooking(Booking **array, int *size, int index);

Flight *readFlights(char *path, int *numberOfFlights);
Booking *readBookings(char *path, int *numberOfBookings);
void writeFlights(char *path, Flight flights[], int size);
void writeBookings(char *path, Booking bookings[], int size);

#endif // STRUCTS_H_
