#pragma once
// analysis.h
// Carbon emission analysis on any Resident array slice

#include <string>
#include "resident.h"

// Run full carbon emission analysis on arr[0..size-1]
// label is printed as the dataset title (e.g. "Dataset 1 (City A)")
void runAnalysis(const Resident arr[], int size, const std::string &label);

// Run age group report: preferred transport, total & avg emission per group
void runAgeGroupReport(const Resident arr[], int size, const std::string &label);
