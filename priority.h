// FILE: priority.h
// Isabella Geraci, Erin Kendall, & Sarah McLoney

#include "utilities.h"
#ifndef    PRIORITY_H
#define    PRIORITY_H

// nonpreemptivePriority
//  Simulates running a list of processes in order of Priority without preemption and calculates the average wait time
//  Takes in an array of PCBs, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float nonpreemptivePriority (PCB pcbs[], int numProcesses, bool verbose);

// preemptivePriority
//  Simulates running a list of processes in order of Priority with preemption and calculates the average wait time
//  Takes in an array of PCBs, the number of PCBs, and whether or not the output should be verbose
//  Prints out each process and its wait time if bool verbose is true
//  Returns the average wait time for all processes
float preemptivePriority (PCB pcbs[], int numProcesses, bool verbose);

// priorityComparison
//  Takes in two PCBs
//  Returns true if the priority of a is greater than or equal to the priority of b
//  Returns true if the first PCB's priority is greater than the second PCB's priority
//  Returns true if the PCB's have the same priority and the first PCB's pid is less than the second PCB's pid
//  Otherwise, returns false
bool priorityComparison (PCB& a, PCB& b);

#endif
