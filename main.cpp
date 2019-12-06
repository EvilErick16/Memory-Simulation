// Erick Juarez
// Juarez.erick16@csu.fullerton.edu
// CPSC 351 Sec 01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

// Library Dependencies
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "memory.h"

////////////////////////////////////////////////////////////////////////////////////
// This file contains the main function of the program
/////////////////////////////////////////////////////////////////////////////////////

/*    Pseudo code for main
    1. get memory size
    2. find valid factors to memoy size to be the page size
    3. let USER pick page size from valid factors fuoind in step 2
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
void findFactors(int);

int main(){

    int memorySize = 0;
  
    cout << "Enter memory size: ";
    cin >> memorySize; 


  return 0;
}


void findFactors(int memorySize) {

  for (int i = 2; i < memorySize; i++) {

    int k = 2;
    float multiple;

    do {

      multiple = i * k; 

      if (multiple == memorySize) {
        cout << "Factors of " << memorySize << ": " << i << "*" << k << endl;
      }

      else {
      k++;
      }
    } while (multiple < memorySize);
  }
  cout << "You entered a Prime number, please select another number" << enld; 
}
