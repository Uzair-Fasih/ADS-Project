#include "MinHeap.hpp"
#include "RedBlackTree.hpp"

class GatorTaxi {
private:
  MinHeap mh;
  RedBlackTree rbt;

public:
  /**
   * @brief prints the triplet (rideNumber, rideCost, tripDuration) identified
   * by the rideNumber; if the ride doesn't exists prints (0,0,0). This query is
   * executed in O(log(n)) time.
   *
   * @param rideNumber unique integer identifier for the ride
   */
  void Print(int rideNumber) {

    // Search operation in RBT is O(log(n)) time
    auto node = rbt.search(rideNumber);

    if (node == nullptr) {
      std::cout << "(0,0,0)" << std::endl;
      return;
    }

    auto ride = node->ride;
    std::cout << "(" << ride.rideNumber << "," << ride.rideCost << ","
              << ride.tripDuration << ")" << std::endl;
  }

  /**
   * @brief prints all the rides between rideNumber1 and rideNumber2 inclusive;
   * prints (0,0,0) otherwise if no rides found. This method is executed in
   * O(log(n) + k) time.
   *
   * @param rideNumber1
   * @param rideNumber2
   */
  void Print(int rideNumber1, int rideNumber2) {
    std::vector<Ride> rides;
    rbt.getRange(rideNumber1, rideNumber2, rides);

    for (int i = 0; i < rides.size(); i++) {
      std::cout << "(" << rides[i].rideNumber << "," << rides[i].rideCost << ","
                << rides[i].tripDuration << ")";

      if (i != rides.size() - 1) {
        std::cout << ",";
      }
    }

    if (rides.size() == 0) {
      std::cout << "(0,0,0)";
    }

    std::cout << std::endl;
  }

  /**
   * @brief Inserts a new ride into the RBT and Min Heap structure. Returns
   * false if operation succeed, else true if operation fails. This operation is
   * performed in O(log(n)) time
   *
   * @param rideNumber
   * @param rideCost
   * @param rideDescription
   * @return true if operation fails
   * @return false if operation succeeds
   */
  bool Insert(int rideNumber, int rideCost, int rideDescription) {
    // Perform a search to see if the ride exists
    auto preNode = rbt.search(rideNumber);

    if (preNode != nullptr) {
      std::cout << "Duplicate RideNumber" << std::endl;
      return true;
    }

    Ride ride = {rideNumber, rideCost, rideDescription};
    // Insert node into min heap, op takes O(log(n))
    auto minHeapNode = mh.insert(ride);

    // Insert node into red-black tree, op takes O(log(n))
    auto rbtNode = rbt.insert(ride);

    // Add a pointer from min-heap node to red-black tree node
    minHeapNode->external = rbtNode;
    // Add a pointer from red-black tree node to min-heap node
    rbtNode->external = minHeapNode;

    return false;
  }

  /**
   * @brief Get the next ride, if no ride exists, print message
   *  Operation takes O(log(n)) time.
   */
  void GetNextRide() {
    auto minHeapNode = mh.getMin(); // Get the next ride in O(1) time

    if (minHeapNode == nullptr) {
      std::cout << "No active ride requests" << std::endl;
      return;
    }

    auto ride = minHeapNode->ride;

    // Also remove the corresponding node in the red-black tree, operation takes
    // O(log(n)) time

    rbt.remove(minHeapNode->external);
    std::cout << "(" << ride.rideNumber << "," << ride.rideCost << ","
              << ride.tripDuration << ")" << std::endl;
  }

  /**
   * @brief Cancel the ride identified by rideNumber. If the ride doesn't exist,
   * simply return. This operation works in O(log(n)) time
   *
   * @param rideNumber
   */
  void CancelRide(int rideNumber) {
    auto rbtNode = rbt.search(rideNumber); // Operation takes O(log(n)) time

    if (rbtNode == nullptr) {
      return;
    }

    auto minHeapNode = rbtNode->external;
    rbt.remove(rbtNode);    // Operation takes O(log(n)) time
    mh.remove(minHeapNode); // Operation takes O(log(n)) time
  }

  /**
   * @brief Updates the trip based on certain conditions. This operation works
   * in O(log(n)) time.
   *
   * @param rideNumber
   * @param new_tripDuration
   */
  void UpdateTrip(int rideNumber, int new_tripDuration) {
    auto rbtNode = rbt.search(rideNumber); // Search takes O(log(n))
    if (rbtNode == nullptr) {
      return;
    }

    auto ride = rbtNode->ride;

    if (new_tripDuration <= ride.tripDuration) {
      // Simply update the tripDuration
      rbtNode->ride.tripDuration = new_tripDuration;
      rbtNode->external->ride.tripDuration = new_tripDuration;
      return;
    } else {
      this->CancelRide(rideNumber); // Cancel takes O(log(n))

      if (ride.tripDuration <= new_tripDuration &&
          new_tripDuration <= ride.tripDuration * 2) {
        this->Insert(rideNumber, ride.rideCost + 10,
                     new_tripDuration); // Insert takes O(log(n))
      }
    }
  }
};