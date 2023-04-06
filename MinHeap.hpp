#include "Nodes.hpp"
#include <vector>

class MinHeap {
public:
  std::vector<MinHeapNode *> nodes;

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

      std::swap(nodes[pIdx], nodes[idx]);
      idx = pIdx;
      pIdx = (idx - 1) / 2;
    }

    return newNode;
  }

  /**
   * @brief Returns the Min Ride while also deleting it in the process. rideCost
   * is used as key. Ties are broken using lower tripDuration
   * @return MinHeapNode
   */
  MinHeapNode *getMin() {

    if (nodes.empty()) {
      return nullptr;
    }

    MinHeapNode *minRide = nodes[0];
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

      std::swap(nodes[idx], nodes[scIdx]);
      idx = scIdx;
    }

    return minRide;
  }

  /**
   * @brief Removes the specified node from the heap
   * @param node The node to remove
   */
  void remove(MinHeapNode *node) {
    // Find the index of the node to remove
    int idx = -1;
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i] == node) {
        idx = i;
        break;
      }
    }

    if (idx == -1) {
      // Node not found in the heap
      return;
    }

    // Swap the node with the last node in the heap
    std::swap(nodes[idx], nodes[nodes.size() - 1]);
    nodes.pop_back();

    if (idx == nodes.size()) {
      // Removed node was the last node in the heap
      return;
    }

    // Fix the heap by checking if the node needs to be bubbled up or down
    int pIdx = (idx - 1) / 2;
    while (idx > 0 &&
           ((nodes[pIdx]->ride.rideCost > nodes[idx]->ride.rideCost) ||
            ((nodes[pIdx]->ride).rideCost == (nodes[idx]->ride).rideCost &&
             (nodes[pIdx]->ride).tripDuration >
                 (nodes[idx]->ride).tripDuration))) {

      std::swap(nodes[pIdx], nodes[idx]);
      idx = pIdx;
      pIdx = (idx - 1) / 2;
    }

    int lcIdx, rcIdx, scIdx;
    while (true) {
      lcIdx = 2 * idx + 1;
      rcIdx = 2 * idx + 2;
      scIdx = idx;

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

      if (scIdx == idx)
        break;

      std::swap(nodes[idx], nodes[scIdx]);
      idx = scIdx;
    }
  }
};
