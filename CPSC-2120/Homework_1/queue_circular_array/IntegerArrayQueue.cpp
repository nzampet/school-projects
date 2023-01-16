#include "IntegerArrayQueue.h"

//Function descriptions in .h file

bool IntegerArrayQueue::enqueue(int value) {
    //Check if full
    if ((back + 2) % size == front) {
        return false;
    }

    //Increment back
    back++;
    if (back >= size) back = 0;

    //Add value
    array[back] = value;
    return true;
}

int IntegerArrayQueue::dequeue() {
    //Check if empty
    if ((back + 1) % size == front) { 
        return 0;
    }

    //Store return value
    int ret = array[front];

    //Increment front
    front++;
    if (front >= size) front = 0;

    return ret;
}