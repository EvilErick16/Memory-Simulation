// Erick Juarez
// Juarez.erick16@gmail.com
// CPSC 351 Sec.01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

// Process structure definition
struct Process {
	int PID;
	int arrivalTime;
	int runTime;
	int memorySegmentSize;
};


// Memory class definition
class Memory {

private:

	// Private data used in the class 
	int memorySize;						// user selected memory size
	int pageSize;						// user selected page size
	int numberOfPages;					// number of pages. each page is of size pageSize
	vector<int> segmentStart;			// segmentStart and segmentEnd at a given index contain the start and end of each page segment 
	vector<int> segmentEnd;
	vector<bool> segmentAvailable;		// keeps track of what segments are used and which are available

public:

	// Default constructor
	Memory() {
		memorySize = 0;
		pageSize = 0; 
		numberOfPages = 0;
	}

	// Constructor
	Memory(int memSize, int pgSize){
		memorySize = memSize;
		pageSize = pgSize;
		numberOfPages = memorySize / pageSize;

		for (int i = 0; i < numberOfPages; i++) {
			segmentAvailable.push_back(true);
			if (i == 0){
				segmentStart.push_back(0);
				segmentEnd.push_back(pageSize - 1);
			}
			else {
				segmentStart.push_back(segmentStart[i-1] + pageSize);
				segmentEnd.push_back(segmentEnd[i-1] + pageSize);
			}
		}
	}

	// Function returns the number of pages needed by a process. input is the process memory segment size
	int getNumberOfPages(int segmentSize){
		if (segmentSize <= pageSize)
			return 1;
		else { 
			int pagesUsed = (segmentSize + pageSize - 1) / pageSize;
			return pagesUsed;
		}

	}

	// Function cheks if there are enough pages available for a process
	bool arePagesAvailable(int pagesNeeded){
		int availableSegments = 0;
		for (int i = 0; i < numberOfPages; i++){
			if (segmentAvailable[i] == true){
				availableSegments++;
				if (availableSegments >= pagesNeeded) {
					return true; 
				} 
			}
		}
		return false;
	}

	// Function adds process to memory, it assumes pages are available - checked by arePagesAvailable() function
	vector<int> addProcess(int pagesUsed){
		vector<int> indices;
		for (int i = 0; i < numberOfPages; i++){
			if (segmentAvailable[i] == true){
				segmentAvailable[i] = false;
				indices.push_back(i);
				if (indices.size() == pagesUsed){
					return indices;
				}
			}
		}
	}

	// Function removes a process from memory. input is a vector of all its indices
	void removeProcess(const vector<int>& indices){
		for (int i = 0; i < indices.size(); i++){
			segmentAvailable[i] = true; 
		}
	}

	// Function returns a vector containing the start and end of a page segment given an index
	vector<int> getSegmentRange(int index){
		vector<int> segmentRange;
		segmentRange.push_back(segmentStart[index]);
		segmentRange.push_back(segmentEnd[index]);
		return segmentRange;
	}

	// The following are getter functions to access the class's private variables 
	int getMemorySize(){
		return memorySize;
	}

	int getPageSize(){
		return pageSize;
	}

	int getNumberOfPages(){
		return numberOfPages;
	}

	vector<int> getSegmentStart(){
		return segmentStart;
	}

	vector<int> getSegmentEnd(){
		return segmentEnd;
	}

	vector<bool> getSegmentAvailable(){
		return segmentAvailable;
	}

	// The following are setter functions
	void setMemVars(int mSize, int pgSize, int numPages){
		this->memorySize = mSize;
		this->pageSize = pgSize;
		this->numberOfPages = numPages; 
	}

	void setSegmentVectors(const vector<int>& start, const vector<int>& end, const vector<bool>& available) {
		this->segmentStart = start;
		this->segmentEnd = end; 
		this->segmentAvailable = available; 
	}
};
