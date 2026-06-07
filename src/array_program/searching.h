#pragma once
// searching.h
// Linear Search (unsorted) and Binary Search (sorted)
// Supports exact match for text fields and range for numericals

#include <string>
#include "resident.h"

// Linear Search — exact match (text fields)
// Fills results[] with matching indices, returns count found

int linearSearchByID      (const Resident arr[], int size, const std::string &val, int results[], int max);
int linearSearchByMode    (const Resident arr[], int size, const std::string &val, int results[], int max);
int linearSearchByCity    (const Resident arr[], int size, const std::string &val, int results[], int max);
int linearSearchByAgeGroup(const Resident arr[], int size, const std::string &val, int results[], int max);

// Linear Search — range match (numerical fields)
// Matches records where field value is within [minVal, maxVal]

int linearRangeAge       (const Resident arr[], int size, double minVal, double maxVal, int results[], int max);
int linearRangeDist      (const Resident arr[], int size, double minVal, double maxVal, int results[], int max);
int linearRangeEmFactor  (const Resident arr[], int size, double minVal, double maxVal, int results[], int max);
int linearRangeDays      (const Resident arr[], int size, double minVal, double maxVal, int results[], int max);
int linearRangeEmission  (const Resident arr[], int size, double minVal, double maxVal, int results[], int max);

// Binary Search — range match on SORTED data
// Array must be sorted by the corresponding key (use getKey / mergeSort)
// Returns number of matches; fills results[] with matching indices

int binaryRangeSearch(const Resident arr[], int size, int key,
                      double minVal, double maxVal,
                      int results[], int max);
