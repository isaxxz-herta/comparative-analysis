#pragma once
// sorting.h
// Merge Sort and Quick Sort on Resident arrays
// ascending: true  = smallest first (ASC)
//            false = largest first  (DESC)
// Why direction matters:
// Merge Sort  — stable O(n log n) / O(n) aux regardless of direction.
//               ASC vs DESC only flips one comparison; time barely differs.
// Quick Sort  — uses median-of-three pivot.
//               On RANDOM data (ASC): avg O(n log n), O(log n) stack.
//               On ALREADY-SORTED data (DESC run after ASC):
//               pivot choices degrade -> closer to O(n^2), deeper stack.

#include "resident.h"

// Merge Sort - O(n log n) all cases, O(n) extra heap, stable
void mergeSort(Resident arr[], int left, int right, int key, bool ascending = true);

// Quick Sort - O(n log n) avg, O(n^2) worst, O(log n) stack avg
// Median of three pivot selection
void quickSort(Resident arr[], int low, int high, int key, bool ascending = true);
