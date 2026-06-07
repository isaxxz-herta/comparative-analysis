#include<bits/stdc++.h>
#include "LinkedList.hpp"
#include "Helper.hpp"

using namespace std;


void CarbonEmisionAnalysis(Linkedlist data) {
    string arr[] = {"Walking", "Bus", "Car", "Carpool", "Bicycle", "School Bus"};

    cout << left;
    cout << "\n" << string(60, '-') << endl;
    cout << setw(18) << "Mode of Transport"
         << setw(8)  << "Count"
         << setw(24) << "Total Emission (kg CO2)"
         << setw(20) << "Average per Resident" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < 6; i++) {
        Value v;
        v.type = STRING;
        v.sVal = arr[i];

        Linkedlist res = data.SearchList(MODE_OF_TRANSPORT, v);

        int    length        = res.getLength();
        double totalEmission = res.totalEmision();
        double avgEmission   = (length > 0) ? totalEmission / length : 0;

		cout << setw(18) << arr[i]
		     << setw(8)  << length
		     << setw(30) << (to_string(totalEmission) + " KG CO2")
		     << setw(35) << (to_string(avgEmission)   + " KG CO2 / resident") << endl;
    }
    cout << string(60, '-') << endl;
}


void AgeGroupCategorizing(Linkedlist &data, int type) {
    string arr[5] = {"Children", "Young Adult", "Working Adult", "Older Working Adult", "Senior"};
    
    
    //linked list search is exclusive
    int lows[5]   = {5,  17, 25, 45, 60};
    int highs[5]  = {18, 26, 46, 61, 101};
    
    cout << "\n==========================================" << endl;
    cout << "Total Emmison "<< data.totalEmision()<<"KG CO2" << endl;
    cout << "============================================" << endl;
	    

    for (int i = 0; i<5; i++) {
        Value low, high;
        low.type = INT;
        high.type = INT;
        low.iVal = lows[i];
        high.iVal = highs[i];

        Linkedlist res = data.BoundedSearchList(AGE, low, high);
        
        cout << "\n========================================" << endl;
	    cout << "Age Group: " << arr[i];
	    cout << " (Age " << lows[i]+1 << " - " << highs[i] - 1 << ")" << endl;
	    cout << "========================================" << endl;
	    
        if(type == 1){
	
	        //res.PrintList();
	
	        string preferredTransport = res.getModeTransport();
	        double totalEmission = res.totalEmision();
	        int length = res.getLength();
	
	        cout<< "Preferred Transport : " << preferredTransport << endl;
	        cout<< "Total Emission      : " << totalEmission <<"KG CO2"<<endl;
	        cout<< "Average Emission    : " << (length > 0 ? totalEmission / length : 0) <<"KG CO2 / Resident"<< endl;
		}

		else if(type ==2){
			CarbonEmisionAnalysis(res);
		}

    }
    cout << "\n========================================" << endl;
	cout << "No Age Group Categorizing"<<endl;
	cout << "========================================" << endl;
    if(type == 2){
    	CarbonEmisionAnalysis(data);

	}
}

// search sorting 

