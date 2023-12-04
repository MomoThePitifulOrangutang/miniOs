// FILE: pager.cpp
// J Hall, K Goebel, M Baird, Transy U
// CS 3074, Fall 2023
//
//
//	Driver for the miniature operating system simulator project (miniOS)
//
//	This program takes in a list of argument inputs from the command line and simulates a miniature operating system by simulating a scheduling 
//	algorithm of processes for execution in a CPU, while also simulating a page replacement algorithm for each process scheduled. 
//
//	This program ONLY takes in command line arguments of the form '--pagerType' followed by one of the following appropriate pager types: FIFO, LRU, MFU or Random, 
//      and of the form '--frames' followed by an integer, and of the form '--pages' followed by an integer, and of the form '--framesize' followed by an 
//	integer that is also a power of two, and of the form '--verbose' (if additional output is desired). This program can also take in a desired input file 
//	to be used in the program, so long as this file's name is the LAST argument specified on the command line, and it fits the proper form. An input file
//	of proper form will always have ONLY two characters of the form 'P_', followed by an integer, as the first element of the file. All subsequent elements
//	will just be integer values. All of these subsequent integers must yield a result smaller than the number of pages when divided by the integer following 
//	the '--framesize' argument.  
//	Any other inputs to the command line will result in an error message followed by the program exiting.
//
//	Should the user NOT enter any arguments into the command line, each of the appropriate arguments will default to some value. '--pagerType' will deafult to FIFO,
//	'--frames' will default to 3, '--pages' will default to 8, '--framesize' will default to 512, '--verbose' will default to false, and if no input file is
//	specified, the input file will default to pager.in.
//

#include "miniOS.h"
using namespace std;	

int main (int argc, char** argv) {
  char schedulerType[CHAR_MAX] = SCHEDULER_TYPE_DEFAULT;
  char pagerType[CHAR_MAX] = PAGER_TYPE_DEFAULT;
  char file[CHAR_MAX] = INPUT_FILE_DEFAULT;
  int quanta = QUANTA_DEFAULT;
  int frames = FRAMES_DEFAULT;
  int pages = PAGES_DEFAULT;
  int frameSize = FRAMESIZE_DEFAULT;
  int processCount = 0;
  int pcbArrayIndex = 0;
  bool preemptive = PREEMPTIVE_DEFAULT;
  bool verbose = VERBOSE_DEFAULT;
  bool schedulerTypeSpecified = false;
  bool quantaSpecified = false;
  bool pagerTypeSpecified = false;
  bool framesSpecified = false;
  bool pagesSpecified = false;
  bool frameSizeSpecified = false;
  bool useDefaultFile = false;
  string pidNum = "";
  ifstream inFile;
  int arrTimeNum, burTimeNum, priorityNum;
  double addressNum, avgWaitTime;
  string pid, arrTime, burTime, priority, address;
  PCB pcbs[MAX_PCBS];	// due to design of the schedulers, cannot avoid statically allocating an array that will take up more memory than necessary to run the program
  queue<string> addresses;
  
  argErrorChecker (argc, argv, useDefaultFile, file, inFile, schedulerType, quanta, pagerType, frames, pages, frameSize, schedulerTypeSpecified, quantaSpecified, pagerTypeSpecified, framesSpecified, pagesSpecified, frameSizeSpecified, verbose, preemptive); 
  readInputFile(inFile, pid, pidNum, processCount, pcbs, pcbArrayIndex, arrTime, arrTimeNum, burTime, burTimeNum, priority, priorityNum, address, addressNum, frameSize, pages, addresses);
  schedule(schedulerType, avgWaitTime, pcbs, processCount, verbose, preemptive, quanta);
//  page();
  
//  PageTable pageTable(pages);	    
  return 0;
}

void argErrorChecker (int argCount, char** argList, bool& useDefaultFile, char* file, ifstream& inFile, char* schedulerType, int& quanta, char* pagerType, int& frames, int& pages, int& frameSize, bool& schedulerTypeSpecified, bool& quantaSpecified, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified, bool& verbose, bool& preemptive) {
  for (int i=1; i < argCount; ++i) {
    if (checkIfArgThatNeedsSpecifier((argCount - 1), i, argList[i], argList, useDefaultFile, schedulerType, quanta, pagerType, frames, pages, frameSize, schedulerTypeSpecified, quantaSpecified, pagerTypeSpecified, framesSpecified, pagesSpecified, frameSizeSpecified)) {
    }
    
    else if (!strcmp(argList[i], PREEMPTIVE)) {
      preemptive = true;
    }
    
    else if (!strcmp(argList[i], VERBOSE)) {
      verbose = true;
    }
    
    else if ((i == (argCount - 1)) && (!useDefaultFile)) {
      strcpy(file, argList[(i)]);
    }
    
    else if (checkIfLooseSpecifierOrTypo(i, argList)) {
       exit(1);
    }
  }
  
  if (!argVerifier(schedulerType, quantaSpecified, preemptive, file, inFile)) {
    exit(1);
  }
}

