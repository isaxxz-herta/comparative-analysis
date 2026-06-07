// analysis.cpp
// Carbon emission analysis + Age group report


#include <iostream>
#include <iomanip>
#include <cstring>
#include "analysis.h"
#include "utils.h"

using namespace std;

// Shared constants
static const char *MODES[]      = { "Car","Bus","Bicycle","Walking","School Bus","Carpool" };
static const int   NUM_MODES    = 6;

struct AgeGroupDef {
    const char *displayLabel;   // e.g. "18-25 (University Students)"
    const char *key;            // matches Resident::ageGroup field
    int minAge, maxAge;
};

static const AgeGroupDef GROUPS[] = {
    { "6-17 (Children & Teenagers)",         "Children & Teenagers (6-17)",        6,  17  },
    { "18-25 (University Students)",          "University Students (18-25)",        18, 25  },
    { "26-45 (Working Adults, Early Career)", "Working Adults Early (26-45)",       26, 45  },
    { "46-60 (Working Adults, Late Career)",  "Working Adults Late (46-60)",        46, 60  },
    { "61-100 (Senior Citizens / Retirees)",  "Senior Citizens (61-100)",           61, 100 }
};
static const int NUM_GROUPS = 5;


// CARBON EMISSION ANALYSIS

void runAnalysis(const Resident arr[], int size, const string &label) {
    if (size == 0) { cout << "  [No records to analyse]\n"; return; }

    cout << "[ CARBON EMISSION ANALYSIS  --  " << left << setw(17) << label << " ]" << endl;

    double grandTotal    = 0;
    int    topGroup      = -1;
    double topGroupTotal = -1;

    for (int g = 0; g < NUM_GROUPS; g++) {

        // Gather stats for this age group (per-mode)
        double modeTot[6] = {0};
        int    modeCnt[6] = {0};
        int    groupCount = 0;
        double groupTotal = 0;

        for (int i = 0; i < size; i++) {
            if (strcmp(arr[i].ageGroup, GROUPS[g].key) != 0) continue;
            groupCount++;
            groupTotal += arr[i].totalEmission;
            for (int m = 0; m < NUM_MODES; m++) {
                if (strcmp(arr[i].modeOfTransport, MODES[m]) == 0) {
                    modeCnt[m]++;
                    modeTot[m] += arr[i].totalEmission;
                    break;
                }
            }
        }

        grandTotal += groupTotal;
        if (groupTotal > topGroupTotal) { topGroupTotal = groupTotal; topGroup = g; }

        // Print group header
        cout << "\n  Age Group: " << GROUPS[g].displayLabel << endl;
        printLine(72);

        if (groupCount == 0) {
            cout << "  (No residents in this age group)" << endl;
            printLine(72);
            cout << "  Total Emission for Age Group: 0 kg CO2" << endl;
            continue;
        }

        // Transport mode table
        cout << left
             << setw(20) << "  Mode of Transport"
             << setw(10) << "Count"
             << setw(26) << "Total Emission (kg CO2)"
             << "Average per Resident" << endl;
        printLine(72);

        for (int m = 0; m < NUM_MODES; m++) {
            if (modeCnt[m] == 0) continue;
            double avg = modeTot[m] / modeCnt[m];
            cout << left
                 << setw(20) << ("  " + string(MODES[m]))
                 << setw(10) << modeCnt[m]
                 << setw(26) << fixed << setprecision(2) << modeTot[m]
                 << fixed << setprecision(2) << avg << endl;
        }

        printLine(72);
        cout << "  Total Emission for Age Group : "
             << fixed << setprecision(2) << groupTotal << " kg CO2" << endl;
        cout << "  Residents in Age Group       : " << groupCount << endl;
        cout << "  Average Emission per Resident: "
             << fixed << setprecision(2) << groupTotal / groupCount << " kg CO2" << endl;
    }

    // Grand total summary
    cout << "\n";
    printLine(72);
    cout << "  GRAND TOTAL (all age groups) : "
         << fixed << setprecision(2) << grandTotal << " kg CO2" << endl;
    if (topGroup >= 0)
        cout << "  Highest emitting group       : Age Group "
             << GROUPS[topGroup].displayLabel
             << " (" << fixed << setprecision(2) << topGroupTotal << " kg CO2)" << endl;
    printLine(72);
}


// AGE GROUP REPORT
// Preferred transport + total & avg emission per group

void runAgeGroupReport(const Resident arr[], int size, const string &label) {
    if (size == 0) { cout << "  [No records to analyse]\n"; return; }

    cout << "\n+------------------------------------------------------+" << endl;
    cout << "|        AGE GROUP REPORT  --  " << left << setw(23) << label << " |" << endl;
    cout << "+------------------------------------------------------+" << endl;
    cout << "|  Per age group: Preferred Transport | Total &        |" << endl;
    cout << "|  Average Carbon Emission                             |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    for (int g = 0; g < NUM_GROUPS; g++) {
        double totalEmission = 0;
        int    count         = 0;
        int    modeCnt[6]    = {0};

        for (int i = 0; i < size; i++) {
            if (strcmp(arr[i].ageGroup, GROUPS[g].key) != 0) continue;
            totalEmission += arr[i].totalEmission;
            count++;
            for (int m = 0; m < NUM_MODES; m++) {
                if (strcmp(arr[i].modeOfTransport, MODES[m]) == 0) {
                    modeCnt[m]++; break;
                }
            }
        }

        // Find preferred transport (highest count)
        int bestIdx = -1, bestCount = 0;
        for (int m = 0; m < NUM_MODES; m++)
            if (modeCnt[m] > bestCount) { bestCount = modeCnt[m]; bestIdx = m; }

        double avgEmission = (count > 0) ? totalEmission / count : 0;

        cout << "\n  =====================================" << endl;
        cout << "  Age Group : " << GROUPS[g].displayLabel << endl;
        cout << "  =====================================" << endl;

        if (count == 0) {
            cout << "  Residents           : 0 (no data)" << endl;
            cout << "  Preferred Transport : Nothing Found" << endl;
            cout << "  Total Emission      : 0" << endl;
            cout << "  Average Emission    : 0" << endl;
        } else {
            cout << "  Residents           : " << count << endl;
            cout << "  Preferred Transport : "
                 << (bestIdx >= 0 ? MODES[bestIdx] : "Nothing Found")
                 << (bestIdx >= 0 ? " (" + to_string(bestCount) + " users)" : "")
                 << endl;
            cout << "  Total Emission      : "
                 << fixed << setprecision(2) << totalEmission << " kg CO2" << endl;
            cout << "  Average Emission    : "
                 << fixed << setprecision(6) << avgEmission << " kg CO2 / resident" << endl;

            cout << "\n  Transport breakdown:" << endl;
            for (int m = 0; m < NUM_MODES; m++) {
                if (modeCnt[m] == 0) continue;
                cout << "    " << left << setw(14) << MODES[m]
                     << ": " << modeCnt[m] << " residents";
                if (bestIdx == m) cout << "  <-- preferred";
                cout << endl;
            }
        }
    }

    cout << "\n  =====================================" << endl;
    cout << "  [End of Age Group Report]" << endl;
    cout << "  =====================================" << endl;
}
