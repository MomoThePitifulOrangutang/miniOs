// FILE: sjf.h
// Isabella Geraci, Erin Kendall, & Sarah McLoney

#ifndef    SJF_H
#define    SJF_H

#include <queue>
#include <algorithm>
#include "utilities.h"

#include <iostream>
using namespace std;

// nonpreemptiveSjf
//  Simulates running a list of processes in order of Shortest Job First and calculates the average wait time
//  Takes in an array of PCBs, a quanta, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float nonpreemptiveSjf (PCB pcbs[], int lines, bool verbose);

// preemptiveSjf
//  Simulates running a list of processes in order of CPU burst with preemption and calculates the average wait time
//  Takes in an array of PCBs, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float preemptiveSjf (PCB pcbs[], int numProcesses, bool verbose);

// interrupt
//  Takes in an array of PCBs and the current time
//  Returns true if any of the arrival times in the array of PCBs is equal to the current time
bool interrupt (PCB pcbs[], int totalProcesses, int currentTime);

// sjfComparison
//  Takes in two PCBs
//  Returns true if the first PCB's CPU burst is less than the second PCB's
//  Returns true if the PCB's have the same burst and the first PCB's pid is less than the second PCB's
//  Otherwise, returns false
bool sjfComparison (PCB& a, PCB& b);

#endif
