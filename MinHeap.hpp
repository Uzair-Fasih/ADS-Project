#include "Nodes.hpp"
#include <bits/stdc++.h>
using namespace std;

class MinHeap {
public:
  vector<MinHeapNode *> nodes;

  /**
   * @brief Inserts a new ride in the min heap.
   * Returns the newly added heap so to add external pointer
   *
   * @param ride Ride information
   * @return MinHeapNode
   */
  MinHeapNode *insert(Ride ride) {
    MinHeapNode *newNode = new MinHeapNode(ride);
    nodes.push_back(newNode);

    if (nodes.size() == 1) {
      return newNode;
    }

    int idx = nodes.size() - 1;
    int pIdx = (idx - 1) / 2;

    while (idx > 0 &&
           ((nodes[pIdx]->ride.rideCost > nodes[idx]->ride.rideCost) ||
            ((nodes[pIdx]->ride).rideCost == (nodes[idx]->ride).rideCost &&
             (nodes[pIdx]->ride).tripDuration >
                 (nodes[idx]->ride).tripDuration))) {

      swap(nodes[pIdx], nodes[idx]);
      idx = pIdx;
      pIdx = (idx - 1) / 2;
    }

    return newNode;
  }

  /**
   * @brief Returns the Min Ride while also deleting it in the process
   * @return MinHeapNode
   */
  Ride getMin() {

    if (nodes.empty()) {
      cout << "Heap is Empty" << endl;
      Ride r;
      return r;
    }

    Ride minRide = nodes[0]->ride;
    MinHeapNode *lastNode = nodes.back();
    nodes.pop_back();

    if (nodes.empty()) {
      return minRide;
    }

    nodes[0] = lastNode;

    int idx = 0;
    while (true) {
      int lcIdx = 2 * idx + 1;
      int rcIdx = 2 * idx + 2;
      int scIdx = idx;

      if (lcIdx < nodes.size() &&
          ((nodes[lcIdx]->ride.rideCost < nodes[scIdx]->ride.rideCost) ||
           ((nodes[lcIdx]->ride).rideCost == (nodes[scIdx]->ride).rideCost &&
            (nodes[lcIdx]->ride).tripDuration <
                (nodes[scIdx]->ride).tripDuration)))
        scIdx = lcIdx;

      if (rcIdx < nodes.size() &&
          ((nodes[rcIdx]->ride.rideCost < nodes[scIdx]->ride.rideCost) ||
           ((nodes[rcIdx]->ride).rideCost == (nodes[scIdx]->ride).rideCost &&
            (nodes[rcIdx]->ride).tripDuration <
                (nodes[scIdx]->ride).tripDuration)))
        scIdx = rcIdx;

      ;
      if (scIdx == idx)
        break;

      swap(nodes[idx], nodes[scIdx]);
      idx = scIdx;
    }

    return minRide;
  }
};
