// experiments.cpp
// Timed experiment runners for sorting and searching

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <algorithm>
#include "experiments.h"
#include "sorting.h"
#include "searching.h"
#include "utils.h"
#include "globals.h"

using namespace std;
using namespace chrono;

// Reverse an array in-place
static void reverseArray(Resident arr[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--)
        swap(arr[i], arr[j]);
}

// Print full record table with row numbers
static void displayAllRecords(const Resident arr[], int size,
                               const string &title) {
    cout << "\n  " << title << "  (" << size << " records)" << endl;
    printLine(116);
    cout << left
         << setw(6)  << "  No"
         << setw(8)  << "ID"
         << setw(5)  << "Age"
         << setw(10) << "City"
         << setw(14) << "Transport"
         << setw(10) << "Dist(km)"
         << setw(12) << "EmFactor"
         << setw(8)  << "Days"
         << setw(14) << "Emission"
         << "Age Group" << endl;
    printLine(116);
    for (int i = 0; i < size; i++) {
        cout << left
             << setw(6)  << ("  " + to_string(i + 1))
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
    printLine(116);
    cout << "  Total: " << size << " records displayed." << endl;
}

// Preview sub-menu for one sort key (age, distance, or emission)
static void previewSubMenu(const Resident ascArr[], const Resident descArr[],
                           int size, const string &keyShort) {
    const int W = 51;

    auto row = [&](const string &content) {
        string padded = content;
        if ((int)padded.size() < W)
            padded += string(W - padded.size(), ' ');
        else
            padded = padded.substr(0, W);
        cout << "  |" << padded << "|" << endl;
    };

    string border(W, '-');
    string line = "  +" + border + "+";

    int choice;
    do {
        string recStr = to_string(size);
        cout << "\n" << line << endl;
        row("  Preview Table  --  Sort by " + keyShort);
        cout << line << endl;
        row("  1. Show Ascending  table (" + recStr + " records)");
        row("  2. Show Descending table (" + recStr + " records)");
        row("  3. Show Both  (Ascending then Descending)");
        row("  0. Skip");
        cout << line << endl;
        cout << "  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllRecords(ascArr, size,
                    "[ ASCENDING  by " + keyShort + " -- Merge Sort ]");
                break;
            case 2:
                displayAllRecords(descArr, size,
                    "[ DESCENDING by " + keyShort + " -- Merge Sort ]");
                break;
            case 3:
                displayAllRecords(ascArr, size,
                    "[ ASCENDING  by " + keyShort + " -- Merge Sort ]");
                displayAllRecords(descArr, size,
                    "[ DESCENDING by " + keyShort + " -- Merge Sort ]");
                break;
            case 0:
                cout << "  [Skipping preview for " << keyShort << "]" << endl;
                break;
            default:
                cout << "  Invalid choice. Please enter 0-3." << endl;
        }
    } while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
}

// SORTING EXPERIMENTS