void SortExperiment(Linkedlist &data) {

    AlgoMenu:
        int algo = -1;
        while (algo < 1 || algo > 2) {
            cout << "\nSelect Sorting Algorithm" << endl;
            cout << "1. Merge Sort" << endl;
            cout << "2. Quick Sort" << endl;
            cin >> algo;
        }

    SortMenu:
        int opt = -1;
        while (opt < 1 || opt > 4) {
            cout << "\nSort By" << endl;
            cout << "1. Age" << endl;
            cout << "2. Daily Distance" << endl;
            cout << "3. Carbon Emission" << endl;
            cout << "4. Go Back" << endl;
            cin >> opt;
        }
        if (opt == 4) goto AlgoMenu;

        Field field;
        string fieldName;
        if (opt == 1) { field = AGE;                   fieldName = "Age";             }
        if (opt == 2) { field = DAILY_DISTANCE;         fieldName = "Daily Distance";  }
        if (opt == 3) { field = CARBON_EMISSION_FACTOR; fieldName = "Carbon Emission"; }

    ActionMenu:
        int action = -1;
        while (action < 1 || action > 3) {
            cout << "\nSelect Action" << endl;
            cout << "1. Measure Memory & Time" << endl;
            cout << "2. View Result" << endl;
            cout << "3. Go Back" << endl;
            cin >> action;
        }
        if (action == 3) goto SortMenu;

        if (action == 1) {
            const int RUNS = 1000;

            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < RUNS; i++) {
                if (algo == 1) data.Sort(field);
                if (algo == 2) data.QuickSort(field);
            }
            auto end = chrono::high_resolution_clock::now();

            double timeTaken = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (double)RUNS;
            size_t memUsed   = data.getLength() * sizeof(Node);

            cout << "\n========================================"  << endl;
            cout << "Algorithm  : " << (algo == 1 ? "Merge Sort" : "Quick Sort") << endl;
            cout << "Sorted by  : " << fieldName << endl;
            cout << "Time Taken : " << timeTaken << " ns (avg over " << RUNS << " runs)" << endl;
            cout << "Memory Used: " << memUsed << " bytes" << endl;
            cout << "Total Nodes: " << data.getLength() << endl;
            cout << "========================================" << endl;
            goto ActionMenu;
        }

        if (action == 2) {
            data.PrintList();
            goto ActionMenu;
        }

        return;
}

