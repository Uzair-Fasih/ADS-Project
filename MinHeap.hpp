#include "Nodes.hpp"
#include <queue>
#include <vector>

class MinHeap {
private:
  MinHeapNode *root = nullptr;

  MinHeapNode *getLastNode() {
    if (!root) {
      return nullptr;
    }

    std::queue<MinHeapNode *> q;
    q.push(root);

    MinHeapNode *lastNode = nullptr;

    while (!q.empty()) {
      lastNode = q.front();
      q.pop();

      if (lastNode->left) {
        q.push(lastNode->left);
      }

      if (lastNode->right) {
        q.push(lastNode->right);
      }
    }

    return lastNode;
  }

  void heapify(MinHeapNode *node) {
    while (true) {
      MinHeapNode *scNode = node;

      if (node->left &&
          ((node->left->ride.rideCost < scNode->ride.rideCost) ||
           ((node->left->ride).rideCost == (scNode->ride).rideCost &&
            (node->left->ride).tripDuration < (scNode->ride).tripDuration))) {
        scNode = node->left;
      }

      if (node->right &&
          ((node->right->ride.rideCost < scNode->ride.rideCost) ||
           ((node->right->ride).rideCost == (scNode->ride).rideCost &&
            (node->right->ride).tripDuration < (scNode->ride).tripDuration))) {
        scNode = node->right;
      }

      if (scNode == node) {
        break;
      }

      std::swap(node->ride, scNode->ride);
      std::swap(node->external, scNode->external);

      if (node->external)
        node->external->external = node;
      if (scNode->external)
        scNode->external->external = scNode;

      node = scNode;
    }
  }

public:
  /**
   * @brief Inserts a new ride in the min heap.
   * Returns the newly added node so to add external pointer
   *
   * @param ride Ride information
   * @return MinHeapNode
   */
  MinHeapNode *insert(Ride ride) {
    MinHeapNode *node = new MinHeapNode(ride);

    if (root == nullptr) {
      root = node;
      return node;
    }

    std::queue<MinHeapNode *> q;
    q.push(root);

    while (!q.empty()) {
      MinHeapNode *temp = q.front();
      q.pop();

      if (temp->left == NULL) {
        temp->left = node;
        node->parent = temp;
        break;
      } else if (temp->right == NULL) {
        temp->right = node;
        node->parent = temp;
        break;
      } else {
        q.push(temp->left);
        q.push(temp->right);
      }
    }

    MinHeapNode *pnode = node->parent;

    // Bubble up
    while (pnode != nullptr &&
           ((pnode->ride.rideCost > node->ride.rideCost) ||
            ((pnode->ride).rideCost == (node->ride).rideCost &&
             (pnode->ride).tripDuration > (node->ride).tripDuration))) {

      std::swap(pnode->ride, node->ride);
      std::swap(pnode->external, node->external);

      if (pnode->external)
        pnode->external->external = pnode;
      if (node->external)
        node->external->external = node;

      node = pnode;
      pnode = node->parent;
    }

    return node;
  }

  /**
   * @brief Returns the Min Ride while also deleting it in the process.
   * rideCost is used as key. Ties are broken using lower tripDuration
   * @return MinHeapNode
   */
  MinHeapNode *getMin() {
    if (root == nullptr) {
      return nullptr;
    }

    // Get largest node
    MinHeapNode *lastNode = getLastNode();

    MinHeapNode *minRide = new MinHeapNode(root->ride);
    minRide->external = root->external;
    if (minRide->external) {
      minRide->external->external = minRide;
    }

    if (root->left == nullptr) {
      root = root->right;
      return minRide;
    }

    // Switch lastNode with root
    root->ride = lastNode->ride;
    root->external = lastNode->external;
    if (root->external) {
      root->external->external = root;
    }

    // Delete the lastNode
    if (lastNode->parent->left == lastNode) {
      lastNode->parent->left = nullptr;
    } else if (lastNode->parent->right == lastNode) {
      lastNode->parent->right = nullptr;
    }

    // Bubble down
    heapify(root);
    return minRide;
  }

  /**
   * @brief Removes the specified node from the heap
   * @param node The node to remove
   */
  void remove(MinHeapNode *node) {
    if (node == nullptr) {
      return;
    }
    if (node == root) {
      this->getMin();
      return;
    }

    // Get largest node
    MinHeapNode *lastNode = getLastNode();

    // Switch lastNode with node
    node->ride = lastNode->ride;
    node->external = lastNode->external;
    if (node->external) {
      node->external->external = node;
    }

    // Delete the lastNode
    if (lastNode->parent && lastNode->parent->left == lastNode) {
      lastNode->parent->left = nullptr;
    } else if (lastNode->parent && lastNode->parent->right == lastNode) {
      lastNode->parent->right = nullptr;
    }

    // Bubble down
    heapify(node);
  }
};