void runSortingExperiments(Resident arr[], int size, const string &label) {
    if (size == 0) { cout << "  [No records to sort]\n"; return; }

    cout << "\n+------------------------------------------------------+" << endl;
    cout << "|        SORTING EXPERIMENTS  --  " << left << setw(20) << label << " |" << endl;
    cout << "+------------------------------------------------------+" << endl;
    cout << "|  Algorithms : Merge Sort  |  Quick Sort              |" << endl;
    cout << "|  Sort Keys  : Age  |  Daily Distance  |  Total Emis. |" << endl;
    cout << "|  Order      : Ascending  |  Descending               |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    const string keyNames[] = {"Age", "Daily Distance (km)", "Total Emission (kg CO2)"};
    const string keyShort[] = {"Age", "Daily Distance", "Total Emission"};

    Resident *ascArr  = new Resident[size];
    Resident *descArr = new Resident[size];
    Resident *qsAsc   = new Resident[size];
    Resident *qsDesc  = new Resident[size];

    for (int key = 0; key < 3; key++) {

        // Timing table
        cout << "\n════════════════════════════════════════════════════════" << endl;
        cout << "  Sort Key: " << keyNames[key] << endl;
        cout << "════════════════════════════════════════════════════════" << endl;

        printLine(80);
        cout << left
             << setw(18) << "  Algorithm"
             << setw(14) << "Order"
             << setw(22) << "Time (microseconds)"
             << setw(10) << "Records"
             << "Complexity" << endl;
        printLine(80);

        // Merge Sort Ascending
        memcpy(ascArr, arr, size * sizeof(Resident));
        auto t1 = high_resolution_clock::now();
        mergeSort(ascArr, 0, size - 1, key);
        auto t2 = high_resolution_clock::now();
        long long msAscTime = duration_cast<microseconds>(t2 - t1).count();

        cout << left << setw(18) << "  Merge Sort"
             << setw(14) << "Ascending"
             << setw(22) << msAscTime
             << setw(10) << size
             << "O(n log n) all cases" << endl;

        // Merge Sort Descending
        memcpy(descArr, ascArr, size * sizeof(Resident));
        auto t3 = high_resolution_clock::now();
        reverseArray(descArr, size);
        auto t4 = high_resolution_clock::now();
        long long msDescTime = msAscTime + duration_cast<microseconds>(t4 - t3).count();

        cout << left << setw(18) << "  Merge Sort"
             << setw(14) << "Descending"
             << setw(22) << msDescTime
             << setw(10) << size
             << "O(n log n) all cases" << endl;

        printLine(80);

        // Quick Sort Ascending
        memcpy(qsAsc, arr, size * sizeof(Resident));
        auto t5 = high_resolution_clock::now();
        quickSort(qsAsc, 0, size - 1, key);
        auto t6 = high_resolution_clock::now();
        long long qsAscTime = duration_cast<microseconds>(t6 - t5).count();

        cout << left << setw(18) << "  Quick Sort"
             << setw(14) << "Ascending"
             << setw(22) << qsAscTime
             << setw(10) << size
             << "O(n log n) avg / O(n^2) worst" << endl;

        // Quick Sort Descending
        memcpy(qsDesc, qsAsc, size * sizeof(Resident));
        auto t7 = high_resolution_clock::now();
        reverseArray(qsDesc, size);
        auto t8 = high_resolution_clock::now();
        long long qsDescTime = qsAscTime + duration_cast<microseconds>(t8 - t7).count();

        cout << left << setw(18) << "  Quick Sort"
             << setw(14) << "Descending"
             << setw(22) << qsDescTime
             << setw(10) << size
             << "O(n log n) avg / O(n^2) worst" << endl;

        printLine(80);
        cout << "  Space: Merge Sort O(n) extra | Quick Sort O(log n) stack" << endl;

        long long fastest = min(msAscTime, qsAscTime);
        if (fastest == msAscTime)
            cout << "  >> Merge Sort was fastest for " << keyShort[key]
                 << " (" << msAscTime << " us)" << endl;
        else
            cout << "  >> Quick Sort was fastest for " << keyShort[key]
                 << " (" << qsAscTime << " us)" << endl;

        // Preview sub-menu
        previewSubMenu(ascArr, descArr, size, keyShort[key]);
    }

    delete[] ascArr;
    delete[] descArr;
    delete[] qsAsc;
    delete[] qsDesc;
}

// SEARCHING EXPERIMENTS (interactive, user-driven)

// Display a subset of records by index list 
static void displayResults(const Resident arr[], const int results[], int count,
                           const string &title) {
    if (count == 0) {
        cout << "  [No matching records found]" << endl;
        return;
    }
    cout << "\n  " << title << "  (" << count << " records)" << endl;
    printLine(116);
    cout << left
         << setw(6)  << "  No"
         << setw(8)  << "ID"
         << setw(5)  << "Age"
         << setw(10) << "City"
         << setw(14) << "Transport"
         << setw(10) << "Dist(km)"
         << setw(12) << "EmFactor"
         << setw(8)  << "Days"
         << setw(14) << "Emission"
         << "Age Group" << endl;
    printLine(116);
    for (int i = 0; i < count; i++) {
        const Resident &r = arr[results[i]];
        cout << left
             << setw(6)  << ("  " + to_string(i + 1))
             << setw(8)  << r.residentID
             << setw(5)  << r.age
             << setw(10) << r.city
             << setw(14) << r.modeOfTransport
             << setw(10) << fixed << setprecision(1) << r.dailyDistance
             << setw(12) << fixed << setprecision(3) << r.carbonEmissionFactor
             << setw(8)  << r.avgDaysPerMonth
             << setw(14) << fixed << setprecision(2) << r.totalEmission
             << r.ageGroup << endl;
    }
    printLine(116);
    cout << "  Total: " << count << " records found." << endl;
}

// Ask user if they want to view the result table
static void askShowResults(const Resident arr[], const int results[],
                           int count, const string &title) {
    if (count == 0) return;
    cout << "\n  Show result table? (1 = Yes / 0 = No): ";
    int show; cin >> show;
    if (show == 1)
        displayResults(arr, results, count, title);
}

// Prompt for range input for numerical fields
static void getRange(const string &fieldName, const string &unit,
                     double &minVal, double &maxVal) {
    cout << "  Enter minimum " << fieldName;
    if (!unit.empty()) cout << " (" << unit << ")";
    cout << ": ";
    cin >> minVal;
    cout << "  Enter maximum " << fieldName;
    if (!unit.empty()) cout << " (" << unit << ")";
    cout << ": ";
    cin >> maxVal;
    if (minVal > maxVal) swap(minVal, maxVal);
}

