#include <bits/stdc++.h>
using namespace std;

#include "GatorTaxi.hpp"

int main() {
  GatorTaxi gt;
  gt.Insert(25, 98, 46);
  gt.GetNextRide();
  gt.GetNextRide();
  gt.Insert(42, 17, 89);
  gt.Insert(9, 76, 31);
  gt.Insert(53, 97, 22);
  gt.GetNextRide();
  gt.Insert(68, 40, 51);

  // cout << "\n>" << endl;
  // gt.rbt.printTree();

  gt.GetNextRide();
  gt.Print(1, 100);
  gt.UpdateTrip(53, 15);
  gt.Insert(96, 28, 82);
  gt.Insert(73, 28, 56);
  gt.UpdateTrip(9, 88);
  gt.GetNextRide();
  gt.Print(9);
  gt.Insert(20, 49, 59);
  gt.Insert(62, 7, 10);
  gt.CancelRide(20);

  gt.Insert(25, 49, 46);
  gt.UpdateTrip(62, 15);
  gt.GetNextRide();
  gt.Print(1, 100);
  gt.Insert(53, 28, 19);
  gt.Print(1, 100);
}