#pragma once
// utils.h
// Utility helpers: CSV loading, display, age group, key extractor

#include <string>
#include "resident.h"

// Assign age group label to a Resident
void assignAgeGroup(Resident &r);

// Extract numeric sort key from a Resident
// key 0 = Age, key 1 = DailyDistance, key 2 = TotalEmission
double getKey(const Resident &r, int key);

// Load a CSV file into the global master array
// Returns number of records loaded
int loadCSV(const std::string &filename, const std::string &cityLabel);

// Copy all records for one city into dest[]
// Returns number of records copied
int extractCity(const char *cityLabel, Resident dest[], int maxDest);

// Print a horizontal separator line
void printLine(int width = 80);

// Display up to maxShow records from arr[]
void displayRecords(const Resident arr[], int size, int maxShow = 20);