// Show options for a text field
static void showOptions(const string &field, const string options[], int n) {
    cout << "  Available " << field << "s:" << endl;
    for (int i = 0; i < n; i++)
        cout << "    [" << (i + 1) << "] " << options[i] << endl;
}

// Print search timing comparison row
static void printSearchTiming(const string &algo, const string &dataState,
                               int found, long long us) {
    cout << left
         << setw(22) << ("  " + algo)
         << setw(16) << dataState
         << setw(12) << found
         << us << " us" << endl;
}

void runSearchingExperiments(Resident arr[], int size, const string &label) {
    if (size == 0) { cout << "  [No records to search]\n"; return; }

    cout << "\n+------------------------------------------------------+" << endl;
    cout << "|       SEARCHING EXPERIMENTS  --  " << left << setw(19) << label << " |" << endl;
    cout << "+------------------------------------------------------+" << endl;
    cout << "|  Numerical → Range Search  (min to max)              |" << endl;
    cout << "|  Text      → Exact Search  (match value)             |" << endl;
    cout << "|  Unsorted  → Linear Search                           |" << endl;
    cout << "|  Sorted    → Binary Search (numerical only)          |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    const int W = 51;
    auto row = [&](const string &content) {
        string p = content;
        if ((int)p.size() < W) p += string(W - p.size(), ' ');
        else p = p.substr(0, W);
        cout << "  |" << p << "|" << endl;
    };
    string border(W, '-');
    string line = "  +" + border + "+";

    int results[MAX_SIZE];
    int field;

    do {
        cout << "\n" << line << endl;
        row("  Select field to search:");
        cout << line << endl;
        row("  [ Numerical (Range Search) ]");
        row("  1. Age");
        row("  2. Daily Distance (km)");
        row("  3. Carbon Emission Factor (kg CO2/km)");
        row("  4. Avg Days Per Month");
        row("  5. Total Emission (kg CO2)");
        cout << line << endl;
        row("  [ Text (Exact Search) ]");
        row("  6. Resident ID");
        row("  7. Mode of Transport");
        row("  8. City");
        row("  9. Age Group");
        cout << line << endl;
        row("  0. Back");
        cout << line << endl;
        cout << "  Enter choice: ";
        cin >> field;
        if (field == 0) break;

        int linFound = 0, binFound = 0;
        long long linTime = 0, binTime = 0;
        double minVal = 0, maxVal = 0;
        string query;
        string fieldName;

        // NUMERICAL RANGE fields
        if (field >= 1 && field <= 5) {

            int sortKey = -1;
            string unit;

            if      (field == 1) { fieldName = "Age";                   unit = "years";      sortKey = 0; }
            else if (field == 2) { fieldName = "Daily Distance";         unit = "km";         sortKey = 1; }
            else if (field == 3) { fieldName = "Carbon Emission Factor"; unit = "kg CO2/km";  sortKey = -1; }
            else if (field == 4) { fieldName = "Avg Days Per Month";     unit = "days";       sortKey = -1; }
            else if (field == 5) { fieldName = "Total Emission";         unit = "kg CO2";     sortKey = 2; }

            cout << "\n  [Range Search for " << fieldName << "]" << endl;
            getRange(fieldName, unit, minVal, maxVal);

            // Linear Search on unsorted data 
            auto t1 = high_resolution_clock::now();
            if      (field == 1) linFound = linearRangeAge      (arr, size, minVal, maxVal, results, MAX_SIZE);
            else if (field == 2) linFound = linearRangeDist     (arr, size, minVal, maxVal, results, MAX_SIZE);
            else if (field == 3) linFound = linearRangeEmFactor (arr, size, minVal, maxVal, results, MAX_SIZE);
            else if (field == 4) linFound = linearRangeDays     (arr, size, minVal, maxVal, results, MAX_SIZE);
            else if (field == 5) linFound = linearRangeEmission (arr, size, minVal, maxVal, results, MAX_SIZE);
            auto t2 = high_resolution_clock::now();
            linTime = duration_cast<microseconds>(t2 - t1).count();

            // Save linear results for display (unsorted order)
            int linResults[MAX_SIZE];
            memcpy(linResults, results, linFound * sizeof(int));

            // Binary Search on sorted data
            int binResults[MAX_SIZE];
            Resident *sorted = nullptr;

            if (sortKey >= 0) {
                sorted = new Resident[size];
                memcpy(sorted, arr, size * sizeof(Resident));
                mergeSort(sorted, 0, size - 1, sortKey);

                auto t3 = high_resolution_clock::now();
                binFound = binaryRangeSearch(sorted, size, sortKey, minVal, maxVal, binResults, MAX_SIZE);
                auto t4 = high_resolution_clock::now();
                binTime = duration_cast<microseconds>(t4 - t3).count();
            }

            // Timing table
            cout << "\n  [Search Results for " << fieldName
                 << " in range [" << minVal << " , " << maxVal << "]]" << endl;
            printLine(64);
            cout << left
                 << setw(22) << "  Algorithm"
                 << setw(16) << "Data State"
                 << setw(12) << "Matches"
                 << "Time" << endl;
            printLine(64);
            printSearchTiming("Linear Search", "Unsorted", linFound, linTime);
            if (sortKey >= 0)
                printSearchTiming("Binary Search", "Sorted", binFound, binTime);
            else
                cout << "  (Binary Search not available for this field — no sort key)" << endl;
            printLine(64);

            if (sortKey >= 0) {
                if (linTime <= binTime)
                    cout << "  >> Linear Search was faster (" << linTime << " us)" << endl;
                else
                    cout << "  >> Binary Search was faster (" << binTime << " us)" << endl;
            }

            // Show results
            if (linFound > 0) {
                cout << "\n  Show which results?" << endl;
                cout << "  1. Linear Search results (unsorted order)" << endl;
                if (sortKey >= 0)
                    cout << "  2. Binary Search results (sorted order)" << endl;
                cout << "  3. Both" << endl;
                cout << "  0. Skip" << endl;
                cout << "  Enter choice: ";
                int showChoice; cin >> showChoice;

                if (showChoice == 1 || showChoice == 3)
                    displayResults(arr, linResults, linFound,
                        "Linear Search Results  [" + fieldName + " : " +
                        to_string((int)minVal) + " - " + to_string((int)maxVal) + "]");

                if (sortKey >= 0 && (showChoice == 2 || showChoice == 3) && sorted)
                    displayResults(sorted, binResults, binFound,
                        "Binary Search Results  [" + fieldName + " : " +
                        to_string((int)minVal) + " - " + to_string((int)maxVal) + "]  (sorted)");
            } else {
                cout << "  [No records found in that range]" << endl;
            }

            if (sorted) delete[] sorted;
        }

        // Text exact match fields
        else if (field >= 6 && field <= 9) {
            if (field == 6) {
                fieldName = "Resident ID";
                cout << "\n  Enter Resident ID to search: ";
                cin >> query;
            }
            else if (field == 7) {
                fieldName = "Mode of Transport";
                const string modes[] = {"Car","Bus","Bicycle","Walking","School Bus","Carpool"};
                showOptions("Mode of Transport", modes, 6);
                cout << "  Enter mode: ";
                cin.ignore();
                getline(cin, query);
            }
            else if (field == 8) {
                fieldName = "City";
                const string cities[] = {"City A", "City B", "City C"};
                showOptions("City", cities, 3);
                cout << "  Enter city: ";
                cin.ignore();
                getline(cin, query);
            }
            else if (field == 9) {
                fieldName = "Age Group";
                const string groups[] = {
                    "Children & Teenagers (6-17)",
                    "University Students (18-25)",
                    "Working Adults Early (26-45)",
                    "Working Adults Late (46-60)",
                    "Senior Citizens (61-100)"
                };
                showOptions("Age Group", groups, 5);
                cout << "  Enter age group (copy exactly): ";
                cin.ignore();
                getline(cin, query);
            }

            cout << "\n  [Exact Search for " << fieldName << " = \"" << query << "\"]" << endl;

            auto t1 = high_resolution_clock::now();
            if      (field == 6) linFound = linearSearchByID      (arr, size, query, results, MAX_SIZE);
            else if (field == 7) linFound = linearSearchByMode    (arr, size, query, results, MAX_SIZE);
            else if (field == 8) linFound = linearSearchByCity    (arr, size, query, results, MAX_SIZE);
            else if (field == 9) linFound = linearSearchByAgeGroup(arr, size, query, results, MAX_SIZE);
            auto t2 = high_resolution_clock::now();
            linTime = duration_cast<microseconds>(t2 - t1).count();

            int linResults[MAX_SIZE];
            memcpy(linResults, results, linFound * sizeof(int));

            printLine(64);
            cout << left
                 << setw(22) << "  Algorithm"
                 << setw(16) << "Data State"
                 << setw(12) << "Matches"
                 << "Time" << endl;
            printLine(64);
            printSearchTiming("Linear Search", "Unsorted", linFound, linTime);
            cout << "  (Binary Search not applicable — text fields use exact linear match)" << endl;
            printLine(64);

            if (linFound > 0) {
                askShowResults(arr, linResults, linFound,
                    "Results  [" + fieldName + " = \"" + query + "\"]");
            } else {
                cout << "  [No matching records found for \"" << query << "\"]" << endl;
            }
        }
        else {
            cout << "  Invalid choice." << endl;
        }

        cout << "\n  Search again? (1 = Yes / 0 = No): ";
        int again; cin >> again;
        if (again != 1) break;

    } while (true);
}

