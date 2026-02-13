//
//  main.cpp
//  cs300_hw2
//
//  Created by Zeynep Uzun on 2.12.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "MPQ.h"
using namespace std;

struct Building {
    int left;
    int height;
    int right;
    int id;
    
    Building(int l, int h, int r, int building_id) : left(l), height(h), right(r), id(building_id) {}
};

// coordinates of the buildings, height represents y axis
struct Boundaries {
    int xCoord;
    int building_id;
    bool isStart; // is it the starting point of the building or not
    int height;
    
    Boundaries(int x_coord, int b_id, bool start, int h)
        : xCoord(x_coord), building_id(b_id), isStart(start), height(h) {}
};

// compares the x coordinates of two boundaries, if x is same process left sides first
bool isSmaller(const Boundaries & a, const Boundaries & b) {
    if (a.xCoord != b.xCoord) {
        return a.xCoord < b.xCoord;
    }
    // if coordinates are the same, process START before END
    if (a.isStart != b.isStart) {
        return a.isStart;
    }
    // if both are starts, higher height first
    if (a.isStart == true) {
        return a.height > b.height;
    }
    // if both are ends, lower height first
    return a.height < b.height;
}

// modified it to work with a vector and 0-based indexing
void percolateDown(vector<Boundaries> & arr, int hole, int size) {
    int child;
    Boundaries tmp = arr[hole]; // creating a "hole"
    
    // iterating while the hole has at least one child
    for (; hole * 2 + 1 < size; hole = child) {
        child = hole * 2 + 1;
        
        // if right child exists and is larger than left child
        if (child != size - 1 && isSmaller(arr[child], arr[child + 1]))
            // select the larger child
            child++;
        
        // if the child is larger than tmp, move child up
        if (isSmaller(tmp, arr[child]))
            arr[hole] = arr[child];
        else
            break;
    }
    arr[hole] = tmp;
}

// sorting them into ascending order using x coordinates
void heapSort(vector<Boundaries> & arr) {
    int currentSize = arr.size();
    
    // buildHeap function from the slides
    for (int i = currentSize / 2 - 1; i >= 0; i--) {
        percolateDown(arr, i, currentSize);
    }
    
    // swapping the max element with the end
    for (int i = currentSize - 1; i > 0; i--) {
        Boundaries tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        
        percolateDown(arr, 0, i);
    }
}

int main() {
    // reading from the file input.txt
    ifstream read("input.txt");
    int count;
    
    // the first line of the input indicates how many buildings there are
    read >> count;
    
    vector<Building> buildings;
    vector<Boundaries> boundaries;
    
    for (int i = 0; i < count; i++) {
        int left, height, right;
        // each line will indicate the x coordinate of the left side, y coordinate (height) and x coordinate of the right side
        read >> left >> height >> right;
        
        buildings.push_back(Building(left, height, right, i));
        
        // putting all of the x coordinates of the left and right sides in a separate array
        boundaries.push_back(Boundaries(left, i, true, height));
        boundaries.push_back(Boundaries(right, i, false, height));
    }
    
    // sorting them into ascending order of the x coordinates
    heapSort(boundaries);
    MPQ<int> MPQ(count);
    int currentMax = 0;
    
    // print 0 0 if the first building does not start at 0
    if (!boundaries.empty() && boundaries[0].xCoord > 0) {
        cout << "0 0" << endl;
    }
    read.close();
    int i = 0;
    // making a left to right sweep across the city
    while (i < boundaries.size()) {
        int currentX = boundaries[i].xCoord;
        
        // checking all boundaries that happen at the exact x coordinate
        while (i < boundaries.size() && boundaries[i].xCoord == currentX) {
            Boundaries & e = boundaries[i];
            
            if (e.isStart == true) {
                // if left edge, insert the building
                MPQ.insert(buildings[e.building_id].height, e.building_id);
            }
            else { // remove the building if right
                MPQ.Remove(e.building_id);
            }
            i++;
        }
        
        // check to see if the maximum height of the buildings in the MPQ has changed
        int newMax;

        if (MPQ.IsEmpty()) {
            newMax = 0;
        }
        else {
            newMax = MPQ.GetMax();
        }
        
        // output the x coordinate followed by the new current maximum height
        if (newMax != currentMax) {
            cout << currentX << " " << newMax << endl;
            currentMax = newMax;
        }
    }
    
    return 0;
}
