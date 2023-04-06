#include <bits/stdc++.h>

#include "MinHeap.hpp"
#include "RedBlackTree.hpp"
using namespace std;

class GatorTaxi {
private:
  MinHeap mh;
  RedBlackTree rbt;

public:
  /**
   * @brief prints the triplet (rideNumber, rideCost, tripDuration);
   * if the ride doesn't exists prints (0,0,0). This query is executed in
   * O(log(n)) time
   *
   * @param rideNumber unique integer identifier for the ride
   */
  void Print(int rideNumber) {

    // Search operation in RBT is O(log(n)) time
    auto node = rbt.search(rideNumber);

    if (node == nullptr) {
      cout << "(0,0,0)" << endl;
      return;
    }

    auto ride = node->ride;
    cout << "(" << ride.rideNumber << "," << ride.rideCost << ","
         << ride.tripDuration << ")" << endl;
  }

  /**
   * @brief prints all the rides between rideNumber1 and rideNumber2 inclusive
   * prints (0,0,0) otherwise if no rides found
   *
   * @param rideNumber1
   * @param rideNumber2
   */
  void Print(int rideNumber1, int rideNumber2) {
    vector<string> rides;
    rbt.getRange(rideNumber1, rideNumber2, rides);

    for (int i = 0; i < rides.size(); i++) {
      cout << rides[i];
      if (i != rides.size() - 1)
        cout << ",";
    }

    if (rides.size() == 0)
      cout << "(0,0,0)";

    cout << endl;
  }

  bool Insert(int rideNumber, int rideCost, int rideDescription) {
    auto preNode = rbt.search(rideNumber);
    if (preNode != nullptr) {
      cout << "Duplicate RideNumber" << endl;
      return true;
    }

    Ride ride = {rideNumber, rideCost, rideDescription};
    auto minHeapNode = mh.insert(ride);
    auto rbtNode = rbt.insert(ride);

    minHeapNode->external = rbtNode;
    rbtNode->external = minHeapNode;

    return false;
  }

  void GetNextRide() {
    // Ride with the lowest rideCost, breaking ties with lowest tripDuration is
    // output and deleted
    auto minHeapNode = mh.getMin();

    if (minHeapNode == nullptr) {
      cout << "No active ride requests" << endl;
      return;
    }

    auto ride = minHeapNode->ride;
    rbt.remove(minHeapNode->external);
    cout << "(" << ride.rideNumber << "," << ride.rideCost << ","
         << ride.tripDuration << ")" << endl;
  }

  void CancelRide(int rideNumber) {
    auto rbtNode = rbt.search(rideNumber);

    if (rbtNode == nullptr) {
      return;
    }

    auto minHeapNode = rbtNode->external;
    rbt.remove(rbtNode);
    mh.remove(minHeapNode);
  }

  void UpdateTrip(int rideNumber, int new_tripDuration) {
    // Rider wishes to change the destination
    // If new_tripDuration <= existing trupDuration, no action needed
    // If existing_tripDuration < new_tripDuration <= 2 * (existing
    // tripDuration) the driver will cancel the existing ride and new ride
    // request with a penalty of 10 on existing rideCost Else, the ride would be
    // declined and removed from DS
    auto rbtNode = rbt.search(rideNumber);
    if (rbtNode == nullptr) {
      return;
    }
    auto ride = rbtNode->ride;

    if (new_tripDuration <= ride.tripDuration) {
      rbtNode->ride.tripDuration = new_tripDuration;
      rbtNode->external->ride.tripDuration = new_tripDuration;
      return;
    } else {
      this->CancelRide(rideNumber);
      if (ride.tripDuration <= new_tripDuration &&
          new_tripDuration <= ride.tripDuration * 2) {
        this->Insert(rideNumber, ride.rideCost + 10, new_tripDuration);
      }
    }
  }
};