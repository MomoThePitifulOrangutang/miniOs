// FILE: utilities.h
// Isabella Geraci, Erin Kendall, & Sarah McLoney

#ifndef    UTILITIES_H
#define    UTILITIES_H

//#include "utilities.cpp"
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

typedef struct PCB {
	string pid;
	int cpuBurst;
	int arrival;
	int priority;
	int wait;
	bool used;
} PCB;

// readOnePCB
//	Reads the contents of a file and puts them in the PCB
//	Takes in a file and a pcb
void readOnePCB(istream& inFile, PCB& pcb);

// copyPCB
//	Takes in two PCBs
//	Does not return, but copies the first PCB to the second PCB
void copyPCB(PCB& orig, PCB& copy);

// updatePCBArr
//	Finds the PCB in the array with the same PID and replaces it
//	Takes in a PCB, an array of PCBs, and the number of PCBs in the array
void updatePCBArr(PCB modPCB, PCB pcbArr[], int numPCB);

// returnAWT
//	Calculates the average wait time of all processes in the array of PCBs
//	Takes in an array of PCBs and the number of PCBs in the array
//	Returns the average wait time of all of the processes
float returnAWT(PCB pcbs[], int numPCB);

// findPCBIndex
//	Loops through the array of PCBs, and finds the index of the PCB that matches the PCB inputted
//	Takes in an array of PCBs, a PCB, and the number of PCBs in the array
//	Returns the index of the PCB in the array
int findPCBIndex (PCB pcbArr[], PCB pcb, int numPCB);

// interrupt
//  Takes in an array of PCBs and the current time
//  Returns true if any of the arrival times in the array of PCBs is equal to the current time
bool interrupt (PCB pcbs[], int totalProcesses, int currentTime);

#endif