void SearchExperiment(Linkedlist &data) {
    SearchMenu:
        int opt = -1;
        while(opt < 0 || opt > 3){
            cout << "\nSearch Type" << endl;
            cout << "1. Exact Search" << endl;
            cout << "2. Range Search" << endl;
            cout << "3. Go Back" << endl;
            cin >> opt;
        }

        if(opt == 3) return;

        if(opt == 1){
            int fopt = -1;
            while(fopt < 0 || fopt > 7){
                cout << "\nSearch By" << endl;
                cout << "1. Resident ID" << endl;
                cout << "2. Age" << endl;
                cout << "3. Mode of Transport" << endl;
                cout << "4. Daily Distance" << endl;
                cout << "5. Carbon Emission Factor" << endl;
                cout << "6. Avg Days Per Month" << endl;
                cout << "7. Go Back" << endl;
                cin >> fopt;
            }

            if(fopt == 7) goto SearchMenu;

            Value v;
            Field field;
            string fieldName;

            if(fopt == 1){
                field = RESIDENT_ID;
                fieldName = "Resident ID";
                v.type = STRING;
                cout << "Enter Resident ID: ";
                cin >> v.sVal;
            }
            if(fopt == 2){
                field = AGE;
                fieldName = "Age";
                v.type = INT;
                cout << "Enter Age: ";
                cin >> v.iVal;
            }
            if(fopt == 3){
                field = MODE_OF_TRANSPORT;
                fieldName = "Mode of Transport";
                v.type = STRING;
                cout << "Enter Mode of Transport: ";
                cin.ignore();
                getline(cin, v.sVal);
            }
            if(fopt == 4){
                field = DAILY_DISTANCE;
                fieldName = "Daily Distance";
                v.type = DOUBLE;
                cout << "Enter Daily Distance: ";
                cin >> v.dVal;
            }
            if(fopt == 5){
                field = CARBON_EMISSION_FACTOR;
                fieldName = "Carbon Emission Factor";
                v.type = DOUBLE;
                cout << "Enter Carbon Emission Factor: ";
                cin >> v.dVal;
            }
            if(fopt == 6){
                field = AVG_DAYS_PER_MONTH;
                fieldName = "Avg Days Per Month";
                v.type = INT;
                cout << "Enter Avg Days Per Month: ";
                cin >> v.iVal;
            }

            const int RUNS = 1000;

            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < RUNS; i++)
                data.SearchList(field, v);
            auto end = chrono::high_resolution_clock::now();

            Linkedlist res = data.SearchList(field, v);

            double timeTaken = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (double)RUNS;
            size_t memUsed   = res.getLength() * sizeof(Node);

            cout << "\n========================================"  << endl;
            cout << "Search By  : " << fieldName << endl;
            cout << "Results    : " << res.getLength() << " found" << endl;
            cout << "Time Taken : " << timeTaken << " ns (avg over " << RUNS << " runs)" << endl;
            cout << "Memory Used: " << memUsed << " bytes" << endl;
            cout << "========================================" << endl;

            res.PrintList();
            goto SearchMenu;
        }

        if(opt == 2){
            int fopt = -1;
            while(fopt < 0 || fopt > 5){
                cout << "\nSearch Range By" << endl;
                cout << "1. Age" << endl;
                cout << "2. Daily Distance" << endl;
                cout << "3. Carbon Emission Factor" << endl;
                cout << "4. Avg Days Per Month" << endl;
                cout << "5. Go Back" << endl;
                cin >> fopt;
            }

            if(fopt == 5) goto SearchMenu;

            Value low, high;
            Field field;
            string fieldName;

            if(fopt == 1){
                field = AGE;
                fieldName = "Age";
                low.type = high.type = INT;
                cout << "Enter Min Age: ";
                cin >> low.iVal;
                cout << "Enter Max Age: ";
                cin >> high.iVal;
            }
            if(fopt == 2){
                field = DAILY_DISTANCE;
                fieldName = "Daily Distance";
                low.type = high.type = DOUBLE;
                cout << "Enter Min Distance: ";
                cin >> low.dVal;
                cout << "Enter Max Distance: ";
                cin >> high.dVal;
            }
            if(fopt == 3){
                field = CARBON_EMISSION_FACTOR;
                fieldName = "Carbon Emission Factor";
                low.type = high.type = DOUBLE;
                cout << "Enter Min Emission: ";
                cin >> low.dVal;
                cout << "Enter Max Emission: ";
                cin >> high.dVal;
            }
            if(fopt == 4){
                field = AVG_DAYS_PER_MONTH;
                fieldName = "Avg Days Per Month";
                low.type = high.type = INT;
                cout << "Enter Min Days: ";
                cin >> low.iVal;
                cout << "Enter Max Days: ";
                cin >> high.iVal;
            }

            const int RUNS = 1000;

            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < RUNS; i++)
                data.BoundedSearchList(field, low, high);
            auto end = chrono::high_resolution_clock::now();

            Linkedlist res = data.BoundedSearchList(field, low, high);

            double timeTaken = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (double)RUNS;
            size_t memUsed   = res.getLength() * sizeof(Node);

            cout << "\n========================================"  << endl;
            cout << "Range Search By : " << fieldName << endl;
            cout << "Results         : " << res.getLength() << " found" << endl;
            cout << "Time Taken      : " << timeTaken << " ns (avg over " << RUNS << " runs)" << endl;
            cout << "Memory Used     : " << memUsed << " bytes" << endl;
            cout << "========================================" << endl;

            res.PrintList();
            goto SearchMenu;
        }
}

void CompareEmissions(Linkedlist &cityA, Linkedlist &cityB, Linkedlist &cityC) {
    
    cout << "\n========================================"  << endl;
    cout << "City A" << endl;
    cout << "========================================" << endl;
    AgeGroupCategorizing(cityA, 1);
    CarbonEmisionAnalysis(cityA);

    cout << "\n========================================"  << endl;
    cout << "City B" << endl;
    cout << "========================================" << endl;
    AgeGroupCategorizing(cityB, 1);
    CarbonEmisionAnalysis(cityB);

    cout << "\n========================================"  << endl;
    cout << "City C" << endl;
    cout << "========================================" << endl;
    AgeGroupCategorizing(cityC, 1);
    CarbonEmisionAnalysis(cityC);
}

