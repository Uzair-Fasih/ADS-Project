#include <bits/stdc++.h>
using namespace std;

#include "MinHeap.hpp"
#include "RedBlackTree.hpp"

int main() {
  MinHeap mh;
  RedBlackTree rbt;
  Ride r1 = {1, 2, 3}, r2 = {2, 3, 4};

  rbt.insert(r1);
  rbt.insert(r2);
  auto x = rbt.search(2);
  cout << x->ride.tripDuration << endl;

  cout << "Compilation Test" << endl;
}