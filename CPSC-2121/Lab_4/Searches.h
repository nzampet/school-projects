/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 10/9/22
 * Lab Section: 003
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>

// Linear search algorithm that loops through a vector and if it
// finds an element that matches the target, it will return the index.
// If not, it returns -1.
template <class T>
int linearSearch(std::vector<T> data, T target) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == target) return i;
    }

    return -1;
}

// Binary search algorithm that finds a match in a *sorted* vector.
// It does this by splitting the vector in half and seeing if the target
// is higher or lower then the current index. It will then keep narrowing
// the search until it finds a match or doesn't.
template <class T>
int binarySearch(std::vector<T> data, T target) {
    int low = 0;
    int high = data.size() - 1;
    int middle = (low + high) / 2;

    //Loop to go through each narrowing phase
    while (high - low > 2) {
        if (data[middle] == target) {
            //Found match -> return index
            return middle;
        } else if (data[middle] < target) {
            //Move low if target is greater
            low = middle + 1;
        } else {
            //Move high if target is lower
            high = middle - 1;
        }

        //Re-center middle
        middle = (low + high) / 2;
    }

    if (data[low] == target) return low;
    if (data[high] == target) return high;
    return -1;
}
