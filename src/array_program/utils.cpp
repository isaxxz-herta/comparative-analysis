// utils.cpp
// Utility helpers: CSV loading, display, age group, key extractor

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include "utils.h"
#include "globals.h"

using namespace std;

// Age group label
void assignAgeGroup(Resident &r) {
    if      (r.age >= 6  && r.age <= 17)  strcpy(r.ageGroup, "Children & Teenagers (6-17)");
    else if (r.age >= 18 && r.age <= 25)  strcpy(r.ageGroup, "University Students (18-25)");
    else if (r.age >= 26 && r.age <= 45)  strcpy(r.ageGroup, "Working Adults Early (26-45)");
    else if (r.age >= 46 && r.age <= 60)  strcpy(r.ageGroup, "Working Adults Late (46-60)");
    else                                   strcpy(r.ageGroup, "Senior Citizens (61-100)");
}

// Sort key extractor
double getKey(const Resident &r, int key) {
    if (key == 0) return r.age;
    if (key == 1) return r.dailyDistance;
    return r.totalEmission;
}

// Load CSV into global master array
int loadCSV(const string &filename, const string &cityLabel) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[ERROR] Cannot open file: " << filename << endl;
        return 0;
    }
    
    string line;
    getline(file, line); 
    int count = 0;
    while (getline(file, line) && masterSize < MAX_SIZE) {
        if (line.empty()) continue;
        if (!line.empty() && line.back() == '\r') line.pop_back();

        stringstream ss(line);
        string token;
        Resident r;

        getline(ss, token, ','); strncpy(r.residentID,        token.c_str(), 9);  r.residentID[9]        = '\0';
        getline(ss, token, ','); r.age = stoi(token);
        getline(ss, token, ','); strncpy(r.modeOfTransport,   token.c_str(), 19); r.modeOfTransport[19]  = '\0';
        getline(ss, token, ','); r.dailyDistance        = stod(token);
        getline(ss, token, ','); r.carbonEmissionFactor = stod(token);
        getline(ss, token, ','); r.avgDaysPerMonth      = stoi(token);

        r.totalEmission = r.dailyDistance * r.carbonEmissionFactor * r.avgDaysPerMonth;
        strncpy(r.city, cityLabel.c_str(), 9); r.city[9] = '\0';
        assignAgeGroup(r);

        master[masterSize++] = r;
        count++;
    }
    file.close();
    return count;
}

// Extract one city's records into dest
int extractCity(const char *cityLabel, Resident dest[], int maxDest) {
    int n = 0;
    for (int i = 0; i < masterSize && n < maxDest; i++)
        if (strcmp(master[i].city, cityLabel) == 0)
            dest[n++] = master[i];
    return n;
}
void printLine(int width) {
    for (int i = 0; i < width; i++) cout << '-';
    cout << endl;
}

// Display records table
void displayRecords(const Resident arr[], int size, int maxShow) {
    int show = (size < maxShow) ? size : maxShow;
    printLine(108);
    cout << left
         << setw(8)  << "ID"
         << setw(5)  << "Age"
         << setw(10) << "City"
         << setw(14) << "Transport"
         << setw(10) << "Dist(km)"
         << setw(12) << "EmFactor"
         << setw(8)  << "Days"
         << setw(14) << "TotalEmission"
         << "Age Group" << endl;
    printLine(108);
    for (int i = 0; i < show; i++) {
        cout << left
             << setw(8)  << arr[i].residentID
             << setw(5)  << arr[i].age
             << setw(10) << arr[i].city
             << setw(14) << arr[i].modeOfTransport
             << setw(10) << fixed << setprecision(1) << arr[i].dailyDistance
             << setw(12) << fixed << setprecision(3) << arr[i].carbonEmissionFactor
             << setw(8)  << arr[i].avgDaysPerMonth
             << setw(14) << fixed << setprecision(2) << arr[i].totalEmission
             << arr[i].ageGroup << endl;
    }
    printLine(108);
    if (size > maxShow)
        cout << "  ... (" << size - maxShow << " more records not shown)" << endl;
}
