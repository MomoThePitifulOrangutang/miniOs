// FILE: miniOS.h
// J Hall, Transy U
// CS 3074, Fall 2023
//
//
//	Interface for the miniOS file
//
//

#ifndef MINIOS_H
#define MINIOS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <queue>
#include <vector>
#include "symConsts.h"
#include "PCBQueue.h"
#include "utilities.h"
#include "fcfs.h"
#include "sjf.h"
#include "priority.h"
#include "rr.h"
#include "Frame.h"
#include "fifo.h"
#include "lru.h"
#include "mfu.h"
#include "random.h"

using namespace std;

// argErrorChecker fn takes in the size of the argument list, the command line argument list array, useDefaultFile flag, the file name, the inputFile, the type, the number of frames, the number of pages, the frame size, the verbose flag, and the flags of each command line argument that requires a specifier after. This fn checks all elements of the argument list for errors through the use of other error checking functions defined below. If verbose was inputted on command line, this fn also sets verbose flag to true. A call to this function can either cause the program to exit due to an error being found, or the fn returns nothing
void argErrorChecker (int argCount, char** argList, bool& useDefaultFile, char* file, ifstream& inFile, char* schedulerType, int& quanta, char* pagerType, int& frames, int& pages, int& frameSize, bool& schedulerTypeSpecified, bool& quantaSpecified, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified, bool& verbose, bool& preemptive);

// checkIfArgThatNeedsSpecifier fn takes in the the last index of the command line argument list, the index of the current command line argument in the command line argument list, the current command line argument, and the command line argument list, the useDefaultFile flag, the type, the number of frames, the number of pages, the frame size, and the flags of each command line argument that requires a specifier after. This fn checks if the current command line argument is one of the four that needs a specifier after it. If so, it calls other error checking functions to ensure that this command line argument was inputted properly. This function either causes the program to exit if an error is found, returns true if current command line argument is one of the four that needs a specifier and no errors were found, or returns false if the current command line argument is not one of the four that need specifiers after them
bool checkIfArgThatNeedsSpecifier (int lastArgIndex, int currentArgIndex, const char* currentArg, char** argList, bool& useDefaultFile, char* schedulerType, int& quanta, char* pagerType, int& frames, int& pages, int& frameSize, bool& schedulerTypeSpecified, bool& quantaSpecified, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified);

// printAlreadySpecifiedError fn takes in the current command line argument. This fn prints an error message unique to that command line argument, stating that this command line argument has already been specified before, then exits the program. Returns nothing
void printAlreadySpecifiedError (const char* currentArg);

// argIsLastArg fn takes in the current command line argument's index in the command line argument list and the last index of the command line argument list. This fn checks if the current command line argument's index is equal to the last command line argument's index. Returns true if so, false otherwise
bool argIsLastArg (int lastArgIndex, int currentArgIndex);

// printArgNotSpecifiedError takes in the current command line argument. This fn prints an error message unique to the command line argument stating that this command line argument needs a specifier but that one is not provided, then exits the program. Returns nothing
void printArgNotSpecifiedError (const char* arg);

// valueIsFloat fn takes in a string. This fn checks if the given value is a float or an invalid integer. Returns true if so, false otherwise
bool valueIsFloat (const char* value);

// nextArgIsLastArg fn takes in the current command line argument's index in the command line argument list and the last index in the command line argument list. This fn checks to see if the command line argument after the current command line argument is the last command line argument in the command line argument list. Returns true if so, false otherwise
bool nextArgIsLastArg (int lastArgIndex, int nextArgIndex);

// invalidSchedulerType fn takes in a type string. This fn checks if this string is a valid scheduler type input. Returns false if it is valid, true if invalid
bool invalidSchedulerType (string schedulerType);

// invalidPagerType fn takes in a type string. This fn checks if this string is a valid pager type input. Returns false if it is valid, true if invalid
bool invalidPagerType (string type);

// powerOfTwo fn takes in the frame size. This fn checks if the given integer for frameSize is a power of two. Returns true if so, false otherwise. Figured out how to do this check from source https://www.geeksforgeeks.org/program-to-find-whether-a-given-number-is-power-of-2/, accessed Nov 11, 2023.
bool powerOfTwo (int frameSize);

// checkIfLooseSpecifierOrTypo fn takes in the current command line argument's index of the command line argument list and the command line argument list. This fn checks if the current command line argument is a specifier command line argument without its precursor command line argument, or if anything is spelled wrong. Returns true if any typos or loose specifiers found, returns false otherwise
bool checkIfLooseSpecifierOrTypo (int currentIndex, char** argList);

// argVerifier fn takes in the specified scheduling type, the flag indicating whether or not '--quanta' has appeared in the command line, the preemptive flag and the file name. This fn checks if quanta was specified for a scheduling type that does not require a quanta, if preemptive was set to true for scheduling type FCFS, and if the file is not openable. Returns false if any of the above are true, true otherwise
bool argVerifier (char* schedulingType, bool& quantaSpecified, bool& preemptive, char* file, ifstream& inFile);

// readInputFile fn takes in 
void readInputFile (ifstream& inFile, string pid, string& pidNum, int& pidNumber, int& processCount, PCB* pcbs, int& pcbArrayIndex, string arrTime, int& arrTimeNum, string burTime, int& burTimeNum, string priority, int& priorityNum, char* schedulerType, PCBQueue& pcbQueue, string address, double addressNum, int frameSize, int pages, queue<string>& addresses);

// pidChecker fn takes in the first string of the input file and an empty string to fill. This fn checks if this string is of proper form ('P_<pidInteger>'). Returns true if so, false otherwise
bool pidChecker (string pid, string& pidNum);

// printFileFormatError fn takes in nothing. This fn prints an error message stating that the file is formatted incorrectly, and exits the program. Returns nothing
void printFileFormatError (void);

// validArrTime fn takes in the arrival time string. This fn checks if this value is an integer, and if this value is greater than or equal to 0. Returns true if so, false otherwise
bool validArrTime (string arrTime, int& arrTimeNum);

// validBurTime fn takes in the burst time string. This fn checks if this value is an integer, and if this value is greater than 0. Returns true if so, false otherwise
bool validBurTime (string burTime, int& burTimeNum);

// validPriority fn takes in the priority string. This fn checks if this value is an integer, and if this value is greater than or equal to 0, and less than or equal to 100. Returns true if so, false otherwise
bool validPriority (string priority, int& priorityNum);

// ensureAddressIsValid fn takes in an address string, a double to be set within the function, the frame size and the number of pages. This fn checks if the address is just an integer, and if this integer is outside the bounds of virtual memory. Returns true if address is an integer and is within the bounds of virtual memory, returns false otherwise
void ensureAddressIsValid (string address, double addressNum, int& frameSize, int& pages);

// stringIsZero fn takes in a string. This fn checks to see if the string is anything but zero. Returns true if the string is just zero or a bunch of 0s, returns false otherwise
bool stringIsZero (string str);

// schedule fn
void schedule (char* schedulerType, double& avgWaitTime, PCB* pcbs, int& processCount, bool& verbose, bool& preemptive, int& quanta);

// emptyQueue fn takes in a queue. This fn pops the queue until it is empty. Returns nothing
void emptyQueue (queue<string>& queue);

// page fn 
void page (Frame* frameTable, Page* pageTable, int frames, int pages, int frameSize, char* pagerType, PCBQueue& pcbQueue, int& foundPid, int& foundBurTime, int foundPriority, queue<string>& foundAddresses, int& pageFaultCount);

// initializeTables fn
void initializeTables (Frame* frameTable, Page* pageTable, int frames, int pages, int frameSize);

#endif
