#include "Nodes.hpp"

class RedBlackTree {
private:
  RBTNode *root = nullptr;

  /**
   * @brief The node's right child becomes the new parent node, and the node
becomes the new left child of the parent If the right child has a left child, it
becomes the right child of the original node The parent and grandparent pointers
are adjusted accordingly The root is updated if necessary
   *
   * @param node
   * @return * This
   */
  void leftRotate(RBTNode *node) {

    // Check if the node exists
    if (node == nullptr) {
      return;
    }

    // Store the right child of the node in a temporary variable
    RBTNode *rightChild = node->right;

    // Make the right child's left child the new right child of the node
    node->right = rightChild->left;

    // Update the parent pointer of the new right child if it exists
    if (rightChild->left != nullptr) {
      rightChild->left->parent = node;
    }

    // Update the parent pointer of the right child
    rightChild->parent = node->parent;

    // Update the root if the node is the root of the tree
    if (node->parent == nullptr) {
      root = rightChild;
    } else if (node == node->parent->left) {
      // Update the parent pointer of the node's parent if the node is a left
      // child
      node->parent->left = rightChild;
    } else {
      // Update the parent pointer of the node's parent if the node is a right
      // child
      node->parent->right = rightChild;
    }

    // Make the node the new left child of the right child
    rightChild->left = node;

    // Update the parent pointer of the node
    node->parent = rightChild;
  }

  /**
   * @brief This function performs a right rotation on the given node The node's
   * left child becomes the new parent node, and the node becomes the new right
   * child of the parent If the left child has a right child, it becomes the
   * left child of the original node The parent and grandparent pointers are
   * adjusted accordingly The root is updated if necessary
   *
   * @param node
   */
  void rightRotate(RBTNode *node) {

    // Check if the node exists
    if (node == nullptr) {
      return;
    }

    // Store the left child of the node in a temporary variable
    RBTNode *leftChild = node->left;

    // Make the left child's right child the new left child of the node
    node->left = leftChild->right;

    // Update the parent pointer of the new left child if it exists
    if (leftChild->right != nullptr) {
      leftChild->right->parent = node;
    }

    // Update the parent pointer of the left child
    leftChild->parent = node->parent;

    // Update the root if the node is the root of the tree
    if (node->parent == nullptr) {
      root = leftChild;
    } else if (node == node->parent->right) {
      // Update the parent pointer of the node's parent if the node is a right
      // child
      node->parent->right = leftChild;
    } else {
      // Update the parent pointer of the node's parent if the node is a left
      // child
      node->parent->left = leftChild;
    }

    // Make the node the new right child of the left child
    leftChild->right = node;

    // Update the parent pointer of the node
    node->parent = leftChild;
  }

  /**
   * @brief The fixInsert function fixes the tree after insertion of a new node,
   * by performing rotations and color changes to maintain the properties of a
   * Red-Black Tree. The function takes the inserted node as input and checks
   * its parent and grandparent nodes to ensure the tree remains balanced. If
   * the tree becomes unbalanced, the function performs rotations and color
   * changes to balance it.
   *
   * @param node
   */
  void fixInsert(RBTNode *node) {
    RBTNode *parent = nullptr;
    RBTNode *grandparent = nullptr;

    // Fix insert violations
    while (node != root && node->color == RED && node->parent != nullptr &&
           node->parent->color == RED) {
      parent = node->parent;
      grandparent = parent->parent;

      // Check for null pointer in grandparent
      if (grandparent == nullptr) { // added null pointer check
        break;
      }

      if (parent == grandparent->left) {
        RBTNode *uncle = grandparent->right;

        if (uncle != nullptr && uncle->color == RED) {
          // Case 1: recoloring
          grandparent->color = RED;
          parent->color = BLACK;
          uncle->color = BLACK;
          node = grandparent;
        } else {
          if (node == parent->right) {
            // Case 2: left rotation and case 3
            leftRotate(parent);
            node = parent;
            parent = node->parent;
          }

          // Case 3: right rotation and recoloring
          rightRotate(grandparent);
          std::swap(parent->color, grandparent->color);
          node = parent;
        }
      } else {
        RBTNode *uncle = grandparent->left;

        if (uncle != nullptr && uncle->color == RED) {
          // Case 1: recoloring
          grandparent->color = RED;
          parent->color = BLACK;
          uncle->color = BLACK;
          node = grandparent;
        } else {
          if (node == parent->left) {
            // Case 2: right rotation and case 3
            rightRotate(parent);
            node = parent;
            parent = node->parent;
          }

          // Case 3: left rotation and recoloring
          leftRotate(grandparent);
          std::swap(parent->color, grandparent->color);
          node = parent;
        }
      }
    }

    // Ensure root node is black
    root->color = BLACK;
  }

