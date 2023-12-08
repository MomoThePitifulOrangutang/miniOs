// FILE: rr.h
// Isabella Geraci, Erin Kendall, & Sarah McLoney

#ifndef RR_H
#define RR_H

#include <queue>
#include "utilities.h"
#include <iostream>
using namespace std;

// rr
//  Simulates running a list of processes using Round Robin order and calculates the average wait time
//  Takes in an array of PCBs, a quanta, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float rr (PCB pcbs[], int quanta, int numProcesses, bool verbose);

#endif
