#include<bits/stdc++.h>
#include "LinkedList.hpp"

using namespace std;



void Linkedlist::PrintList() {
    Node *temp = head;

    cout << left;

    cout << setw(6)  << "ID"
         << setw(6)  << "Age"
         << setw(12) << "Transport"
         << setw(10) << "Distance"
         << setw(12) << "CO2_Factor"
         << setw(6)  << "Days" << endl;

    cout << string(52, '-') << endl;

    while (temp != nullptr) {
        cout << setw(6)  << temp->residentID
             << setw(6)  << temp->age
             << setw(12) << temp->modeOfTransport
             << setw(10) << temp->dailyDistance
             << setw(12) << temp->carbonEmissionFactor
             << setw(6)  << temp->avgDaysPerMonth
             << endl;

        temp = temp->next;
    }
}

void Linkedlist::InsertHead(Node* data) {
    if (head == NULL) {
        head = data;
        data->next = nullptr;
        return;
    }

    data->next = this->head;
    this->head = data;
}

Linkedlist Linkedlist::SearchList(Field field, Value target) {
    Linkedlist result;
    Node *temp = head;
    string a,b;

    while (temp != nullptr) {

        bool match = false;

        switch (field) {

            case AGE:
                if (temp->age == target.iVal)
                    match = true;
                break;

            case RESIDENT_ID:
                a = temp->residentID;
		        b = target.sVal;
		        transform(a.begin(), a.end(), a.begin(), ::tolower);
		        transform(b.begin(), b.end(), b.begin(), ::tolower);
		        if (a == b) match = true;
                break;

            case DAILY_DISTANCE:
                if (temp->dailyDistance == target.dVal)
                    match = true;
                break;

            case CARBON_EMISSION_FACTOR:
                if (temp->carbonEmissionFactor == target.dVal)
                    match = true;
                break;

            case MODE_OF_TRANSPORT:
		        a = temp->modeOfTransport;
		        b = target.sVal;
		        transform(a.begin(), a.end(), a.begin(), ::tolower);
		        transform(b.begin(), b.end(), b.begin(), ::tolower);
                if (a == b) match = true;
                break;

            case AVG_DAYS_PER_MONTH:
                if (temp->avgDaysPerMonth == target.iVal)
                    match = true;
                break;

            default:
                match = false;
                break;
        }

        if (match) {
            Node *tmp = new Node(*temp);
            result.InsertHead(tmp);
        }

        temp = temp->next;
    }

    return result;
}

Linkedlist Linkedlist::BoundedSearchList(Field field, Value lower, Value upper) {
    Linkedlist result;
    Node *temp = head;

    while (temp != nullptr) {

        bool match = false;

        switch (field) {

            case AGE:
                if (temp->age > lower.iVal && temp->age < upper.iVal)
                    match = true;
                break;

            case DAILY_DISTANCE:
                if (temp->dailyDistance > lower.dVal && temp->dailyDistance < upper.dVal)
                    match = true;
                break;

            case CARBON_EMISSION_FACTOR:
                if (temp->carbonEmissionFactor > lower.dVal && temp->carbonEmissionFactor < upper.dVal)
                    match = true;
                break;

            case AVG_DAYS_PER_MONTH:
                if (temp->avgDaysPerMonth > lower.iVal && temp->avgDaysPerMonth < upper.iVal)
                    match = true;
                break;

            default:
                match = false;
                break;
        }

        if (match) {
            Node *tmp = new Node(*temp);
            result.InsertHead(tmp);
        }

        temp = temp->next;
    }

    return result;
}

//MERGE SORT
Node* Linkedlist::split(Node* head) {
    Node* fast = head;
    Node* slow = head;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;

        if (fast != nullptr) {
            slow = slow->next;
        }
    }

    Node* temp = slow->next;
    slow->next = nullptr;

    return temp;
}

Node* Linkedlist::merge(Node* first, Node* second, Field field) {

    if (first == nullptr) return second;
    if (second == nullptr) return first;

    bool condition = false;

    switch (field) {

        case AGE:
            condition = (first->age < second->age);
            break;

        case DAILY_DISTANCE:
            condition = (first->dailyDistance < second->dailyDistance);
            break;

        case CARBON_EMISSION_FACTOR:
            condition = (first->carbonEmissionFactor < second->carbonEmissionFactor);
            break;

    }

    if (condition) {
        first->next = merge(first->next, second, field);
        return first;
    }
    else {
        second->next = merge(first, second->next, field);
        return second;
    }
}
Node* Linkedlist::mergeSort(Node* head, Field field) {

    if (head == nullptr || head->next == nullptr)
        return head;

    Node* second = split(head);

    head = mergeSort(head, field);
    second = mergeSort(second, field);

    return merge(head, second, field);
}

