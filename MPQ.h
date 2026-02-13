//
//  MPQ.h
//  cs300_hw2
//
//  Created by Zeynep Uzun on 2.12.2025.
//

#ifndef _MPQ_H
#define _MPQ_H

#include <iostream>
using namespace std;

template <class Comparable>
class MPQ {
private:
    // each item has a value and a label
    struct MPQObject {
        Comparable value;
        int label;
        MPQObject() : value(), label(0) {} // default constructor
        MPQObject(Comparable val, int l) : value(val), label(l) {} // parametric constructor
    };
    
    MPQObject * Heap; // heap array
    int * Location; // array to map label and index
    int capacity;
    int size;
    void percolateDown(int hole);
public:
    MPQ(int labels); // constructor
    ~MPQ(); // destructor
    void insert(Comparable value, int label);
    Comparable Remove(int label);
    Comparable GetMax() const;
    bool IsEmpty() const;
};

template <class Comparable>
MPQ<Comparable>::MPQ(int labels) {
    capacity = labels + 1; // added 1 because heap is 1-indexed
    size = 0; // initial size is 0

    Heap = new MPQObject[capacity];
    Location = new int[capacity];

    // initialize Location to 0
    for (int i = 0; i < capacity; i++)
        Location[i] = 0;
}

template <class Comparable>
// destructor function
MPQ<Comparable>::~MPQ() {
    delete [] Heap;
    delete [] Location;
}

template <class Comparable> // checks whether heap is empty or not
bool MPQ<Comparable>::IsEmpty() const {
    return (size == 0);
}

// keeping maxheap by moving element down
template <class Comparable>
void MPQ<Comparable>::percolateDown(int hole) {
    int child;
    MPQObject tmp = Heap[hole]; // saving the item to create a hole
    
    // loop while hole has at least one child
    for (; hole * 2 <= size; hole = child) {
        child = hole * 2;
        
        // checking if right child exists and is greater than the left
        if (child != size && Heap[child + 1].value > Heap[child].value) {
            child++;
        }
        
        // if the child is greater than temp
        if (Heap[child].value > tmp.value) {
            Heap[hole] = Heap[child]; // move child up
            Location[Heap[hole].label] = hole;
        } else {
            break;
        }
    }
    
    Heap[hole] = tmp;
    Location[Heap[hole].label] = hole;
}

template <class Comparable>
void MPQ<Comparable>::insert(Comparable value, int label) {
    size++;
    int hole = size; // incremented size and created a hole at the end
    Location[label] = hole;
    Heap[hole] = MPQObject(value, label);
    MPQObject tmp = Heap[hole];
    
    // while hole is not root and parent is smaller
    while (hole > 1 && tmp.value > Heap[hole / 2].value) {
        Heap[hole] = Heap[hole / 2]; // move parent down
        Location[Heap[hole].label] = hole; // updating Location array
        hole = hole / 2; // move hole up
    }
    
    Heap[hole] = tmp;
    Location[tmp.label] = hole;
}

// return maximum value
template <class Comparable>
Comparable MPQ<Comparable>::GetMax() const {
    if (IsEmpty())
        return Comparable();
    return Heap[1].value;  // since root of max-heap has maximum value
}

// remove item with given label
template <class Comparable>
Comparable MPQ<Comparable>::Remove(int label) {
    int idx = Location[label]; // finding the location
    if (idx == 0) {
        return Comparable(); // item not found
    }

    Comparable removedVal = Heap[idx].value;

    // replace removed item with last item in heap
    Heap[idx] = Heap[size];
    Location[Heap[idx].label] = idx;

    size--;
    Location[label] = 0; // since removed, updating location
    // checking if moved item should percolate up or down
    if (idx > 1 && Heap[idx].value > Heap[idx / 2].value) {
        // if larger than parent, percolate up
        int hole = idx;
        MPQObject tmp = Heap[hole];
        
        while (hole > 1 && tmp.value > Heap[hole / 2].value) {
            Heap[hole] = Heap[hole / 2];
            Location[Heap[hole].label] = hole;
            hole = hole / 2;
        }
        
        Heap[hole] = tmp;
        Location[tmp.label] = hole;
    }
    else {
        // moved item should percolate down
        percolateDown(idx);
    }

    return removedVal;
}

#endif
