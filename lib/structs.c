#include "structs.h"
#include "cJSON.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Appends a new flight to a dynamic array of flights
// If array is NULL, creates new array with single element
void appendFlight(Flight **array, int *size, Flight element) {
  if (array == NULL) { // Initialize new array if none exists
    *array = malloc(sizeof(Flight));
    *size = 1;
    (*array)[0] = element;
    return;
  }
  // Create new array with one extra space
  Flight *newArray = malloc(sizeof(Flight) * (*size + 1));
  // Copy existing elements
  memcpy(newArray, *array, sizeof(Flight) * (*size));
  // Add new element at end
  newArray[*size] = element;
  (*size)++;
  free(*array);      // Free old array
  *array = newArray; // Update pointer to new array
}

// Removes a flight from the array at specified index
// Handles special cases for empty array and single element
void deleteFlight(Flight **array, int *size, int index) {
  if (*array == NULL || *size <= 0) { // Handle empty array
    *size = 0;
    return;
  }
  if (*size == 1) { // Handle single element array
    free(*array);
    *size = 0;
    *array = NULL;
    return;
  }
  // Create new array with one less space
  Flight *newArray = malloc(sizeof(Flight) * (*size - 1));
  // Copy elements before index
  if (index > 0)
    memcpy(newArray, *array, sizeof(Flight) * index);
  // Copy elements after index
  if (index < *size - 1)
    memcpy(newArray + index, *array + index + 1,
           sizeof(Flight) * (*size - index - 1));
  (*size)--;
  free(*array);
  *array = newArray;
}

// Appends a new booking to a dynamic array of bookings
// Similar logic to appendFlight
void appendBooking(Booking **array, int *size, Booking element) {
  if (array == NULL) {
    *array = malloc(sizeof(Booking));
    *size = 1;
    (*array)[0] = element;
    return;
  }
  Booking *newArray = malloc(sizeof(Booking) * (*size + 1));
  memcpy(newArray, *array, sizeof(Booking) * (*size));
  newArray[*size] = element;
  (*size)++;
  free(*array);
  *array = newArray;
}

// Removes a booking from the array at specified index
// Similar logic to deleteFlight
void deleteBooking(Booking **array, int *size, int index) {
  if (*array == NULL || *size <= 0) {
    *size = 0;
    return;
  }
  if (*size == 1) {
    free(*array);
    *size = 0;
    array = NULL; // Note: This line has a bug - should be *array = NULL
    return;
  }
  Booking *newArray = malloc(sizeof(Booking) * (*size - 1));
  if (index > 0)
    memcpy(newArray, *array, sizeof(Booking) * index);
  if (index < *size - 1)
    memcpy(newArray + index, *array + index + 1,
           sizeof(Booking) * (*size - index - 1));
  (*size)--;
  free(*array);
  *array = newArray;
}

