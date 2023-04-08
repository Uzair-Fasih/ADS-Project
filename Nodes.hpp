#ifndef NODES_HEADER
#define NODES_HEADER

enum Color { RED, BLACK };
struct Ride {
  int rideNumber;
  int rideCost;
  int tripDuration;
};

class MinHeapNode;
class RBTNode;

/**
 * @brief MinHeapNode implementation
 * Each node holds the ride information and an additional external pointer
 * to a node in RBT
 */
class MinHeapNode {
public:
  Ride ride;
  MinHeapNode *left, *right, *parent;
  RBTNode *external;

  MinHeapNode(Ride ride) {
    this->ride = ride;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    external = nullptr;
  }
};

/**
 * @brief RBTNode implementation
 * Each node holds the ride information, and an additional external node to a
 * node in Min Heap
 */
class RBTNode {
public:
  Ride ride;
  Color color;
  RBTNode *left;
  RBTNode *right;
  RBTNode *parent;
  MinHeapNode *external;

  RBTNode(Ride ride) {
    this->ride = ride;
    color = RED; // Newly created nodes are RED for most cases
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    external = nullptr;
  }
};

#endif