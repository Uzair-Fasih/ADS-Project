/**
 * @file main.cpp
 * @author Mohammad Uzair Fasih (mfasih@ufl.edu) [UFID: 6286-1020]
 * @brief GatoxTaxi Implementation for Advanced Data Structures
 * @version 0.1
 * @date 2023-04-06
 *
 * @copyright MIT 2023
 *
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "GatorTaxi.hpp"

int main(int argc, char *argv[]) {
  GatorTaxi gt;

  if (argc < 2) {
    cerr << "Please provide a filename as an argument" << endl;
    return 1;
  }

  // Open the input file
  ifstream inputFile(argv[1]);

  // Check if the file was opened successfully
  if (!inputFile) {
    cerr << "Unable to open input file" << endl;
    return 1;
  }

  FILE *outFile = freopen("output_file.txt", "w", stdout);

  // Check if the file was opened successfully
  if (outFile == nullptr) {
    fprintf(stderr, "Unable to open output file\n");
    return 1;
  }

  // Read each line of the input file
  string line;
  while (getline(inputFile, line)) {
    // Use a stringstream to split the line into tokens
    stringstream ss(line);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '(')) {
      tokens.push_back(token);
    }

    // Ensure that the line contains at least one token
    if (tokens.empty()) {
      continue;
    }

    // Determine which function to call based on the first token
    if (tokens[0] == "Insert") {
      // Extract the three integer arguments
      int x, y, z;
      char delimiter;
      stringstream argStream(tokens[1]);
      argStream >> x >> delimiter >> y >> delimiter >> z;
      auto err = gt.Insert(x, y, z);
      if (err) {
        break;
      }
    } else if (tokens[0] == "GetNextRide") {
      gt.GetNextRide();

    } else if (tokens[0] == "Print") {
      // Extract the two integer arguments
      int x, y;
      stringstream argStream(tokens[1]);
      argStream >> x;
      if (argStream.peek() == ',') {
        argStream.ignore();
        argStream >> y;
        // Call the Print function with the two extracted arguments
        gt.Print(x, y);
      } else {
        // Call the Print function with the one extracted argument
        gt.Print(x);
      }

    } else if (tokens[0] == "UpdateTrip") {
      // Extract the two integer arguments
      int x, y;
      char delimiter;
      stringstream argStream(tokens[1]);
      argStream >> x >> delimiter >> y;
      gt.UpdateTrip(x, y);

    } else if (tokens[0] == "CancelRide") {
      // Extract the integer argument
      int x;
      stringstream argStream(tokens[1]);
      argStream >> x;
      gt.CancelRide(x);

    } else {
      cerr << "Invalid input: " << line << endl;
    }
  }

  // Close the input file
  inputFile.close();

  return 0;
}