void Linkedlist::Sort(Field field){
    head = mergeSort(head, field);
}

int Linkedlist::getLength() {
    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    return count;
}


string Linkedlist::getModeTransport(){
	Node* temp = head;
	int count[5] = {0, 0, 0, 0 ,0};
	string arr[] = {"walking", "bus", "car", "carpool", "bicycle"};
	while(temp!=nullptr){
	string s = temp->modeOfTransport;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	
	if (s == "walking") {
		count[0]+=1;
	}
	if (s == "bus") {
		count[1]+=1;
	}
	if (s == "car") {
		count[2]+=1;
	}
	if (s == "carpool") {
		count[3]+=1;
	}
	if (s == "bicycle") {
		count[4]+=1;
	}
	temp = temp->next;
		
	}
	
	int tmp, max = -1;

	for(int i = 0; i<5;i++){
		
		if(count[i]>max){
			tmp = i;
			max = count[i];
		} 
	}
	if(max==0) return "Nothing Found";
	return arr[tmp];
}

double Linkedlist::totalEmision(){
	Node* temp = head;
	double totalEmmision = 0.0;
	while(temp!=nullptr){
		totalEmmision += temp->carbonEmissionFactor*temp->dailyDistance*temp->avgDaysPerMonth;
		
		temp = temp->next;
	}
	
	return totalEmmision;
}

// QUICK SORT
Node* Linkedlist::getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

Node* Linkedlist::partition(Node* head, Node* end, Node** newHead, Node** newEnd, Field field) {
    Node* pivot = end;
    Node* prev  = nullptr;
    Node* cur   = head;
    Node* tail  = pivot;

    *newHead = nullptr;

    while (cur != pivot) {

        bool condition = false;

        switch (field) {
            case AGE:
                condition = (cur->age < pivot->age);
                break;
            case DAILY_DISTANCE:
                condition = (cur->dailyDistance < pivot->dailyDistance);
                break;
            case CARBON_EMISSION_FACTOR:
                condition = (cur->carbonEmissionFactor < pivot->carbonEmissionFactor);
                break;
            default:
                break;
        }

        if (condition) {
            if (*newHead == nullptr)
                *newHead = cur;
            prev = cur;
            cur  = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Node* tmp  = cur->next;
            cur->next  = nullptr;
            tail->next = cur;
            tail       = cur;
            cur        = tmp;
        }
    }

    if (*newHead == nullptr)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

Node* Linkedlist::quickSortHelper(Node* head, Node* end, Field field) {
    if (head == nullptr || head == end)
        return head;

    Node* newHead = nullptr;
    Node* newEnd  = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd, field);

    if (newHead != pivot) {
        Node* tmp = newHead;

        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortHelper(newHead, tmp, field);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortHelper(pivot->next, newEnd, field);

    return newHead;
}

void Linkedlist::QuickSort(Field field) {
    head = quickSortHelper(head, getTail(head), field);
}

void Linkedlist::AppendList(const Linkedlist& other) {
    Node* temp = other.head;
    while (temp != nullptr) {
        Node* tmp = new Node(*temp);
        tmp->next = nullptr;
        if (head == nullptr) {
            head = tmp;
        } else {
            Node* tail = head;
            while (tail->next != nullptr)
                tail = tail->next;
            tail->next = tmp;
        }
        temp = temp->next;
    }
}

Linkedlist readCsv(string filename, char sep) {
    Linkedlist data;

    fstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file make sure data folder is populated!" << endl;
        return data;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {

        stringstream s(line);

        string id;
		int age, days;
        string transport;
        double distance, emission;

        string temp;
        

        // read residentID
        getline(s, temp, sep);
        id = temp;

        // read age
        getline(s, temp, sep);
        age = stoi(temp);

        // read transport
        getline(s, transport, sep);

        // read distance
        getline(s, temp, sep);
        distance = stod(temp);

        // read emission
        getline(s, temp, sep);
        emission = stod(temp);

        // read avg days
        getline(s, temp, sep);
        days = stoi(temp);

        // create node + insert
        Node* newNode = new Node(id, age, transport, distance, emission, days);
        data.InsertHead(newNode);
    }

    return data;
}
