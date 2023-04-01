#include <bits/stdc++.h>

#include "MinHeap.hpp"
#include "RedBlackTree.hpp"
using namespace std;

class GatorTaxi {
private:
public:
  MinHeap mh;
  RedBlackTree rbt;
  void Print(int rideNumber) {
    auto node = rbt.search(rideNumber);

    if (node == nullptr) {
      cout << "(0,0,0)" << endl;
      return;
    }

    auto ride = node->ride;
    cout << "(" << ride.rideNumber << "," << ride.rideCost << ","
         << ride.tripDuration << ")" << endl;
  }

  void Print(int rideNumber1, int rideNumber2) {
    // Prints all triplexts (r_x, rideCost, tripDuration) for
    // which rideNumber1 <= r_x <= rideNumber2
    rbt.printRange(rideNumber1, rideNumber2);
    cout << endl;
  }

  void Insert(int rideNumber, int rideCost, int rideDescription) {
    auto preNode = rbt.search(rideNumber);
    if (preNode != nullptr) {
      cout << "Duplicate RideNumber" << endl;
      return;
    }

    Ride ride = {rideNumber, rideCost, rideDescription};
    auto minHeapNode = mh.insert(ride);
    auto rbtNode = rbt.insert(ride);

    minHeapNode->external = rbtNode;
    rbtNode->external = minHeapNode;
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
    rbt.remove(rbtNode);
    auto minHeapNode = rbtNode->external;
    mh.remove(minHeapNode);
    // If exists, delete the ride with rideNumber
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
      cout << "No Bueno hombre" << endl;
      return;
    }
    auto ride = rbtNode->ride;

    if (new_tripDuration < ride.tripDuration) {
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