  /**
   * @brief The fixInsert function fixes the tree after insertion of a new node,
   * by performing rotations and color changes to maintain the properties of a
   * Red-Black Tree. The function takes the inserted node as input and checks
   * its parent and grandparent nodes to ensure the tree remains balanced. If
   * the tree becomes unbalanced, the function performs rotations and color
   * changes to balance it.
   *
   * @param node
   */
  void fixDelete(RBTNode *node) {
    while (node != root && node->color == BLACK) {
      if (node == node->parent->left) {
        RBTNode *sibling = node->parent->right;

        if (sibling == nullptr) {
          // Handle segmentation fault: if sibling is null, break the loop
          break;
        }

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          leftRotate(node->parent);
          sibling = node->parent->right;
        }

        if (sibling->left == nullptr || sibling->right == nullptr) {
          // Handle segmentation fault: if sibling's left or right child is
          // null, break the loop
          break;
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
          // If both of sibling's children are black, color sibling red and move
          // up the tree
          sibling->color = RED;
          node = node->parent;
        } else {
          if (sibling->right->color == BLACK) {
            // If sibling's right child is black, color its left child black,
            // color sibling red, perform right rotation on sibling, and update
            // sibling to be node's new sibling
            sibling->left->color = BLACK;
            sibling->color = RED;
            rightRotate(sibling);
            sibling = node->parent->right;
          }

          // Color sibling with parent's color and color parent black, color
          // sibling's right child black, perform left rotation on parent, and
          // move up to the root
          sibling->color = node->parent->color;
          node->parent->color = BLACK;
          sibling->right->color = BLACK;
          leftRotate(node->parent);
          node = root;
        }
      } else {
        // Same as above, but with "left" and "right" swapped
        RBTNode *sibling = node->parent->left;

        if (sibling == nullptr) {
          // Handle segmentation fault: if sibling is null, break the loop
          break;
        }

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          rightRotate(node->parent);
          sibling = node->parent->left;
        }

        if (sibling->left == nullptr || sibling->right == nullptr) {
          // Handle segmentation fault: if sibling's left or right child is
          // null, break the loop
          break;
        }

        if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
          // If both of sibling's children are black, color sibling red and move
          // up the tree
          sibling->color = RED;
          node = node->parent;
        } else {
          if (sibling->left->color == BLACK) {
            // If sibling's left child is black, color its right child black,
            // color sibling red, perform left rotation on sibling, and update
            // sibling to be node's new sibling
            sibling->right->color = BLACK;
            sibling->color = RED;
            leftRotate(sibling);
            sibling = node->parent->left;
          }

          // Color sibling with parent's color and color parent black, color
          // sibling's left child black, perform right rotation on parent, and
          // move up to the root
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

  /**
   * @brief Remove a node from the red-black tree. If the node doesn't exist
   * simply return. Operation works in O(log(n)) time.
   *
   * @param node
   */
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

  void getRange(int start, int end, std::vector<Ride> &rides) {
    getRange(root, start, end, rides);
  }

  /**
   * @brief Get the rides within the range specified start and end. The rides
   * are added to the rides std::vector passed by reference.The time complexity
   * of using inorder traversal to get this range is O(k + log(n)), where k is
   * the number of nodes in the range.
   *
   * @param node
   * @param start
   * @param end
   * @param rides
   */
  void getRange(RBTNode *node, int start, int end, std::vector<Ride> &rides) {
    if (node == nullptr) {
      return;
    }

    if (node->ride.rideNumber > start) {
      getRange(node->left, start, end, rides);
    }

    if (node->ride.rideNumber >= start && node->ride.rideNumber <= end) {
      rides.push_back(node->ride);
    }

    if (node->ride.rideNumber < end) {
      getRange(node->right, start, end, rides);
    }
  }
};
