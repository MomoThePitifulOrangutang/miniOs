// FILE: miniOS.cpp
// J Hall, K Goebel, M Baird, Transy U
// CS 3074, Fall 2023
//
//
//	Driver for the miniature operating system simulator project (miniOS)
//
//	This program takes in a list of argument inputs from the command line and simulates a miniature operating system by simulating a scheduling 
//	algorithm of processes for execution in a CPU, while also simulating a page replacement algorithm for each process scheduled. 
//
//	This program ONLY takes in command line arguments of the form '--pagerType' followed by one of the following appropriate pagerTypes: FIFO, LRU, MFU or Random, 
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
  bool preemptive = PREEMPTIVE_DEFAULT;
  bool verbose = VERBOSE_DEFAULT;
  bool schedulerTypeSpecified = false;
  book quantSpecified = false;
  bool pagerTypeSpecified = false;
  bool framesSpecified = false;
  bool pagesSpecified = false;
  bool frameSizeSpecified = false;
  bool useDefaultFile = false;
  string pidNum = "";
  ifstream inFile;
  double addressNum;
  string pid, address;
  queue<int> addressQueue;
  PageReplacementSimulator simulator;
  
  argErrorChecker (argc, argv, useDefaultFile, file, inFile, pagerType, frames, pages, frameSize, pagerTypeSpecified, framesSpecified, pagesSpecified, frameSizeSpecified, verbose);
  inFile >> pid;
  pidChecker(pid, pidNum); 
  inFile >> address;
  while (!inFile.eof()) {
    ensureAddressIsValid(address, addressNum, frameSize, pages);
    addressQueue.push(addressNum);
    inFile >> address;
  }
  
  PageTable pageTable(pages);	    
  simulator.simulation(addressQueue, pid, pageTable, frames, pages, frameSize, verbose, pagerType);
  return 0;
}

void argErrorChecker (int argCount, char** argList, bool& useDefaultFile, char* file, ifstream& inFile, char* pagerType, int& frames, int& pages, int& frameSize, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified, bool& verbose) {
  for (int i=1; i < argCount; ++i) {
    if (checkIfArgThatNeedsSpecifier((argCount - 1), i, argList[i], argList, useDefaultFile, pagerType, frames, pages, frameSize, pagerTypeSpecified, framesSpecified, pagesSpecified, frameSizeSpecified)) {
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
  
  inFile.open(file);
  if (!inFile.is_open()) {
    cout << endl << "Unable to open file. Please retry." << endl
         << "Either the file is not in the directory, or the specified file name is invalid." << endl << endl;
    exit(1);
  }
}

bool checkIfArgThatNeedsSpecifier (int lastArgIndex, int currentArgIndex, const char* currentArg, char** argList, bool& useDefaultFile, char*& pagerType, int& frames, int& pages, int& frameSize, bool& pagerTypeSpecified, bool& framesSpecified, bool& pagesSpecified, bool& frameSizeSpecified) {
  if (!strcmp(currentArg, PAGER_TYPE)) {
    if (pagerTypeSpecified) {
      printAlreadySpecifiedError(currentArg);
    }
    
    pagerTypeSpecified = true;
    if (argIsLastArg(lastArgIndex, currentArgIndex)) {
      cout << endl << "Scheduling type";
      printArgNotSpecifiedError(currentArg);
    }
    
    strcpy(pagerType, argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if (invalidType(pagerType)) {
      cout << endl << "Specified scheduling pagerType is not a valid pagerType. Please retry." << endl
           << "Ensure that this value is specified directly after argument '--pagerType', separated by a space, and is one of the following pagerTypes: 'FIFO', 'LRU', 'MFU', 'Random'." << endl << endl;
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
    
    if ((frames > MAX_FRAMES) || (frames < 1)) {
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
    
    if (pages < 1) {
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
    
    if (valueIsFloat(currentArg)) {
      cout << endl << "Size of frame specified is of invalid pagerType. Please retry." << endl
           << "Ensure that this value is ONLY an integer." << endl << endl;
      exit(1);
    }
    
    frameSize = atoi(argList[(currentArgIndex + 1)]);
    if (nextArgIsLastArg(lastArgIndex, (currentArgIndex + 1))) {
      useDefaultFile = true;
    }
    
    if (frameSize < 1) {
      cout << endl << "Size of frame specified is invalid. Please retry." << endl
           << "Frame sizes are always a power of the number two. Ensure that this is the case for the input." << endl << endl;
      exit(1);
    } 
    
    if (!powerOfTwo(frameSize)) {
      cout << endl << "Size of frame specified is invalid. Please retry." << endl
           << "Frame sizes are always a power of the number two. Ensure that this is the case for the input." << endl << endl;
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

bool invalidType (string pagerType) {
  if ((strcmp(pagerType.c_str(), TYPE_DEFAULT)) && (strcmp(pagerType.c_str(), LRU)) && (strcmp(pagerType.c_str(), MFU)) && (strcmp(pagerType.c_str(), RANDOM))) {
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
  if ((!strcmp(argList[(currentIndex - 1)], TYPE)) || (!strcmp(argList[(currentIndex - 1)], FRAMES)) || (!strcmp(argList[(currentIndex - 1)], PAGES)) || (!strcmp(argList[(currentIndex - 1)], FRAMESIZE))) {
    return false;
  } 
   
  else {
    cout << endl << "No loose specifiers or typos allowed.  Please retry." << endl
         << "Ensure that any specifier arguments are directly after the appropriate argument of form '--<argumentType>', separated by a space, and that a file argument is the LAST in the argument list." << endl << endl;
    return true;
  }
}

void pidChecker (string pid, string pidNum) {
  if (pid[0] != 'P') {
    printFileFormatError();
  }
  
  if (pid[1] != '_') {
    printFileFormatError();
  }
  
  for (int i=2; i < pid.length(); ++i) {
    pidNum = pidNum + pid[i];
  }
  
  if ((!stringIsZero(pidNum)) && (!atoi(pidNum.c_str()))) {
    printFileFormatError();
  }
}

void printFileFormatError (void) {
  cout << endl << "This file is not of proper format. Please retry." << endl
         << "Proper files fit the form: P_<pidInteger> followed by addresses in the form of integers, each separated by a space." << endl << endl;
    exit(1);
}

void ensureAddressIsValid (string address, double& addressNum, int& frameSize, int& pages) {
  if (valueIsFloat(address.c_str())) {
    printFileFormatError();
  }
  
  addressNum = atof(address.c_str());
  if ((!stringIsZero(address)) && (!addressNum)) {
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
