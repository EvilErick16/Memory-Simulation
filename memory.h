// Erick Juarez
// Juarez.erick16@gmail.com
// CPSC 351 Sec.01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

#pragma once

#include <vector>
using std::vector;

class Memory {

    private:

	int memorySize;
	int pageSize;
	int numberOfPages;
	vector<int> segmentNames;

    public:

	Memory() {
	    memorySize = 0;
	    pageSize = 0;
	    numberOfPages = 0;
	   // segmentNames = new vector<int>; 
	}

	void setMemorySize(int memSize) {
	    memorySize = memSize;
	}

	int getMemorySize() {
	    return memorySize;
	}


};
