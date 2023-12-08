// FILE: fcfs.h
// Isabella Geraci, Erin Kendall, & Sarah McLoney

#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include "utilities.h"
#include <iostream>
using namespace std;

// fcfs
//  Simulates running a list of processes in First Come First Serve order and calculates the average wait time
//  Takes in an array of PCBs, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float fcfs (PCB pcbs[], int numProcesses, bool verbose);

#endif
