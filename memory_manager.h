// Erick Juarez
// Juarez.erick16@gmail.com
// CPSC 351 Sec.01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

#pragma once

#include "memory.h"

// TODO: Finish memory manager class definition
class MemoryManager {

private:
	
	Memory memory;						// memory object defined in memory.h
	vector<Process> listOfProcesses;	// Vector of Process objects, defined in memory.h
	vector<int> inputQueue;				// Vector of ints holds PIDs of Process objects waiting in the queue
	vector<vector<string>> events; 		// 2D vector that keeps track of all the Arrivals, Movements to Memory, and Terminations

public: 

	// Constructor 
	MemoryManager(const vector<Process>& processes, Memory& mem){
		this->listOfProcesses = processes;
		this->memory.setMemVars(mem.getMemorySize(), mem.getPageSize(), mem.getNumberOfPages());
		this->memory.setSegmentVectors(mem.getSegmentStart(), mem.getSegmentEnd(), mem.getSegmentAvailable()); 
	}

	// Function checks if a process arrived at given time. If a process arrives, it will add elements to events vector
	void checkArrivals(int time);

	// TODO: Finish MovetoMemIfPossible implementation
	void moveToMemIfPossible(int time);
	
	// TODO: Finish check Terminations implementation
	void checkTerminations(int time);
};



void MemoryManager::checkArrivals(int time){

	// For every process in the list
	for (int i = 0; i < listOfProcesses.size(); i++){
		
		// Is the current process arriving at this time
		if (listOfProcesses[i].arrivalTime == time){

			// If current process is arriving at this time, add its PID to the input Queue
			inputQueue.push_back(listOfProcesses[i].PID);

			// Check if events vector is empty 
			if (events.empty()){
 					
				// If events vector is empty, add a new element to it
				// First element of events vector is the time at which the event happened
				events.push_back(vector<string> ());
				events[0].push_back(std::to_string(time));
			}

			// The following for and if statements add strings to the events vector 
			bool inEvent = false;
			for (int k = 0; k < events.size(); k++){
					
				if (std::stoi(events[k][0]) == time){

					inEvent = true;
					 
					string text = "Process " + std::to_string(listOfProcesses[i].PID) + " arrives";
					events[k].push_back(text);
					cout << "Time: " << time << " " << text << endl;

					text = "\tInput Queue: [";
					for (int h = 0; h < inputQueue.size(); h++){
						if (h != 0){
							text += ", ";
						}
						text += std::to_string(inputQueue[h]);
					}
					text += "]";
					events[k].push_back(text);
					cout << text << endl;
				} 
			}
			if (!inEvent) {
				events.push_back(vector<string>());
				int lastIndex = events.size() - 1;
				events[lastIndex].push_back(std::to_string(time));

				string text = "Process " + std::to_string(listOfProcesses[i].PID) + " arrives";
				events[lastIndex].push_back(text);
				cout << "Time: " << time << " " << text << endl;

				text = "\tInput Queue: [";
				for (int h = 0; h < inputQueue.size(); h++){
					if (h != 0){
						text += ", ";
					}
					text += std::to_string(inputQueue[h]);
				}
				text += "]";
				events[lastIndex].push_back(text);
				cout << text << endl;
			}
		}
	}
}

// TODO: Finish MovetoMemIfPossible implementation
void MemoryManager::moveToMemIfPossible(int time){

}

// TODO: Finish check Terminations implementation
void MemoryManager::checkTerminations(int time) {

}