/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 11/28/2022
 * Assignment Name: Min-Heap Implementation Using a Vector
 */

#include "minHeap.h"

//Implement the following functions that maintain the heap property
void minHeap::siftUp(int pos) {
    int parent = floor((pos - 1) / 2);
    
    while (pos != 0 && (heap[pos] < heap[parent])) {
        int tmp = heap[pos];
        heap[pos] = heap[parent];
        heap[parent] = tmp;

        pos = parent;
        parent = floor((pos - 1) / 2);
    }
}

void minHeap::siftDown(int pos) {
    int lChild = pos * 2 + 1;
    int rChild = pos * 2 + 2;

    if (rChild < (int)heap.size() &&
        (heap[pos] > heap[lChild] || heap[pos] > heap[rChild])) {
        if (heap[lChild] <= heap[rChild]) {
            int tmp = heap[pos];
            heap[pos] = heap[lChild];
            heap[lChild] = tmp;
            pos = lChild;
        } else {
            int tmp = heap[pos];
            heap[pos] = heap[rChild];
            heap[rChild] = tmp;
            pos = rChild;
        }
    } else if (lChild < (int)heap.size() && heap[pos] > heap[lChild]) {
        int tmp = heap[pos];
        heap[pos] = heap[lChild];
        heap[lChild] = tmp;
        pos = lChild;
    } else return;

    siftDown(pos);
}

//Implement all the following functions
//constructor, Should build the heap from bottom-up
minHeap::minHeap(vector<int> data) {
    for (int val : data) {
        heap.push_back(val);
        siftUp((int)heap.size() - 1);
    }
}

//Insert value into heap
void minHeap::insert(int value) {
    heap.push_back(value);
    siftUp((int)heap.size() - 1);
}

//Removes minimum value
int minHeap::removeMin() {
    if (heap.size() == 0) return -1;

    int tmp = heap[0];
    heap[0] = heap[(int)heap.size() - 1];
    heap[(int)heap.size() - 1] = tmp;
    heap.pop_back();
    siftDown(0);
    return tmp;
}