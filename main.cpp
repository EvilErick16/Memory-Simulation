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
#include "memory_manager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file contains the main logic of the program                                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main function definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){

  // Declare variables
  int memorySize = 0;               // Memory size that is specified by the user
  int pageSize = 0;                 // Page size is a factor of memory size

  int processCount;                 // Number of processes that will be loaded 
  vector<Process> processList;      // List of processes. Process objects are defined in memory.h 
  
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
  vector<string> inLines;   // Each line from the input file is an element in the inLines vector
  string str;
  while (std::getline(inFile, str)){
    inLines.push_back(str);
  }
  inFile.close();

  // Initialize Process objects with info pulled form the file
  processCount = initProc(inLines, processList);

  // Initialize memory object 
  Memory mem = Memory(memorySize, pageSize);

  // Initialize memory manager object
  MemoryManager mm = MemoryManager(processList, mem);

  // TODO: while time < 1000000 
  for (int time = 0; time < 100000; time++){
    mm.checkArrivals(time);
  }

      // move to memory if possible
      // check terminations
  

  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function returns page size as an int. Parameter is memory size. Function calculates factors of the size and    //
// lets the user select one of the factors to be the page size                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getPageSize(int memorySize) {
  // Declare variables
  vector<int> memFactors;                   // Holds all factors of memory size, these are the options given to the user for selecting page size
  int halfMemory = (memorySize / 2) + 1;    // Since factors of a number are symmetrical, we only have to look at half of them
  int factorCounter = 0;                    // Keeps track of how many factors there are
  int userChoice;                           // User choice. It's the index to memFactors

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Initializes process objects. It returns the number of processes that were intialized as an int        //
// parameters are a vector of lines from the input file, and a list of processes passed by reference              // 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int initProc(vector<string>& inLines, vector<Process>& processList) {

  // First line in the input array contains the number of processes
  int processCount = std::stoi(inLines[0]);

  // Loop through vector that contains lines from the input and use data to intialize Process objects
  for (int i = 1; i < inLines.size(); i++){

    int PID, arrivalTime, runTime, memorySegmentSize;

    // First line of inLines is the Process ID (PID)
    PID = std::stoi(inLines[i]);
    i++;  // Increment i to access the next line of inLines 

    // Split the next line of inLines in a vector called timeStats
    std::istringstream iss(inLines[i]);
    std::istream_iterator<string> begin(iss), end;
    vector<string> timeStats(begin, end);
    // Frist element of this line is the arrival time and the second element is the run time. 
    arrivalTime = std::stoi(timeStats[0]);
    runTime = std::stoi(timeStats[1]);
    i++;  // Increment i to access the next line of inLines

    // Split this line of inLines into a vector called memStats
    std::istringstream ss(inLines[i]);  
    std::istream_iterator<string> start(ss), stop;
    vector<string> memStats(start, stop);

    // Second element of memStats is always a number containing memory segment size of this process
    memorySegmentSize = std::stoi(memStats[1]); 
    // If this process has more than one segment, add all the segments together to get the actual segment size
    for (int k = 1; k < std::stoi(memStats[0]); k++){
      memorySegmentSize += std::stoi(memStats[k + 1]);
    }
    i++;  // Increment i to skip the blank line in inLines 

    // Initialize process object and add it to the process list
    Process newProc = {PID, arrivalTime, runTime, memorySegmentSize};
    processList.push_back(newProc);
  }
  return processCount;
}