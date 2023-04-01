#include "Ride.hpp"
#include <bits/stdc++.h>

using namespace std;

class GatorTaxi {
public:
  void Print(int rideNumber) {
    // Prints the triplet (rideNumber, rideCost, tripDuration)
  }

  void Print(int rideNumber1, int rideNumber2) {
    // Prints all triplexts (r_x, rideCost, tripDuration) for
    // which rideNumber1 <= r_x <= rideNumber2
  }

  void Insert(){int rideNumber, int rideCost, int rideDescription} {
    Ride r = {rideNumber, rideCost, rideDescription};
    // Here rideNumber must be unique
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