// Reads flights data from JSON file and converts to Flight array
Flight *readFlights(char *path, int *numberOfFlights) {
  // Read file contents
  const char *contents = readFile(path);
  if (contents == NULL) { // Handle non-existent file
    *numberOfFlights = 0;
    writeFile("{\n\t\"type\": \"flights\"\n}", path);
    return NULL;
  }

  // Parse JSON and validate type
  cJSON *json = cJSON_Parse(contents);
  free((void *)contents);
  if (json == NULL) { // Handle invalid JSON
    const char *errorPtr = cJSON_GetErrorPtr();
    printf("JSON has been tampered with.\n");
    if (errorPtr != NULL)
      printf("%s", errorPtr);
    exit(-1);
  }

  // Verify JSON type is "flights"
  cJSON *type = cJSON_GetObjectItemCaseSensitive(json, "type");
  if (strcmp(type->valuestring, "flights") != 0) {
    printf("JSON has been tampered with.\n");
    exit(-1);
  }

  // Extract flights array from JSON
  cJSON *flightsJSON = cJSON_GetObjectItemCaseSensitive(json, "flights");
  *numberOfFlights = cJSON_GetArraySize(flightsJSON);
  Flight *flights = malloc(sizeof(Flight) * (*numberOfFlights));

  // Parse each flight object
  for (int i = 0; i < *numberOfFlights; i++) {
    cJSON *flightJSON = cJSON_GetArrayItem(flightsJSON, i);
    Flight flight;

    // Extract and validate each field
    cJSON *nameJSON = cJSON_GetObjectItemCaseSensitive(flightJSON, "name");
    if (cJSON_IsString(nameJSON) && (nameJSON->valuestring != NULL))
      strcpy(flight.name, nameJSON->valuestring);
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    // Parse availability
    cJSON *availabilityJSON =
        cJSON_GetObjectItemCaseSensitive(flightJSON, "available");
    flight.available = cJSON_IsTrue(availabilityJSON);

    // Parse seats
    cJSON *seatsJSON = cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
    if (cJSON_IsNumber(seatsJSON))
      flight.seats = seatsJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    // Parse free seats
    cJSON *freeSeatsJSON =
        cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
    if (cJSON_IsNumber(freeSeatsJSON))
      flight.freeSeats = freeSeatsJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    // Parse source airport
    cJSON *sourceJSON = cJSON_GetObjectItemCaseSensitive(flightJSON, "source");
    if (cJSON_IsString(sourceJSON) && (sourceJSON->valuestring != NULL))
      strcpy(flight.source, sourceJSON->valuestring);
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    // Parse destination airport
    cJSON *destinationJSON =
        cJSON_GetObjectItemCaseSensitive(flightJSON, "destination");
    if (cJSON_IsString(destinationJSON) &&
        (destinationJSON->valuestring != NULL))
      strcpy(flight.destination, destinationJSON->valuestring);
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    flights[i] = flight;
  }

  cJSON_Delete(json);
  return flights;
}

// Reads bookings data from JSON file and converts to Booking array
// Similar structure to readFlights
Booking *readBookings(char *path, int *numberOfBookings) {
  const char *contents = readFile(path);
  if (contents == NULL) {
    *numberOfBookings = 0;
    writeFile("{\n\t\"type\": \"bookings\"\n}", path);
    return NULL;
  }

  cJSON *json = cJSON_Parse(contents);
  free((void *)contents);
  if (json == NULL) {
    const char *errorPtr = cJSON_GetErrorPtr();
    printf("JSON has been tampered with.\n");
    if (errorPtr != NULL)
      printf("%s", errorPtr);
    exit(-1);
  }

  cJSON *type = cJSON_GetObjectItemCaseSensitive(json, "type");
  if (strcmp(type->valuestring, "bookings") != 0) {
    printf("JSON has been tampered with.\n");
    exit(-1);
  }

  // Extract and parse bookings array
  cJSON *bookingsJSON = cJSON_GetObjectItemCaseSensitive(json, "bookings");
  *numberOfBookings = cJSON_GetArraySize(bookingsJSON);
  Booking *bookings = malloc(sizeof(Booking) * (*numberOfBookings));

  for (int i = 0; i < *numberOfBookings; i++) {
    cJSON *bookingJSON = cJSON_GetArrayItem(bookingsJSON, i);
    Booking booking;

    // Parse each booking field
    cJSON *passengerNameJSON =
        cJSON_GetObjectItemCaseSensitive(bookingJSON, "passengerName");
    if (cJSON_IsString(passengerNameJSON) &&
        (passengerNameJSON->valuestring != NULL))
      strcpy(booking.passengerName, passengerNameJSON->valuestring);
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    cJSON *flightIdJSON =
        cJSON_GetObjectItemCaseSensitive(bookingJSON, "flightId");
    if (cJSON_IsNumber(flightIdJSON))
      booking.flightId = flightIdJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    cJSON *seatsJSON = cJSON_GetObjectItemCaseSensitive(bookingJSON, "seats");
    if (cJSON_IsNumber(seatsJSON))
      booking.seats = seatsJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    cJSON *ageJSON = cJSON_GetObjectItemCaseSensitive(bookingJSON, "age");
    if (cJSON_IsNumber(ageJSON))
      booking.age = ageJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    cJSON *phoneNumberJSON =
        cJSON_GetObjectItemCaseSensitive(bookingJSON, "phoneNumber");
    if (cJSON_IsNumber(phoneNumberJSON))
      booking.phoneNumber = phoneNumberJSON->valueint;
    else {
      printf("JSON has been tampered.\n");
      exit(-1);
    }

    bookings[i] = booking;
  }

  cJSON_Delete(json);
  return bookings;
}

