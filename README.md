## 📌 Max Priority Queue with Label-Based Removal

This project implements a **Max Priority Queue (MPQ)** in C++ using a binary heap and an index-mapping mechanism to support efficient removal of elements by label.

Unlike standard heaps, this structure allows direct access and deletion of arbitrary elements in **O(log n)** time.

---

## Overview

The MPQ stores elements with:

* a **priority value**
* a **unique label**

The queue always keeps the highest priority element at the root while allowing removal of any element using its label.

This design is similar to **indexed priority queues** used in:

* Dijkstra’s algorithm
* task scheduling systems
* simulation engines
* event-driven systems

---

## Features

✔ Max-heap based priority queue
✔ O(log n) insertion
✔ O(1) maximum retrieval
✔ O(log n) removal by label
✔ Location mapping for fast access
✔ Template-based generic implementation

---

## Data Structure Design

### Heap Array

Stores elements in max-heap order.

### Location Array

Maps each label to its position in the heap.

This enables direct access without searching.

---

## Supported Operations

### Insert

Adds a new element with priority and label.

```cpp
mpq.insert(value, label);
```

### Get Maximum

Returns the highest priority value.

```cpp
mpq.GetMax();
```

### Remove by Label

Removes an element using its label.

```cpp
mpq.Remove(label);
```

### Check if Empty

```cpp
mpq.IsEmpty();
```

---

## Example

```cpp
MPQ<int> pq(10);

pq.insert(50, 1);
pq.insert(30, 2);
pq.insert(80, 3);

cout << pq.GetMax();   // 80

pq.Remove(3);

cout << pq.GetMax();   // 50
```

---

## ⏱ Complexity

| Operation       | Complexity |
| --------------- | ---------- |
| Insert          | O(log n)   |
| GetMax          | O(1)       |
| Remove by label | O(log n)   |
| Search by label | O(1)       |

---

## How Removal Works

1. Locate element using the **Location array**.
2. Replace it with the last heap element.
3. Update location mapping.
4. Restore heap property using percolate up/down.

---

## 🧪 Concepts Demonstrated

* Binary heap implementation
* Indexed priority queues
* Efficient deletion strategies
* Template programming in C++
* Heap property maintenance
