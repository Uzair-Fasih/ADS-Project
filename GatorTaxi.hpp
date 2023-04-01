#include <bits/stdc++.h>

#include "MinHeap.hpp"
#include "RedBlackTree.hpp"
using namespace std;

class GatorTaxi {
private:
  MinHeap mh;
  RedBlackTree rbt;

public:
  void Print(int rideNumber) {
    auto node = rbt.search(rideNumber);
    auto ride = node->ride;
    cout << "(" << ride.rideNumber << ", " << ride.rideCost << ", "
         << ride.tripDuration << ")" << endl;
  }

  void Print(int rideNumber1, int rideNumber2) {
    // Prints all triplexts (r_x, rideCost, tripDuration) for
    // which rideNumber1 <= r_x <= rideNumber2
  }

  void Insert(int rideNumber, int rideCost, int rideDescription) {
    Ride ride = {rideNumber, rideCost, rideDescription};
    auto minHeapNode = mh.insert(ride);
    auto rbtNode = rbt.insert(ride);

    minHeapNode->external = rbtNode;
    rbtNode->external = minHeapNode;
  }

  void GetNextRide() {
    // Ride with the lowest rideCost, breaking ties with lowest  tripDuration is
    // output and deleted
  }

  void CancelRide(int rideNumber) {
    // If exists, delete the ride with rideNumber
  }

  void UpdateTrip(int rideNumber, int new_tripDuration) {
    // Rider wishes to change the destination
    // If new_tripDuration <= existing trupDuration, no action needed
    // If existing_tripDuration < new_tripDuration <= 2 * (existing
    // tripDuration) the driver will cancel the existing ride and new ride
    // request with a penalty of 10 on existing rideCost Else, the ride would be
    // declined and removed from DS
  }
};