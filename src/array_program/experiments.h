#pragma once
// experiments.h
// Timed experiment runners for sorting and searching, works on any Resident array slice passed in

#include <string>
#include "resident.h"

// Run timed Merge Sort + Quick Sort experiments on arr[0..size-1]
void runSortingExperiments(Resident arr[], int size, const std::string &label);

// Run timed Linear Search (unsorted) + Binary Search (sorted) on arr[0..size-1]
void runSearchingExperiments(Resident arr[], int size, const std::string &label);