// Writes array of flights to JSON file
void writeFlights(char *path, Flight flights[], int size) {
  if (flights == NULL) { // Handle empty array
    writeFile("{\n\t\"type\": \"flights\"\n}", path);
    return;
  }

  // Create JSON object and add type
  cJSON *json = cJSON_CreateObject();
  cJSON_AddItemToObject(json, "type", cJSON_CreateString("flights"));

  // Create flights array
  cJSON *flightsJSON = cJSON_CreateArray();
  for (int i = 0; i < size; i++) {
    cJSON *flightJSON = cJSON_CreateObject();
    Flight flight = flights[i];

    // Add all flight fields to JSON object
    cJSON_AddItemToObject(flightJSON, "name", cJSON_CreateString(flight.name));
    cJSON_AddItemToObject(flightJSON, "available",
                          (flight.available) ? cJSON_CreateTrue()
                                             : cJSON_CreateFalse());
    cJSON_AddItemToObject(flightJSON, "seats",
                          cJSON_CreateNumber(flight.seats));
    cJSON_AddItemToObject(flightJSON, "freeSeats",
                          cJSON_CreateNumber(flight.freeSeats));
    cJSON_AddItemToObject(flightJSON, "source",
                          cJSON_CreateString(flight.source));
    cJSON_AddItemToObject(flightJSON, "destination",
                          cJSON_CreateString(flight.destination));
    cJSON_AddItemToArray(flightsJSON, flightJSON);
  }

  // Add flights array to main JSON object
  cJSON_AddItemToObject(json, "flights", flightsJSON);

  // Write JSON to file and clean up
  char *out = cJSON_Print(json);
  writeFile(out, path);
  free(out);
  cJSON_Delete(json);
}

// Writes array of bookings to JSON file
// Similar structure to writeFlights
void writeBookings(char *path, Booking bookings[], int size) {
  if (bookings == NULL) {
    writeFile("{\n\t\"type\": \"bookings\"\n}", path);
    return;
  }

  cJSON *json = cJSON_CreateObject();
  cJSON_AddItemToObject(json, "type", cJSON_CreateString("bookings"));
  cJSON *bookingsJSON = cJSON_CreateArray();

  for (int i = 0; i < size; i++) {
    cJSON *bookingJSON = cJSON_CreateObject();
    Booking booking = bookings[i];

    // Add all booking fields to JSON object
    cJSON_AddItemToObject(bookingJSON, "passengerName",
                          cJSON_CreateString(booking.passengerName));
    cJSON_AddItemToObject(bookingJSON, "flightId",
                          cJSON_CreateNumber(booking.flightId));
    cJSON_AddItemToObject(bookingJSON, "seats",
                          cJSON_CreateNumber(booking.seats));
    cJSON_AddItemToObject(bookingJSON, "age", cJSON_CreateNumber(booking.age));
    cJSON_AddItemToObject(bookingJSON, "phoneNumber",
                          cJSON_CreateNumber(booking.phoneNumber));
    cJSON_AddItemToArray(bookingsJSON, bookingJSON);
  }

  cJSON_AddItemToObject(json, "bookings", bookingsJSON);
  char *out = cJSON_Print(json);
  writeFile(out, path);
  free(out);
  cJSON_Delete(json);
}
