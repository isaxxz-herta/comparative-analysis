// menu.cpp
// Menu subsystems, performance analysis, insights

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "menu.h"
#include "globals.h"
#include "utils.h"
#include "experiments.h"
#include "analysis.h"

using namespace std;

// INDIVIDUAL DATASET SUB-MENU

void datasetSubMenu(const char *cityLabel, const char *displayName) {
    Resident work[MAX_SIZE];
    int sz = extractCity(cityLabel, work, MAX_SIZE);

    if (sz == 0) {
        cout << "  [No records found for " << displayName << "]\n";
        return;
    }

    int sub;
    do {
        cout << "" << displayName << " (" <<sz<< " records)" << endl;
        cout << "1. Sorting Experiments (Merge + Quick Sort" << endl;
        cout << "2. Searching Experiments (Linear + Binary)" << endl;
        cout << "3. Carbon Emission Analysis" << endl;
        cout << "4. Age Group Report" << endl;
        cout << "5. Run All Experiments" << endl;
        cout << "6. Display Records" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> sub;

        string lbl(displayName);
        switch (sub) {
            case 1: runSortingExperiments(work, sz, lbl);   break;
            case 2: runSearchingExperiments(work, sz, lbl); break;
            case 3: runAnalysis(work, sz, lbl);             break;
            case 4: runAgeGroupReport(work, sz, lbl);       break;
            case 5:
                runSortingExperiments(work, sz, lbl);
                runSearchingExperiments(work, sz, lbl);
                runAnalysis(work, sz, lbl);
                runAgeGroupReport(work, sz, lbl);
                break;
            case 6:
                cout << "\n  [Records for " << displayName << "]" << endl;
                displayRecords(work, sz);
                break;
            case 0: break;
            default: cout << "  Invalid choice.\n";
        }
    } while (sub != 0);
}

// COMBINED DATASET MENU

void combinedMenu() {
    int sub;
    do {
        cout << "COMBINED - All Datasets (" << masterSize << " records)" << endl;
        cout << "1. Sorting Experiments (Merge + Quick Sort)" << endl;
        cout << "2. Searching Experiments (Linear + Binary)" << endl;
        cout << "3. Carbon Emission Analysis" << endl;
        cout << "4. Age Group Report" << endl;
        cout << "5. Run All Experiments" << endl;
        cout << "6. Display First 20 Records" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> sub;

        const string lbl = "All Datasets (Combined)";
        switch (sub) {
            case 1: runSortingExperiments(master, masterSize, lbl);   break;
            case 2: runSearchingExperiments(master, masterSize, lbl); break;
            case 3: runAnalysis(master, masterSize, lbl);             break;
            case 4: runAgeGroupReport(master, masterSize, lbl);       break;
            case 5:
                runSortingExperiments(master, masterSize, lbl);
                runSearchingExperiments(master, masterSize, lbl);
                runAnalysis(master, masterSize, lbl);
                runAgeGroupReport(master, masterSize, lbl);
                break;
            case 6:
                cout << "\n  [All Records - first 20 shown]" << endl;
                displayRecords(master, masterSize, 20);
                break;
            case 0: break;
            default: cout << "  Invalid choice.\n";
        }
    } while (sub != 0);
}


// INDIVIDUAL DATASET SELECTION MENU

void individualMenu() {
    int sub;
    do {
        cout << "INDIVIDUAL DATASET EXPERIMENTS" << endl;
        cout << "1. Dataset 1 - City A  (" << setw(3) << countA << " records)" << endl;
        cout << "2. Dataset 2 - City B  (" << setw(3) << countB << " records)" << endl;
        cout << "3. Dataset 3 - City C  (" << setw(3) << countC << " records)" << endl;
        cout << "0. Back" << endl;
        cout << "  Enter choice: ";
        cin >> sub;

        switch (sub) {
            case 1: datasetSubMenu("City A", "Dataset 1 (City A)"); break;
            case 2: datasetSubMenu("City B", "Dataset 2 (City B)"); break;
            case 3: datasetSubMenu("City C", "Dataset 3 (City C)"); break;
            case 0: break;
            default: cout << "  Invalid choice.\n";
        }
    } while (sub != 0);
}

// PERFORMANCE ANALYSIS

void performanceAnalysis() {
    cout << "[ PERFORMANCE ANALYSIS  (Array Structure) ]" << endl;

    cout << "\n  Total records loaded : " << masterSize << endl;
    cout << "  Struct size          : " << sizeof(Resident) << " bytes" << endl;
    cout << "  Total memory used    : " << sizeof(Resident) * masterSize
         << " bytes (" << fixed << setprecision(2)
         << (sizeof(Resident) * masterSize / 1024.0) << " KB)" << endl;

    cout << "\n  Sorting Algorithm Comparison:" << endl;
    printLine(82);
    cout << left << setw(20) << "  Algorithm"
         << setw(20) << "Best Case"
         << setw(20) << "Average Case"
         << setw(20) << "Worst Case"
         << "Space" << endl;
    printLine(82);
    cout << left << setw(20) << "  Merge Sort"
         << setw(20) << "O(n log n)"
         << setw(20) << "O(n log n)"
         << setw(20) << "O(n log n)"
         << "O(n)" << endl;
    cout << left << setw(20) << "  Quick Sort"
         << setw(20) << "O(n log n)"
         << setw(20) << "O(n log n)"
         << setw(20) << "O(n^2)"
         << "O(log n)" << endl;
    printLine(82);

    cout << "\n  Searching Algorithm Comparison:" << endl;
    printLine(82);
    cout << left << setw(20) << "  Algorithm"
         << setw(16) << "Data State"
         << setw(20) << "Best Case"
         << setw(20) << "Worst Case"
         << "Space" << endl;
    printLine(82);
    cout << left << setw(20) << "  Linear Search"
         << setw(16) << "Unsorted"
         << setw(20) << "O(1)"
         << setw(20) << "O(n)"
         << "O(1)" << endl;
    cout << left << setw(20) << "  Binary Search"
         << setw(16) << "Sorted"
         << setw(20) << "O(1)"
         << setw(20) << "O(log n)"
         << "O(1)" << endl;
    printLine(82);

    cout << "\n  Array Access Characteristics:" << endl;
    printLine(82);
    cout << left << setw(30) << "  Operation"
         << setw(20) << "Complexity"
         << "Note" << endl;
    printLine(82);
    cout << left << setw(30) << "  Random access (index)"
         << setw(20) << "O(1)"
         << "Contiguous memory, direct indexing" << endl;
    cout << left << setw(30) << "  Insert at end"
         << setw(20) << "O(1)"
         << "If capacity available" << endl;
    cout << left << setw(30) << "  Insert at middle"
         << setw(20) << "O(n)"
         << "Requires shifting elements" << endl;
    cout << left << setw(30) << "  Delete from middle"
         << setw(20) << "O(n)"
         << "Requires shifting elements" << endl;
    printLine(82);
}