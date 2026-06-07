
// sorting.cpp
// Merge Sort and Quick Sort — supports ASC and DESC order

#include <algorithm>   
#include "sorting.h"
#include "utils.h"    

using namespace std;

// Merge Sort algorithm

static void mergeArrays(Resident arr[], int left, int mid, int right,
                        int key, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Resident *L = new Resident[n1];
    Resident *R = new Resident[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool takeLeft = ascending ? (getKey(L[i], key) <= getKey(R[j], key))
                                  : (getKey(L[i], key) >= getKey(R[j], key));
        if (takeLeft) arr[k++] = L[i++];
        else          arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Resident arr[], int left, int right, int key, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left,    mid,   key, ascending);
        mergeSort(arr, mid + 1, right, key, ascending);
        mergeArrays(arr, left, mid, right, key, ascending);
    }
}

// Quick Sort algorithm

static int partition(Resident arr[], int low, int high, int key, bool ascending) {
    int mid = low + (high - low) / 2;

    if (ascending) {
        if (getKey(arr[mid],  key) < getKey(arr[low],  key)) swap(arr[low],  arr[mid]);
        if (getKey(arr[high], key) < getKey(arr[low],  key)) swap(arr[low],  arr[high]);
        if (getKey(arr[mid],  key) < getKey(arr[high], key)) swap(arr[mid],  arr[high]);
    } else {
        if (getKey(arr[mid],  key) > getKey(arr[low],  key)) swap(arr[low],  arr[mid]);
        if (getKey(arr[high], key) > getKey(arr[low],  key)) swap(arr[low],  arr[high]);
        if (getKey(arr[mid],  key) > getKey(arr[high], key)) swap(arr[mid],  arr[high]);
    }

    double pivot = getKey(arr[high], key);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool condition = ascending ? (getKey(arr[j], key) <= pivot)
                                   : (getKey(arr[j], key) >= pivot);
        if (condition) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Resident arr[], int low, int high, int key, bool ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, key, ascending);
        quickSort(arr, low,    pi - 1, key, ascending);
        quickSort(arr, pi + 1, high,   key, ascending);
    }
}
