#include "structs.h"
#include "cJSON.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void appendFlight(Flight **array, int *size, Flight element) {
    if (array == NULL) {
        *array = malloc(sizeof(Flight));
        *size = 1;
        (*array)[0] = element;
        return;
    }
    Flight *newArray = malloc(sizeof(Flight) * (*size + 1));
    memcpy(newArray, *array, sizeof(Flight) * (*size));
    newArray[*size] = element;
    (*size)++;
    free(*array);
    *array = newArray;
}

void deleteFlight(Flight **array, int *size, int index) {
    if (*array == NULL || *size <= 0) {
        *size = 0;
        return;
    }
    if (*size == 1) {
        free(*array);
        *size = 0;
        *array = NULL;
        return;
    }
    Flight *newArray = malloc(sizeof(Flight) * (*size - 1));
    if (index > 0)
        memcpy(newArray, *array, sizeof(Flight) * index);
    if (index < *size - 1)
        memcpy(newArray + index, *array + index + 1,
               sizeof(Flight) * (*size - index - 1));
    (*size)--;
    free(*array);
    *array = newArray;
}

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

void deleteBooking(Booking **array, int *size, int index) {
    if (*array == NULL || *size <= 0) {
        *size = 0;
        return;
    }
    if (*size == 1) {
        free(*array);
        *size = 0;
        array = NULL;
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

Flight *readFlights(char *path, int *numberOfFlights) {
    const char *contents = readFile(path);
    if (contents == NULL) {
        *numberOfFlights = 0;
        writeFile("{\n\t\"type\": \"flights\"\n}", path);
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
    if (strcmp(type->valuestring, "flights") != 0) {
        printf("JSON has been tampered with.\n");
        exit(-1);
    }
    cJSON *flightsJSON = cJSON_GetObjectItemCaseSensitive(json, "flights");
    *numberOfFlights = cJSON_GetArraySize(flightsJSON);
    Flight *flights = malloc(sizeof(Flight) * (*numberOfFlights));
    for (int i = 0; i < *numberOfFlights; i++) {
        cJSON *flightJSON = cJSON_GetArrayItem(flightsJSON, i);
        Flight flight;
        cJSON *nameJSON = cJSON_GetObjectItemCaseSensitive(flightJSON, "name");
        if (cJSON_IsString(nameJSON) && (nameJSON->valuestring != NULL))
            strcpy(flight.name, nameJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON *availabilityJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "available");
        flight.available = cJSON_IsTrue(availabilityJSON);
        cJSON *seatsJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
        if (cJSON_IsNumber(seatsJSON))
            flight.seats = seatsJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON *freeSeatsJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "seats");
        if (cJSON_IsNumber(freeSeatsJSON))
            flight.freeSeats = freeSeatsJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON *sourceJSON =
            cJSON_GetObjectItemCaseSensitive(flightJSON, "source");
        if (cJSON_IsString(sourceJSON) && (sourceJSON->valuestring != NULL))
            strcpy(flight.source, sourceJSON->valuestring);
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
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
    cJSON *bookingsJSON = cJSON_GetObjectItemCaseSensitive(json, "bookings");
    *numberOfBookings = cJSON_GetArraySize(bookingsJSON);
    Booking *bookings = malloc(sizeof(Booking) * (*numberOfBookings));
    for (int i = 0; i < *numberOfBookings; i++) {
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
        cJSON *flightIdJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "flightId");
        if (cJSON_IsNumber(flightIdJSON))
            booking.flightId = flightIdJSON->valueint;
        else {
            printf("JSON has been tampered.\n");
            exit(-1);
        }
        cJSON *seatsJSON =
            cJSON_GetObjectItemCaseSensitive(bookingJSON, "seats");
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

void writeFlights(char *path, Flight flights[], int size) {
    if (flights == NULL) {
        writeFile("{\n\t\"type\": \"flights\"\n}", path);
        return;
    }
    cJSON *json = cJSON_CreateObject();
    cJSON_AddItemToObject(json, "type", cJSON_CreateString("flights"));
    cJSON *flightsJSON = cJSON_CreateArray();
    for (int i = 0; i < size; i++) {
        cJSON *flightJSON = cJSON_CreateObject();
        Flight flight = flights[i];
        cJSON_AddItemToObject(flightJSON, "name",
                              cJSON_CreateString(flight.name));
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
    cJSON_AddItemToObject(json, "flights", flightsJSON);
    char *out = cJSON_Print(json);
    writeFile(out, path);
    free(out);
    cJSON_Delete(json);
}

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
        cJSON_AddItemToObject(bookingJSON, "passengerName",
                              cJSON_CreateString(booking.passengerName));
        cJSON_AddItemToObject(bookingJSON, "flightId",
                              cJSON_CreateNumber(booking.flightId));
        cJSON_AddItemToObject(bookingJSON, "seats",
                              cJSON_CreateNumber(booking.seats));
        cJSON_AddItemToObject(bookingJSON, "age",
                              cJSON_CreateNumber(booking.age));
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
