// TODO: specific seat numbers
#include "structs.h"
#include "cJSON/cJSON.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Flight *appendFlight(Flight *array, int size, Flight element) {
    Flight *newArray = malloc(sizeof(Flight) * (size + 1));
    for (int i = 0; i < size; i++)
        newArray[i] = array[i];
    newArray[size] = element;
    return newArray;
}

Booking *appendBooking(Booking *array, int size, Booking element) {
    Booking *newArray = malloc(sizeof(Booking) * (size + 1));
    for (int i = 0; i < size; i++)
        newArray[i] = array[i];
    newArray[size] = element;
    return newArray;
}

Flight *readFlights(char *path, int *numberOfFlights) {
    const char *contents = readFile(path);
    cJSON *json = cJSON_Parse(contents);
    if (json == NULL) {
        const char *errorPtr = cJSON_GetErrorPtr();
        printf("JSON has been tampered with.\n");
        if (errorPtr != NULL)
            printf("%s", errorPtr);
        exit(-1);
    }
    cJSON *type = cJSON_GetObjectItemCaseSensitive(json, "type");
    if (!strcmp(type->valuestring, "flights")) {
        printf("JSON has been tampered with.\n");
        exit(-1);
    }
    cJSON_Delete(type);
    cJSON *flightsJSON = cJSON_GetObjectItemCaseSensitive(json, "flights");
    *numberOfFlights = cJSON_GetArraySize(flightsJSON);
    Flight *flights = malloc(sizeof(Flight) * (*numberOfFlights));
    for (int i = 0; i < numberOfFlights; i++) {
        cJSON *flightJSON = cJSON_GetArrayItem(flightsJSON, i);
        Flight flight;
        cJSON *nameJSON = cJSON_GetObjectItemCaseSensitive(flightJSON, "name");
        if (cJSON_IsString(nameJSON) && (nameJSON->valuestring != NULL))
            strcpy(flight.name, nameJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(nameJSON);
        cJSON *availabilityJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "available");
        if (cJSON_IsTrue(availabilityJSON) == 0)
            flight.available = 1;
        else
            flight.available = 0;
        cJSON_Delete(availabilityJSON);
        cJSON *seatsJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
        if (cJSON_IsNumber(seatsJSON))
            flight.seats = seatsJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(seatsJSON);
        cJSON *freeSeatsJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
        if (cJSON_IsNumber(freeSeatsJSON))
            flight.freeSeats = freeSeatsJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(freeSeatsJSON);
        cJSON *sourceJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "source");
        if (cJSON_IsString(sourceJSON) && (sourceJSON->valuestring != NULL))
            strcpy(flight.destination, sourceJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(sourceJSON);
        cJSON *destinationJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "destination");
        if (cJSON_IsString(destinationJSON) &&
            (destinationJSON->valuestring != NULL))
            strcpy(flight.destination, destinationJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(destinationJSON);
        cJSON_Delete(flightJSON);
        flights[i] = flight;
    }
    cJSON_Delete(flightsJSON);
    cJSON_Delete(json);
    return flights;
}

Booking *readBookings(char *path, int *numberOfBookings) {
    const char *contents = readFile(path);
    cJSON *json = cJSON_Parse(contents);
    if (json == NULL) {
        const char *errorPtr = cJSON_GetErrorPtr();
        printf("JSON has been tampered with.\n");
        if (errorPtr != NULL)
            printf("%s", errorPtr);
        exit(-1);
    }
    cJSON *type = cJSON_GetObjectItemCaseSensitive(json, "type");
    if (!strcmp(type->valuestring, "bookings")) {
        printf("JSON has been tampered with.\n");
        exit(-1);
    }
    cJSON_Delete(type);
    cJSON *bookingsJSON = cJSON_GetObjectItemCaseSensitive(json, "bookings");
    *numberOfBookings = cJSON_GetArraySize(bookingsJSON);
    Booking *bookings = malloc(sizeof(Booking) * (*numberOfBookings));
    for (int i = 0; i < numberOfBookings; i++) {
        cJSON *bookingJSON = cJSON_GetArrayItem(bookingsJSON, i);
        Booking booking;
        cJSON *passengerNameJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "passengerName");
        if (cJSON_IsString(passengerNameJSON) &&
            (passengerNameJSON->valuestring != NULL))
            strcpy(booking.passengerName, passengerNameJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(passengerNameJSON);
        cJSON *flightIdJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "flightId");
        if (cJSON_IsNumber(flightIdJSON))
            booking.flightId = flightIdJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(flightIdJSON);
        cJSON *seatsJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "seats");
        if (cJSON_IsNumber(seatsJSON))
            booking.seats = seatsJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(seatsJSON);
        cJSON *ageJSON = cJSON_GetObjectItemCaseSensitive(bookingJSON, "age");
        if (cJSON_IsNumber(ageJSON))
            booking.age = ageJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(ageJSON);
        cJSON *phoneNumberJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "phoneNumber");
        if (cJSON_IsNumber(phoneNumberJSON))
            booking.phoneNumber = phoneNumberJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON_Delete(phoneNumberJSON);
        cJSON_Delete(bookingJSON);
        bookings[i] = booking;
    }
    cJSON_Delete(bookingsJSON);
    cJSON_Delete(json);
    return bookings;
}