int menu(){
	MainMenu:
		int opt=-1;
		Linkedlist data;
		while(opt<0 || opt>4){
			cout<<"Select Data"<<endl<<"1. City A"<<endl<<"2. City B"<<endl<<"3. City C"<<endl<<"4. Exit"<<endl;
			cin>>opt;
		}
		if(opt == 1){
			data = readCsv("Data/dataset1-cityA.csv");
		}
		if(opt == 2){
			data = readCsv("Data/dataset2-cityB.csv");
		}
		if(opt == 3){
			data = readCsv("Data/dataset3-cityC.csv");
		}
	
		if(opt == 4){
			return 0;
		}
	
	MenuA:
		opt=-1;
		while(opt<0 || opt>3){
			cout<<"Select Data"<<endl<<"1. Emision Analysis"<<endl<<"2. Sort and Search Experiment"<<endl<<"3. go back"<<endl;
			cin>>opt;
		}
		if(opt == 1){
			goto MenuEmision;
		}
		if(opt == 2){
			goto MenuExperiment;
		}
		if(opt == 3){
			goto MainMenu;
		}


	MenuEmision:
		opt=-1;
		while(opt<0 || opt>4){
			cout<<"Select Data"<<endl<<"1. Age Group analysis"<<endl<<"2. Transport Mode analysis"<<endl<<"3. Compare Accross all dataset"<<endl<<"4. go back"<<endl;
			cin>>opt;
		}
		if(opt == 1){
			AgeGroupCategorizing(data, 1);
			goto MenuEmision;
		}
		if(opt == 2){
			AgeGroupCategorizing(data, 2);
			goto MenuEmision;
		}
		if(opt == 3){
			Linkedlist cityA = readCsv("Data/dataset1-cityA.csv");
    		Linkedlist cityB = readCsv("Data/dataset2-cityB.csv");
    		Linkedlist cityC = readCsv("Data/dataset3-cityC.csv");
    		CompareEmissions(cityA, cityB, cityC);
    		goto MenuEmision;
		}
		if(opt == 4){
			goto MenuA;
		}

	MenuExperiment:
	    opt=-1;
	    while(opt<0 || opt>3){
	        cout << "\nExperiment Menu" << endl;
	        cout << "1. Sort Experiment" << endl;
	        cout << "2. Search Experiment" << endl;
	        cout << "3. Go Back" << endl;
	        cin >> opt;
	    }
	    if(opt == 3){
	        goto MenuA;
	    }

	    ExperimentDataSelect:
	    {
		    int dopt = -1;
		    while(dopt < 1 || dopt > 4){
		        cout << "\nSelect Dataset for Experiment" << endl;
		        cout << "1. Current City (already loaded)" << endl;
		        cout << "2. All Cities Combined"           << endl;
		        cout << "3. Go Back"                       << endl;
		        cin >> dopt;
		    }
		    if(dopt == 3) goto MenuExperiment;

		    Linkedlist experimentData;
		    if(dopt == 1){
		        experimentData = data;
		    }
		    if(dopt == 2){
		        cout << "\nLoading all cities..." << endl;
		        Linkedlist cityA = readCsv("Data/dataset1-cityA.csv");
		        Linkedlist cityB = readCsv("Data/dataset2-cityB.csv");
		        Linkedlist cityC = readCsv("Data/dataset3-cityC.csv");
		        cityA.AppendList(cityB);
		        cityA.AppendList(cityC);
		        experimentData = cityA;
		        cout << "All Cities loaded. Total records: " << experimentData.getLength() << endl;
		    }

		    if(opt == 1){
		        SortExperiment(experimentData);
		    }
		    if(opt == 2){
		        SearchExperiment(experimentData);
		    }
	    }
	    goto MenuExperiment;
}
