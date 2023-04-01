#ifndef RBT_HEADER
#define RBT_HEADER

#include "Ride.hpp"
#include <bits/stdc++.h>

enum Color { RED, BLACK };

/**
 * @brief
 *
 */
class RBTNode {
public:
  Ride ride;
  Color color;
  RBTNode *left;
  RBTNode *right;
  RBTNode *parent;

  RBTNode(Ride ride) {
    this->ride = ride;
    color = RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class RedBlackTree {
private:
  RBTNode *root;

  void leftRotate(RBTNode *node) {
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

    while (node != root && node->color == RED && node->parent->color == RED) {
      parent = node->parent;
      grandparent = parent->parent;

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
          std::swap(parent->color, grandparent->color);
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
          std::swap(parent->color, grandparent->color);
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

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          leftRotate(node->parent);
          sibling = node->parent->right;
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

        if (sibling->color == RED) {
          sibling->color = BLACK;
          node->parent->color = RED;
          rightRotate(node->parent);
          sibling = node->parent->left;
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

  void insert(Ride ride) {
    RBTNode *node = new RBTNode(ride);
    RBTNode *parent = nullptr;
    RBTNode *current = root;

    while (current != nullptr) {
      parent = current;

      if (ride.rideNumber < current->ride.rideNumber) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    node->parent = parent;

    if (parent == nullptr) {
      root = node;
    } else if (ride.rideNumber < parent->ride.rideNumber) {
      parent->left = node;
    } else {
      parent->right = node;
    }

    fixInsert(node);
  }

  void remove(int rideNumber) {
    RBTNode *node = search(rideNumber);

    if (node == nullptr) {
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

      node->left->parent = replace;

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
};

#endif