bool checkIfArgThatNeedsSpecifier (int lastArgIndex, int currentArgIndex, const char* currentArg, char** argList, bool& useDefaultFile, char* schedulerType, int& quanta, char* pagerType, int& frames, int& pages, int& frameSize, bool& schedulerTypeSpecified, bool& quantaSpecified, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified) {
  if (!strcmp(currentArg, SCHEDULER_TYPE)) {
    if (schedulerTypeSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    schedulerTypeSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Scheduler Type";
      printArgNotSpecifiedError(currentArg);
    }
    
    strcpy(schedulerType, argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if (invalidSchedulerType(schedulerType)) {
      cout << endl << "Specified scheduler type is not a valid scheduler type. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--schedulerType', separated by a space, and is one of the following scheduler types: 'FCFS', 'SJF', 'Priority', 'RR'." << endl << endl;
        exit(1);
    } 
    
    return true;
  } 
  
  else if (!strcmp(currentArg, QUANTA)) {
    if (quantaSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    quantaSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Quanta value";
      printArgNotSpecifiedError(currentArg);
    }
    
    quanta = atoi(argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if ((quanta < 1) || (valueIsFloat(argList[(currentArgIndex + 1)]))) {
      cout << endl << "Quanta value specified is invalid. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--quanta', separated by a space, and that this value is ONLY an integer greater than 0." << endl << endl;
      exit(1);
    }
    
    return true;
  }

  if (!strcmp(currentArg, PAGER_TYPE)) {
    if (pagerTypeSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    pagerTypeSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Pager Type";
      printArgNotSpecifiedError(currentArg);
    }
    
    strcpy(pagerType, argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if (invalidPagerType(pagerType)) {
      cout << endl << "Specified pager type is not a valid pager type. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--pagerType', separated by a space, and is one of the following pager types: 'FIFO', 'LRU', 'MFU', 'Random'." << endl << endl;
        exit(1);
    } 
    
    return true;
  } 
   
  else if (!strcmp(currentArg, FRAMES)) {
    if (framesSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    framesSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Number of frames";
      printArgNotSpecifiedError(currentArg);
    }
    
    frames = atoi(argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if ((frames > MAX_FRAMES) || (frames < 1) ||(valueIsFloat(argList[(currentArgIndex + 1)]))) {
      cout << endl << "Number of frames specified is invalid. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--frames', separated by a space, and that this value is ONLY an integer within the range of 1 to " << MAX_FRAMES << "." << endl << endl;
      exit(1);  
    }
   
    return true;
  } 
   
  else if (!strcmp(currentArg, PAGES)) {
    if (pagesSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    pagesSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Number of pages";
      printArgNotSpecifiedError(currentArg);
    }
    
    pages = atoi(argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if ((pages < 1) || (valueIsFloat(argList[(currentArgIndex + 1)]))) {
      cout << endl << "Number of pages specified is invalid. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--pages', separated by a space, and that this value is ONLY an integer greater than 0." << endl << endl;
      exit(1);
    }
    
    return true;
  }
   
  else if (!strcmp(currentArg, FRAMESIZE)) {
    if (frameSizeSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    frameSizeSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Frame size";
      printArgNotSpecifiedError(currentArg);
    }
    
    frameSize = atoi(argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if ((valueIsFloat(argList[(currentArgIndex + 1)])) || (frameSize < 1) || (!powerOfTwo(frameSize))) {
      cout << endl << "Size of frame specified is invalid. Please retry." << endl
           << "Frame sizes are always an integer power of the number two. Ensure that this is the case for the input." << endl << endl;
      exit(1);
    }
    
    return true;
  }
   
  return false;
}

void printAlreadySpecifiedError (const char* currentArg) {
  cout << endl << "Argument '" << currentArg << "' can only be specified once. Please retry." << endl << endl;
  exit(1); 
}

bool argIsLastArg (int lastArgIndex, int currentArgIndex) {
  if (currentArgIndex == lastArgIndex) {
    return true;
  }
  
  return false;
}

void printArgNotSpecifiedError (const char* arg) {    
  cout << " was not specified. Please retry." << endl << "Ensure that this value is specified directly after argument '" << arg << "', separated by a space." << endl << endl;
  exit(1);
}

bool valueIsFloat (const char* value) {
  int strLength = strlen(value);
  for (int i=0; i < strLength; ++i) {
    if ((value[i] == '.') || (value[i] == ',')) {
      return true;
    }
  }
  
  return false;
}

bool nextArgIsLastArg (int lastArgIndex, int nextArgIndex) {
  if (nextArgIndex == lastArgIndex) {
    return true;
  }
  
  return false;
}

bool invalidSchedulerType (string schedulerType) {
  if ((strcmp(schedulerType.c_str(), SCHEDULER_TYPE_DEFAULT)) && (strcmp(schedulerType.c_str(), SJF)) && (strcmp(schedulerType.c_str(), PRIORITY)) && (strcmp(schedulerType.c_str(), RR))) {
    return true;
  }
  
  return false;
}

bool invalidPagerType (string pagerType) {
  if ((strcmp(pagerType.c_str(), PAGER_TYPE_DEFAULT)) && (strcmp(pagerType.c_str(), LRU)) && (strcmp(pagerType.c_str(), MFU)) && (strcmp(pagerType.c_str(), RANDOM))) {
    return true;
  }
  
  return false;
}

bool powerOfTwo (int frameSize) {
  if ((ceil(log2(frameSize))) == (floor(log2(frameSize)))) {
    return true;
  }
  
  else {
    return false;
  }
}

bool checkIfLooseSpecifierOrTypo (int currentIndex, char** argList) {
  if ((!strcmp(argList[(currentIndex - 1)], SCHEDULER_TYPE)) || (!strcmp(argList[(currentIndex - 1)], PAGER_TYPE)) || (!strcmp(argList[(currentIndex - 1)], FRAMES)) || (!strcmp(argList[(currentIndex - 1)], PAGES)) || (!strcmp(argList[(currentIndex - 1)], FRAMESIZE))) {
    return false;
  } 
   
  else {
    cout << endl << "No loose specifiers or typos allowed.  Please retry." << endl
         << "Ensure that any specifier arguments are directly after the appropriate argument of form '--<argumentType>', separated by a space, and that a file argument is the LAST in the argument list." << endl << endl;
    return true;
  }
}

bool argVerifier (char* schedulerType, bool& quantaSpecified, bool& preemptive, char* file, ifstream& inFile) {
  if (quantaSpecified) {
    if ((schedulerType == SCHEDULER_TYPE_DEFAULT) || (schedulerType == SJF) || (schedulerType == PRIORITY)) {
      cout << endl << "Scheduler type '" << schedulerType << "' does not need a quanta. Please retry." << endl
           << "Ensure that quanta is only specified if scheduler type is RR." << endl << endl;
      return false;
      }
  }
  
  if ((preemptive) && (schedulerType == SCHEDULER_TYPE_DEFAULT)) {
    cout << endl << "Scheduler type '" << schedulerType << "' cannot be preemptive by definition. Please retry." << endl
         << "Ensure that preemptive is only specified when scheduler type is SJF or Priority (RR is preemptive by definition)" << endl << endl;
    return false;
  }
  
  inFile.open(file);
  if (!inFile.is_open()) {
    cout << endl << "Unable to open file. Please retry." << endl
         << "Either the file is not in the directory, or the specified file name is invalid." << endl << endl;
    return false;
  }
  
  return true;
}

void readInputFile (ifstream& inFile, string pid, string pidNum, int& processCount, PCB* pcbs, int& pcbArrayIndex, string arrTime, int& arrTimeNum, string burTime, int& burTimeNum, string priority, int& priorityNum, string address, double addressNum, int frameSize, int pages, queue<string>& addresses) {
  inFile >> pid;
  while (!inFile.eof()) {
    if (!pidChecker(pid, pidNum)) {
      printFileFormatError();
    }
    
    ++processCount;
    pcbs[pcbArrayIndex].pid = pid;
    inFile >> arrTime;
    if (!validArrTime(arrTime, arrTimeNum)) {
      printFileFormatError();
    }
    
    pcbs[pcbArrayIndex].arrival = arrTimeNum;
    inFile >> burTime;
    if (!validBurTime(burTime, burTimeNum)) {
      printFileFormatError();
    }
    
    pcbs[pcbArrayIndex].cpuBurst = burTimeNum;
    inFile >> priority;
    if (!validPriority(priority, priorityNum)) {
      printFileFormatError();
    }
    
    pcbs[pcbArrayIndex].priority = priorityNum;
    pcbs[pcbArrayIndex].wait = 0;
    pcbs[pcbArrayIndex].used = false;
    ++pcbArrayIndex; 
    inFile >> address;
    for (int i=0; i < burTimeNum; ++i) {
      if (inFile.eof()) {
        printFileFormatError();
      }
      
      ensureAddressIsValid(address, addressNum, frameSize, pages);
      addresses.push(address);
      inFile >> address;
    } 
    
//    cout << endl << pcbs[(pcbArrayIndex -1)].pid << endl << pcbs[(pcbArrayIndex -1)].arrival << endl << pcbs[(pcbArrayIndex -1)].cpuBurst << endl << pcbs[(pcbArrayIndex -1)].priority << endl;
  }
  
//  for (int i =0; i < addresses.size(); ++i) {
//    cout << endl << addresses.front();
//    addresses.push(addresses.front());
//    addresses.pop();
//  }
}

bool pidChecker (string pid, string& pidNum) {
  for (int i=2; i < pid.length(); ++i) {
    pidNum = pidNum + pid[i];
  }
  
  if ((pid[0] != 'P') || (pid[1] != '_') || ((!stringIsZero(pidNum)) && (!atoi(pidNum.c_str())))) {
    pidNum = "";
    return false;
  }
  
  pidNum = "";
  return true;
}

void printFileFormatError (void) {
  cout << endl << "This file is not of proper format. Please retry." << endl
         << "Proper files fit the form: P_<pidInteger> followed by <arrivalTimeInteger>, <burstTimeInteger(greater than 0)>, <priorityInteger(between 0 and 100)>," << endl
         << "and a number of addresses equal to the <burstTimeInteger>, all in the form of integers, each separated by a space." << endl << endl;
    exit(1);
}

bool validArrTime (string arrTime, int& arrTimeNum) {
  arrTimeNum = atoi(arrTime.c_str());
  if ((valueIsFloat(arrTime.c_str())) || ((!stringIsZero(arrTime)) && (arrTimeNum == 0)) || (arrTimeNum < 0)) {
    return false;
  }
  
  return true;
}

bool validBurTime (string burTime, int& burTimeNum) {
  burTimeNum = atoi(burTime.c_str());
  if ((valueIsFloat(burTime.c_str())) || (burTimeNum < 1)) {
    return false;
  }
  
  return true;
}

bool validPriority (string priority, int& priorityNum) {
  priorityNum = atoi(priority.c_str());
  if ((valueIsFloat(priority.c_str())) || ((!stringIsZero(priority)) && (priorityNum == 0)) || (priorityNum < 0) || (priorityNum > 100)) {
    return false;
  }
  
  return true;
}

void ensureAddressIsValid (string address, double addressNum, int& frameSize, int& pages) {
  addressNum = atof(address.c_str());
  if ((valueIsFloat(address.c_str())) || ((!stringIsZero(address)) && (addressNum == 0))) {
    printFileFormatError();
  }  
    
  if ((addressNum/frameSize) > pages) {
    cout << endl << "Address " << address << " is not a valid address. Please retry." << endl
         << "Ensure that for all addresses of the input file, when the address is divided by the framesize, it does not exceed the number of pages." << endl << endl;
    exit(1); 
  }
}

bool stringIsZero (string str) {
  for (int i=0; i < str.length(); ++i) {
    if (str[i] != '0') {
      return false;
    }
  }
  
  return true;
}

void schedule (char* schedulerType, double& avgWaitTime, PCB* pcbs, int& processCount, bool& verbose, bool& preemptive, int& quanta) {
  if (!strcmp(schedulerType, SCHEDULER_TYPE_DEFAULT)) {
    avgWaitTime = fcfs(pcbs, processCount, verbose);
    cout << endl << "Average Wait Time: " << avgWaitTime << endl;
  }
  
  else if (!strcmp(schedulerType, SJF)) {
    if (preemptive) {
      avgWaitTime = preemptiveSjf(pcbs, processCount, verbose);
      cout << endl << "Average Wait Time: " << avgWaitTime << endl;
    }
    
    else {
      avgWaitTime = nonpreemptiveSjf(pcbs, processCount, verbose);
      cout << endl << "Average Wait Time: " << avgWaitTime << endl;
    }
  }
  
  else if (!strcmp(schedulerType, PRIORITY)) {
    if (preemptive) {
      avgWaitTime = preemptivePriority(pcbs, processCount, verbose);
      cout << endl << "Average Wait Time: " << avgWaitTime << endl;
    }
    
    else {
      avgWaitTime = nonpreemptivePriority(pcbs, processCount, verbose);
      cout << endl << "Average Wait Time: " << avgWaitTime << endl;
    }
  }
  
 else if (!strcmp(schedulerType, RR)) {
    avgWaitTime = rr(pcbs, quanta, processCount, verbose);
    cout << endl << "Average Wait Time: " << avgWaitTime << endl;
  }
}
