/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 10/9/22
 * Lab Section: 003
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
#include <cstdlib>

// This is a recursive implementation of merge sort. It will sort a vector
// by splitting the list in half until down to single elements. Then, it
// combines these elements through "merging". This is faster than regular
// sorting because when combining two already sorted vectors you only need
// to compare the next smallest of both vectors.
template <class T>
std::vector<T> mergeSort(std::vector<T> lst) {
    if (lst.size() == 1) return lst; //Base case

    std::vector<T> v1;
    std::vector<T> v2;

    int i = 0; //Split vector into two
    for (; i < lst.size() / 2; i++) v1.push_back(lst[i]);
    for (; i < lst.size(); i++) v2.push_back(lst[i]);

    //Recurse
    v1 = mergeSort(v1);
    v2 = mergeSort(v2);

    //Clear lst to be refilled with the new elements
    lst.clear();

    i = 0;
    int j = 0; //Loop through each newly sorted vector while
    int k = 0; //"merging" as described above
    while (j < v1.size() && k < v2.size()) {
        if (v1[j] <= v2[k]) {
            lst.push_back(v1[j]);
            j++;
        } else {
            lst.push_back(v2[k]);
            k++;
        }
    }

    //Add the remaining part of either list to the new merged vector
    for (; j < v1.size(); j++) lst.push_back(v1[j]);
    for (; k < v2.size(); k++) lst.push_back(v2[k]);

    return lst;
}

//Swaps two input values by reference
template <class T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// This is a helper function for quick sort. We use more parameters with
// references and low and high indexes so we can stay in-place. This
// function randomly picks a pivot value and then sorts everything
// under that value to the left and everything over to the right.
// Then, the partially sorted left and right get called with the same
// function until the base case where there is no elements left to sort.
template <class T>
void quickSortHelper(std::vector<T>& lst, int low, int high) {
    if (low >= high) return; //Base case

    //Pick a random pivot, swap it with the low
    int pivotIndex = std::rand() % (high - low) + low;
    swap(lst[low], lst[pivotIndex]);
    pivotIndex = low;

    //Get our pivot value and sort the list around that pivot
    //We move everything lower then the pivot to the right of it.
    T pivotValue = lst[pivotIndex];
    for (int i = low + 1; i < high + 1; i++) {
        if (lst[i] < pivotValue) {
            pivotIndex++;
            swap(lst[pivotIndex], lst[i]);
        }
    }

    //Move the pivot between the lower and higher values
    swap(lst[low], lst[pivotIndex]);

    //Recurse until the base case
    quickSortHelper(lst, low, pivotIndex - 1);
    quickSortHelper(lst, pivotIndex + 1, high);
}

// This is the main quick sort function. We call the helper function
// that does most of the work. Explanation of working above
template <class T>
std::vector<T> quickSort(std::vector<T> lst) {
    quickSortHelper(lst, 0, lst.size() - 1);
    return lst;
}
