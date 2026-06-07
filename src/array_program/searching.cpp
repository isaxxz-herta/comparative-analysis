// searching.cpp
// Linear Search (unsorted) + Binary Search (sorted, range)

#include <cstring>
#include "searching.h"
#include "utils.h"    

using namespace std;


// LINEAR SEARCH — exact match (text fields)

int linearSearchByID(const Resident arr[], int size, const string &val,
                     int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (strcmp(arr[i].residentID, val.c_str()) == 0)
            results[found++] = i;
    return found;
}

int linearSearchByMode(const Resident arr[], int size, const string &val,
                       int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (strcmp(arr[i].modeOfTransport, val.c_str()) == 0)
            results[found++] = i;
    return found;
}

int linearSearchByCity(const Resident arr[], int size, const string &val,
                       int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (strcmp(arr[i].city, val.c_str()) == 0)
            results[found++] = i;
    return found;
}

int linearSearchByAgeGroup(const Resident arr[], int size, const string &val,
                           int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (strcmp(arr[i].ageGroup, val.c_str()) == 0)
            results[found++] = i;
    return found;
}

// LINEAR SEARCH — range match (numerical fields)

int linearRangeAge(const Resident arr[], int size, double minVal, double maxVal,
                   int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (arr[i].age >= minVal && arr[i].age <= maxVal)
            results[found++] = i;
    return found;
}

int linearRangeDist(const Resident arr[], int size, double minVal, double maxVal,
                    int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (arr[i].dailyDistance >= minVal && arr[i].dailyDistance <= maxVal)
            results[found++] = i;
    return found;
}

int linearRangeEmFactor(const Resident arr[], int size, double minVal, double maxVal,
                        int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (arr[i].carbonEmissionFactor >= minVal && arr[i].carbonEmissionFactor <= maxVal)
            results[found++] = i;
    return found;
}

int linearRangeDays(const Resident arr[], int size, double minVal, double maxVal,
                    int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (arr[i].avgDaysPerMonth >= minVal && arr[i].avgDaysPerMonth <= maxVal)
            results[found++] = i;
    return found;
}

int linearRangeEmission(const Resident arr[], int size, double minVal, double maxVal,
                        int results[], int max) {
    int found = 0;
    for (int i = 0; i < size && found < max; i++)
        if (arr[i].totalEmission >= minVal && arr[i].totalEmission <= maxVal)
            results[found++] = i;
    return found;
}


// BINARY SEARCH — range on SORTED data
// Find first index where key >= minVal (lower bound)
// Find last  index where key <= maxVal (upper bound)
// Collect all indices in between

static int lowerBound(const Resident arr[], int size, int key, double minVal) {
    int lo = 0, hi = size;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (getKey(arr[mid], key) < minVal) lo = mid + 1;
        else                                hi = mid;
    }
    return lo;
}

static int upperBound(const Resident arr[], int size, int key, double maxVal) {
    int lo = 0, hi = size;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (getKey(arr[mid], key) <= maxVal) lo = mid + 1;
        else                                 hi = mid;
    }
    return lo - 1;
}

int binaryRangeSearch(const Resident arr[], int size, int key,
                      double minVal, double maxVal,
                      int results[], int max) {
    int lo = lowerBound(arr, size, key, minVal);
    int hi = upperBound(arr, size, key, maxVal);
    int found = 0;
    for (int i = lo; i <= hi && found < max; i++)
        results[found++] = i;
    return found;
}
