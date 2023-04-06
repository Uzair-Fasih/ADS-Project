#include "Nodes.hpp"

class RedBlackTree {
private:
  RBTNode *root = nullptr;

  void leftRotate(RBTNode *node) {

    if (node == nullptr) {
      return;
    }

    RBTNode *rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
      rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
      root = rightChild;
    } else if (node == node->parent->left) {
      node->parent->left = rightChild;
    } else {
      node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
  }

  void rightRotate(RBTNode *node) {

    if (node == nullptr) {
      return;
    }

    RBTNode *leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
      leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
      root = leftChild;
    } else if (node == node->parent->right) {
      node->parent->right = leftChild;
    } else {
      node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
  }

  void fixInsert(RBTNode *node) {
    RBTNode *parent = nullptr;
    RBTNode *grandparent = nullptr;

    while (node != root && node->color == RED && node->parent != nullptr &&
           node->parent->color == RED) {
      parent = node->parent;
      grandparent = parent->parent;

      if (grandparent == nullptr) { // added null pointer check
        break;
      }

      if (parent == grandparent->left) {
        RBTNode *uncle = grandparent->right;

        if (uncle != nullptr && uncle->color == RED) {
          grandparent->color = RED;
          parent->color = BLACK;
          uncle->color = BLACK;
          node = grandparent;
        } else {
          if (node == parent->right) {
            leftRotate(parent);
            node = parent;
            parent = node->parent;
          }

          rightRotate(grandparent);
          swap(parent->color, grandparent->color);
          node = parent;
        }
      } else {
        RBTNode *uncle = grandparent->left;

        if (uncle != nullptr && uncle->color == RED) {
          grandparent->color = RED;
          parent->color = BLACK;
          uncle->color = BLACK;
          node = grandparent;
        } else {
          if (node == parent->left) {
            rightRotate(parent);
            node = parent;
            parent = node->parent;
          }

          leftRotate(grandparent);
          swap(parent->color, grandparent->color);
          node = parent;
        }
      }
    }

    root->color = BLACK;
  }

  void fixDelete(RBTNode *node) {
    while (node != root && node->color == BLACK) {
      if (node == node->parent->left) {
        RBTNode *sibling = node->parent->right;

        if (sibling == nullptr) {
          // Handle segmentation fault
          break;
        }

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          leftRotate(node->parent);
          sibling = node->parent->right;
        }

        if (sibling->left == nullptr || sibling->right == nullptr) {
          // Handle segmentation fault
          break;
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
          sibling->color = RED;
          node = node->parent;
        } else {
          if (sibling->right->color == BLACK) {
            sibling->left->color = BLACK;
            sibling->color = RED;
            rightRotate(sibling);
            sibling = node->parent->right;
          }

          sibling->color = node->parent->color;
          node->parent->color = BLACK;
          sibling->right->color = BLACK;
          leftRotate(node->parent);
          node = root;
        }
      } else {
        RBTNode *sibling = node->parent->left;

        if (sibling == nullptr) {
          // Handle segmentation fault
          break;
        }

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          rightRotate(node->parent);
          sibling = node->parent->left;
        }

        if (sibling->left == nullptr || sibling->right == nullptr) {
          // Handle segmentation fault
          break;
        }

        if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
          sibling->color = RED;
          node = node->parent;
        } else {
          if (sibling->left->color == BLACK) {
            sibling->right->color = BLACK;
            sibling->color = RED;
            leftRotate(sibling);
            sibling = node->parent->left;
          }

          sibling->color = node->parent->color;
          node->parent->color = BLACK;
          sibling->left->color = BLACK;
          rightRotate(node->parent);
          node = root;
        }
      }
    }

    node->color = BLACK;
  }

public:
  /**
   * @brief Searches for a node identified by the rideNumber much like a BST
   *
   * @param rideNumber
   * @return RBTNode*
   */
  RBTNode *search(int rideNumber) {
    RBTNode *current = root;

    while (current != nullptr && current->ride.rideNumber != rideNumber) {
      if (rideNumber < current->ride.rideNumber) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return current;
  }

  /**
   * @brief An insert operation for the red-black tree. This operation is
   * executed in O(log(n)) time.
   *
   * @param ride
   * @return RBTNode*
   */
  RBTNode *insert(Ride ride) {
    RBTNode *node = new RBTNode(ride); // New node to be inserted

    // Check if root is nullptr and set new node as root
    if (root == nullptr) {
      root = node;
      node->color = BLACK;
      return node;
    }

    RBTNode *parent = nullptr;
    RBTNode *current = root;

    // Identify an empty spot in the BST to insert the node
    while (current != nullptr) {
      parent = current;

      if (ride.rideNumber < current->ride.rideNumber) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    // Check if parent is nullptr and set new node as root
    if (parent == nullptr) {
      root = node;
      node->color = BLACK;
    } else {
      // Add the node to the tree through the parent
      node->parent = parent;
      if (ride.rideNumber < parent->ride.rideNumber) {
        parent->left = node;
      } else {
        parent->right = node;
      }
      fixInsert(node); // Rebalance the tree if needed
    }

    return node;
  }

  void remove(RBTNode *node) {

    if (node == nullptr) {
      return;
    }

    if (node == root && node->left == nullptr && node->right == nullptr) {
      root = nullptr;
      return;
    }

    RBTNode *child;
    RBTNode *parent;
    Color color;

    if (node->left != nullptr && node->right != nullptr) {
      RBTNode *replace = node->right;

      while (replace->left != nullptr) {
        replace = replace->left;
      }

      child = replace->right;
      parent = replace->parent;
      color = replace->color;

      if (child != nullptr) {
        child->parent = parent;
      }

      if (parent == nullptr) {
        root = child;
      } else if (replace == parent->left) {
        parent->left = child;
      } else {
        parent->right = child;
      }

      if (replace->parent == node) {
        parent = replace;
      }

      replace->parent = node->parent;
      replace->color = node->color;
      replace->left = node->left;
      replace->right = node->right;

      if (node->parent == nullptr) {
        root = replace;
      } else if (node == node->parent->left) {
        node->parent->left = replace;
      } else {
        node->parent->right = replace;
      }

      if (node->left != nullptr) {
        node->left->parent = replace;
      }

      if (node->right != nullptr) {
        node->right->parent = replace;
      }
    } else {

      if (node->left != nullptr) {
        child = node->left;
      } else {
        child = node->right;
      }

      parent = node->parent;
      color = node->color;

      if (child != nullptr) {
        child->parent = parent;
      }

      if (parent == nullptr) {
        root = child;
      } else if (node == parent->left) {
        parent->left = child;
      } else {
        parent->right = child;
      }
    }

    if (color == BLACK) {
      fixDelete(child == nullptr ? parent : child);
    }

    delete node;
  }

  void getRange(int start, int end, vector<string> &rides) {
    getRange(root, start, end, rides);
  }

  void getRange(RBTNode *node, int start, int end, vector<string> &rides) {
    if (node == nullptr) {
      return;
    }

    if (node->ride.rideNumber > start) {
      getRange(node->left, start, end, rides);
    }

    if (node->ride.rideNumber >= start && node->ride.rideNumber <= end) {
      rides.push_back("(" + to_string(node->ride.rideNumber) + "," +
                      to_string(node->ride.rideCost) + "," +
                      to_string(node->ride.tripDuration) + ")");
    }

    if (node->ride.rideNumber < end) {
      getRange(node->right, start, end, rides);
    }
  }
};
