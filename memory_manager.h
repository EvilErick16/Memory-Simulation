// Erick Juarez
// Juarez.erick16@gmail.com
// CPSC 351 Sec.01 - Operating Systems
// Assignment 2 - Memory Manager Simulation

#pragma once

#include "memory.h"

// TODO: Finish memory manager class definition
class MemoryManager {

private:
	
	Memory memory;
	vector<Process> listOfProcesses;
	vector<int> inputQueue;
	vector<vector<string>> events; 		// 2D vector that keeps track of all the Arrivals, Movements to Memory, and Terminations

public: 

	// Constructor 
	MemoryManager(const vector<Process>& processes, Memory& mem){
		this->listOfProcesses = processes;
		this->memory.setMemVars(mem.getMemorySize(), mem.getPageSize(), mem.getNumberOfPages());
		this->memory.setSegmentVectors(mem.getSegmentStart(), mem.getSegmentEnd(), mem.getSegmentAvailable()); 
	}


	void checkArrivals(int time){

		//cout << "\nTime: " << time << endl;
		for (int i = 0; i < listOfProcesses.size(); i++){
			cout << "Process: " << listOfProcesses[i].PID;
			if (listOfProcesses[i].arrivalTime == time){
				cout << "\tProcess arrived" << endl;
				inputQueue.push_back(listOfProcesses[i].PID);
				if (events.empty()){
					cout << "events vect is empty, initializing" << endl; 
					events.push_back(vector<string> ());
					events[0].push_back(std::to_string(time));
				}

				for (int k = 0; k < events.size(); k++){
					cout << "Looking at element " << k << " of events vector";
					cout << "\tevents size:" << events.size() << "\t time: " << time << endl;
					if (std::stoi(events[k][0]) == time){

						cout << "Element " << k << " already has an entry with time = " << time << endl; 
						string text = "Process " + std::to_string(listOfProcesses[i].PID) + " arrives";
						events[k].push_back(text);
						cout << text << endl;

						text = "Input Queue: [";
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
						// TODO: FIX BUG RIGHT HERE 
					else {
						cout << "events[" << k << "][0] did not match time, creating new events entry..." << endl;
						events.push_back(vector<string> ());
						events[k + 1].push_back(std::to_string(time));
					}
				}
			}
		}

	}

	void moveToMemIfPossible(int time){

	}
	
	void checkTerminations(int time) {

	}
};