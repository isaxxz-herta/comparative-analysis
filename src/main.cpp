#include <iostream>
#include <string>

#include "LinkedList.hpp" 
#include "globals.h"   
#include "utils.h"
#include "menu.h"
   

using namespace std;

int menu();               
int array_menu() {
    cout << "\n============================================" << endl;
    cout << "  GROUP #39 DSTR - ARRAY IMPLEMENTATION"        << endl;
    cout << "  Urban Carbon Emission Analysis"             << endl;
    cout << "  Sort   : Merge Sort | Quick Sort"           << endl;
    cout << "  Search : Linear (unsorted) | Binary (sorted)" << endl;
    cout << "============================================" << endl;

    countA = loadCSV("Data/dataset1-cityA.csv", "City A");
    countB = loadCSV("Data/dataset2-cityB.csv", "City B");
    countC = loadCSV("Data/dataset3-cityC.csv", "City C");

    cout << "\n[Datasets Loaded]" << endl;
    cout << "  Dataset 1 (City A) : " << countA << " records" << endl;
    cout << "  Dataset 2 (City B) : " << countB << " records" << endl;
    cout << "  Dataset 3 (City C) : " << countC << " records" << endl;
    cout << "  Total              : " << masterSize << " records" << endl;

    int choice;
    do {
        cout << "\n+----------------------------------------------+" << endl;
        cout << "|            MAIN MENU ARRAY PROGRAM           |" << endl;
        cout << "+----------------------------------------------+" << endl;
        cout << "|  1. Individual Dataset Experiments           |" << endl;
        cout << "|     (Search, Sort & Analyse each dataset)    |" << endl;
        cout << "|  2. Combined Dataset Experiments             |" << endl;
        cout << "|     (Search, Sort & Analyse all 3 together)  |" << endl;
        cout << "|  3. Performance Analysis (Array Structure)   |" << endl;
        cout << "|  0. Exit                                     |" << endl;
        cout << "+----------------------------------------------+" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: individualMenu();             break;
            case 2: combinedMenu();               break;
            case 3: performanceAnalysis();        break;
            case 0: cout << "\nGoodbye!\n";       break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

// ============================================================
// INSIGHTS & RECOMMENDATIONS
// ============================================================
void insightsAndRecommendations() {
    cout << "\n╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║          INSIGHTS & RECOMMENDATIONS                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;

    const char *ageGroups[] = {
        "Children & Teenagers (6-17)",
        "University Students (18-25)",
        "Working Adults Early (26-45)",
        "Working Adults Late (46-60)",
        "Senior Citizens (61-100)"
    };
    double totals[5] = {0}; int counts[5] = {0};
    for (int i = 0; i < masterSize; i++)
        for (int g = 0; g < 5; g++)
            if (strcmp(master[i].ageGroup, ageGroups[g]) == 0) {
                totals[g] += master[i].totalEmission; counts[g]++; break;
            }

    // Sort descending for ranking display
    for (int i = 0; i < 4; i++) {
        int maxG = i;
        for (int j = i+1; j < 5; j++) if (totals[j] > totals[maxG]) maxG = j;
        swap(totals[i], totals[maxG]);
        swap(counts[i], counts[maxG]);
        const char *tmp = ageGroups[i]; ageGroups[i] = ageGroups[maxG]; ageGroups[maxG] = tmp;
    }

    cout << "\n  [Emission Ranking by Age Group - All Cities]" << endl;
    printLine(70);
    cout << left << setw(36) << "  Age Group"
         << setw(24) << "Total Emission (kg CO2)"
         << "Residents" << endl;
    printLine(70);
    for (int g = 0; g < 5; g++) {
        if (counts[g] == 0) continue;
        cout << left << setw(36) << ("  " + string(ageGroups[g]))
             << setw(24) << fixed << setprecision(2) << totals[g]
             << counts[g] << endl;
    }
    printLine(70);

    cout << "\n  [Recommendations for City Planners]" << endl;
    printLine(70);
    cout << "  1. \"" << ageGroups[0] << "\" contributes the most emissions.\n";
    cout << "     -> Prioritise carpooling lanes and incentivise EV adoption.\n";
    cout << "  2. Bicycle and Walking produce ZERO CO2 emissions.\n";
    cout << "     -> Invest in cycling infrastructure and pedestrian zones.\n";
    cout << "  3. School Bus and Bus have the lowest emission factors.\n";
    cout << "     -> Increase public transit frequency to attract car users.\n";
    cout << "  4. University towns (City B) show high active-transport usage.\n";
    cout << "     -> Replicate university-area policies city-wide.\n";
    printLine(70);

cout << "\n  [Algorithm Recommendation for this dataset]" << endl;
    printLine(70);
    cout << "  Dataset size: " << masterSize << " records\n";
    
    cout << "\n  --- Array Perspective ---" << endl;
    cout << "  - Sorting  : Quick Sort is faster in practice (low overhead).\n";
    cout << "               Merge Sort guarantees O(n log n) worst case.\n";
    cout << "  - Searching: Binary Search takes ~log2(" << masterSize << ") = "
         << (int)(log2(masterSize) + 1) << " steps after sorting.\n";
    
    cout << "\n  --- Linked List Perspective ---" << endl;
    cout << "  - Sorting  : Merge Sort is IDEAL (no extra space, stable).\n";
    cout << "               Quick Sort is possible but harder to implement.\n";
    cout << "  - Searching: Linear Search ONLY (O(n)). Binary search is\n";
    cout << "               INEFFICIENT due to lack of random access (O(n log n)).\n";
    printLine(70);
}

void masterMenu() {
    
    while (true) {

        int structChoice = -1;
        cout << "\nSelect Data Structure for Analysis:" << endl;
        cout << "1. Linked List Implementation" << endl;
        cout << "2. Array Implementation" << endl;
        cout << "3. Get Insight"<<endl;
        cout << "4. Go Back" << endl;
        cout << "Enter choice: ";
        cin >> structChoice;

        if (structChoice == 4) continue;

        if (structChoice == 1) {
            cout << "\n--- Transitioning to Linked List Module ---" << endl;
            menu(); 
        } 
        else if (structChoice == 2) {

            cout << "\n--- Transitioning to Array Module ---" << endl;
            
            array_menu(); 
        }
        
        else if (structChoice == 3) {

            
            insightsAndRecommendations(); 
        }
    }
}

int main() {
    masterMenu();
    return 0;
}
