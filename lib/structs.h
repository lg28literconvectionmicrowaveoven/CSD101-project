#ifndef STRUCTS_H_ // Header guard to prevent multiple inclusion
#define STRUCTS_H_

// Structure to store booking information for a passenger
typedef struct {
  char passengerName[51]; // Name of the passenger (max 50 chars + null
                          // terminator)
  int flightId;           // Unique identifier for the flight
  int seats;              // Number of seats booked
  int age;                // Age of the passenger
  int phoneNumber;        // Contact number of the passenger
} Booking;

// Structure to store flight information
typedef struct {
  int available;  // Flag indicating if the flight is available (1) or not (0)
  char name[51];  // Flight name/number (max 50 chars + null terminator)
  int seats;      // Total number of seats in the flight
  int freeSeats;  // Number of seats currently available
  char source[4]; // Three-letter airport code for departure + null terminator
  char
      destination[4]; // Three-letter airport code for arrival + null terminator
} Flight;

// Dynamic array operations for Flight structures
void appendFlight(Flight **array, int *size,
                  Flight element); // Add a new flight to the array
void deleteFlight(Flight **array, int *size,
                  int index); // Remove a flight from the array

// Dynamic array operations for Booking structures
void appendBooking(Booking **array, int *size,
                   Booking element); // Add a new booking to the array
void deleteBooking(Booking **array, int *size,
                   int index); // Remove a booking from the array

// File I/O operations for Flights
Flight *
readFlights(char *path,
            int *numberOfFlights); // Read flights from file, returns array
void writeFlights(char *path, Flight flights[],
                  int size); // Write flights array to file

// File I/O operations for Bookings
Booking *
readBookings(char *path,
             int *numberOfBookings); // Read bookings from file, returns array
void writeBookings(char *path, Booking bookings[],
                   int size); // Write bookings array to file

#endif // STRUCTS_H_  // End of header guard
