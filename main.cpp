// Erick Juarez
// Juarez.erick16@csu.fullerton.edu
// CPSC 351 Sec 01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

// Library Dependencies
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
# include <fstream>
using std::ifstream;
using std::ofstream;
# include <string>
using std::string;
#include <algorithm>
#include <sstream>
#include <iterator>

#include "memory.h"

////////////////////////////////////////////////////////////////////////////////////
// This file contains the main function of the program
/////////////////////////////////////////////////////////////////////////////////////

/*    Pseudo code for main
    1. get memory size
    2. find valid factors to memoy size to be the page size
    3. let USER pick page size from valid factors found in step 2
    4. open INPUT File
    5. get process information and initialize PROCESS objcts
    6. Initialize MEMORY and MEMORY MANAGER objects
    7. Initialize Time, For time < 100,000:
	(These funnctions are implemented in the Memory Manager class.
	  i. Check process arrivals
	 ii. Check if process can be loaded to memory
	iii. Check for process terminations
*/

// Function prototypes
int getPageSize(int);
int initProc(vector<string>&, vector<Process>&);

int main(){

  int memorySize = 0;
  int pageSize = 0;

  int processCount;
  vector<Process> processList;
  
  // Get memory info form User
  cout << "Enter memory size: ";
  cin >> memorySize; 
  pageSize = getPageSize(memorySize);
  cout << "==============================================================================================" << endl;
  cout << "Initializing\nMemory Size: " << memorySize << "KB\npageSize: " << pageSize << "KB" << endl;

  // Read process info from file
  ifstream inFile;
  inFile.open("in1.txt"); 
  if (!inFile){
    cout << "Error opening file!" << endl;
    exit(1); 
  }
  vector<string> inLines;
  string str;
  while (std::getline(inFile, str)){
    inLines.push_back(str);
  }
  inFile.close();

  // Initialize Process objects with info pulled form the file
  processCount = initProc(inLines, processList);

  // TODO: Initialize memory object 
  // TODO: Initialize memory manager object 

  // TODO: while time < 1000000 
      // check arrivals
      // move to memory if possible
      // check terminations
  

  return 0;
}

int getPageSize(int memorySize) {
  vector<int> memFactors; 
  int halfMemory = (memorySize / 2) + 1;
  int factorCounter = 0;
  int userChoice;

  cout << "Select from available page sizes - note that smaller page sizes will be able to hold less data" << endl;
  cout << "==============================================================================================" << endl;

  // Find all factors of memorySize and add them to memFactors
  for (int i = 2; i < halfMemory; i++) {
    int k = 2;
    float multiple;
    do {

      multiple = i * k; 
      if (multiple == memorySize) {
        factorCounter++; 
        cout << "(" << factorCounter << ": " << i << ") ";
        memFactors.push_back(i);
        break;
      }
      else {
      k++;
      }
    } while (multiple < memorySize);
  }

  // Have user select page size from the available memFactors
  cout << endl; 
  cin >> userChoice;

  return memFactors[userChoice - 1];
}

int initProc(vector<string>& inLines, vector<Process>& processList) {
   int processCount = std::stoi(inLines[0]);
  
  for (int i = 1; i < inLines.size(); i++){
    int PID, arrivalTime, runTime, memorySegmentSize;

    PID = std::stoi(inLines[i]);
    i++;


    std::istringstream iss(inLines[i]);
    std::istream_iterator<string> begin(iss), end;
    vector<string> timeStats(begin, end);

    arrivalTime = std::stoi(timeStats[0]);
    runTime = std::stoi(timeStats[1]);
    i++;

    std::istringstream ss(inLines[i]);
    std::istream_iterator<string> start(ss), stop;
    vector<string> memStats(start, stop);

    memorySegmentSize = std::stoi(memStats[1]);
    for (int k = 1; k < std::stoi(memStats[0]); k++){
      memorySegmentSize += std::stoi(memStats[k + 1]);
    }
    i++;
    Process newProc = {PID, arrivalTime, runTime, memorySegmentSize};
    processList.push_back(newProc);
  }
  return processCount;
}