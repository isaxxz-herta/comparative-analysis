#pragma once
// resident.h
// Defines the Resident data structure and array size constant

const int MAX_SIZE = 600;

struct Resident {
    char   residentID[10];
    int    age;
    char   modeOfTransport[20];
    double dailyDistance;
    double carbonEmissionFactor;
    int    avgDaysPerMonth;
    double totalEmission;
    char   ageGroup[40];
    char   city[10];
};
