#ifndef LinkedList_HPP
#define LinkedList_HPP
#include <bits/stdc++.h>
#include<string>
#include "Helper.hpp"

using namespace std;

struct Node {

    string residentID;
    int age;
    string modeOfTransport;
    double dailyDistance;
    double carbonEmissionFactor;
    int avgDaysPerMonth;

    struct Node* next;

    Node(string residentID, int age, string modeOfTransport, double dailyDistance,
        double carbonEmissionFactor, int avgDaysPerMonth) {
        this->residentID = residentID;
        this->age = age;
        this->modeOfTransport = modeOfTransport;
        this->dailyDistance = dailyDistance;
        this->carbonEmissionFactor = carbonEmissionFactor;
        this->avgDaysPerMonth = avgDaysPerMonth;
        this->next = nullptr;
    }

    Node(const Node& other) {
        this->residentID = other.residentID;
        this->age = other.age;
        this->modeOfTransport = other.modeOfTransport;
        this->dailyDistance = other.dailyDistance;
        this->carbonEmissionFactor = other.carbonEmissionFactor;
        this->avgDaysPerMonth = other.avgDaysPerMonth;
        this->next = nullptr;
    }
};

class Linkedlist {
    Node *head;

public:
    Linkedlist() {
        head = NULL;
    }

    void PrintList();
    void InsertHead(Node* data);
    Linkedlist SearchList(Field field, Value target);
    Linkedlist BoundedSearchList(Field field, Value lower, Value upper);
    Node* split(Node* head);
    Node* merge(Node* first, Node* second, Field field);
    Node* mergeSort(Node* head, Field field);
    int getLength();
    string getModeTransport();
    double totalEmision();
    void Sort(Field field);
    Node* getTail(Node* cur);
	Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd, Field field);
	Node* quickSortHelper(Node* head, Node* end, Field field);
	void QuickSort(Field field);
	void AppendList(const Linkedlist& other);


};

Linkedlist readCsv(string filename, char sep=',') ;


#endif
