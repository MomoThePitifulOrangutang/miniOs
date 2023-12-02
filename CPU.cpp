// FILE: CPU.cpp
// Group 5, Transy U
// CS 3074, Fall 2023
//
//
//	Driver for the CPU Scheduler
//	
//	*our program does not print an error message if a type argument is entered as "--<type>" instead of "--type <type>"
//	*our program uses a parser instead of the typical method of reading a file. Simply forgot this method and didn't have time to edit this after realizing. This does not have an effect on the program's performance though.
//	*our SJFScheduler only works if preemptive flag is set to false. If preemptive is instead true, our program returns the same output as when preemptive is set to false. 
//	*our PriorityScheduler only works if preemptive flag is set to false. If preemptive is instead true, our program returns the same output as when preemptive is set to false.
//	*our RRScheduler does not work as Round Robin should. It operates exactly like FCFSScheduler. We got very close, but had to abandon the attempt simply due to running out of time to debug the logic.
//
//

#include <iostream>
#include <fstream>
#include <string.h>
#include "RRAndFCFSQueue.h"
#include "SJFQueue.h"
#include "PriorityQueue.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "PriorityScheduler.h"
#include "RRScheduler.h"
using namespace std;

const char* TYPE = "--type";
const char* PREEMPTIVE = "--preemptive";
const char* QUANTA = "--quanta";
const char* INPUT_FILE = "--file";
const char* VERBOSE = "--verbose";
const string SJF = "SJF";
const string PRIORITY = "Priority";
const string RR = "RR";
const string TYPE_DEFAULT = "FCFS";
const string QUANTA_DEFAULT = "10";
const string INPUT_FILE_DEFAULT = "sched.in";
const bool PREEMPTIVE_DEFAULT = false;
const bool VERBOSE_DEFAULT = false;
const bool QUANTA_FLAG_DEFAULT = false;

// argInputErrorChecker takes in a variety of information and performs various errors messages on the inputted information, returns true if no errors found, false otherwuse
bool argInputErrorChecker (string type, bool& preemptive, bool verbose, bool quantaFlag, int& quanta);

// fileParser takes in a string currentLine and parses out several variables, returns nothing
void fileParser (string currentLine, string& pid, string& arrTime, string& burTime, string& priority, int& index);

int main (int argc, char** argv) {
  string type = TYPE_DEFAULT;
  string quantaStr = QUANTA_DEFAULT;
  string file = INPUT_FILE_DEFAULT;
  bool preemptive = PREEMPTIVE_DEFAULT;
  bool verbose = VERBOSE_DEFAULT;
  bool quantaFlag = QUANTA_FLAG_DEFAULT;
  string pid, arrTime, burTime, priority, currentLine;
  int quanta, index, pidNum, arrTimeNum, burTimeNum, priorityNum, foundPid, foundArrTime, foundBurTime, foundPriority, test;
  ifstream inFile;
  RRAndFCFSQueue fcfsQueue, rrQueue;
  SJFQueue sjfQueue;
  PriorityQueue priQueue;
  FCFSScheduler fcfs;
  SJFScheduler sjf;
  PriorityScheduler pri;
  RRScheduler rr;
   
  for (int i=1; i < argc; ++i) {
    if (!strcmp(argv[i], TYPE)) {
      type = argv[(i+1)];
    }
	    
    else if (!strcmp(argv[i], PREEMPTIVE)) {
      preemptive = true;
    }
    
    else if (!strcmp(argv[i], QUANTA)) {
       quantaStr = argv[(i+1)];
       quantaFlag = true;
    }

    else if (!strcmp(argv[i], INPUT_FILE)) {
       file = argv[(i+1)];
       cout << endl << file << endl;
    }

    else if (!strcmp(argv[i], VERBOSE)) {
      verbose = true;
    }
  }

  // if no errors detected and file is openable, parses each line into a a queue of PCBs, passing this queue into our scheduler wrappers
  quanta = atoi(quantaStr.c_str());
  if (argInputErrorChecker(type, preemptive, verbose, quantaFlag, quanta)) {
    inFile.open(file);
    if (inFile.is_open()) {
      while (!inFile.eof()) {
	pid = "";
        arrTime = "";
        burTime = "";
        priority = "";
	getline(inFile, currentLine);
        fileParser(currentLine, pid, arrTime, burTime, priority, index);
        if ((pid != "") && (arrTime != "") && (burTime != "") && (priority != "")) {	// using inFile.eof() as a sentinel was causing an empty line to be read and inputted into a queue, this condition avoids that
          pidNum = atoi(pid.c_str());
          arrTimeNum = atoi(arrTime.c_str());
          burTimeNum = atoi(burTime.c_str());
          priorityNum = atoi(priority.c_str());
          if (type == TYPE_DEFAULT) {
            fcfsQueue.push(pidNum, arrTimeNum, burTimeNum, priorityNum);
          }
          
          else if (type == SJF) {
            sjfQueue.push(pidNum, arrTimeNum, burTimeNum, priorityNum);
          }
          
          else if (type == PRIORITY) {
            priQueue.push(pidNum, arrTimeNum, burTimeNum, priorityNum);
          }
          
          else if (type == RR) {
            rrQueue.push(pidNum, arrTimeNum, burTimeNum, priorityNum);
          }
        }      
      } 
	    
      if (type == TYPE_DEFAULT) {
        fcfs.wrapper(fcfsQueue, preemptive, verbose);
      }
      
      else if (type == SJF) {
        sjf.wrapper(sjfQueue, preemptive, verbose);
      }
      
      else if (type == PRIORITY) {
        pri.wrapper(priQueue, preemptive, verbose);
      }
      
      else if (type == RR) {
        rr.wrapper(rrQueue, quanta, preemptive, verbose);
      }
    }
	    
    else {
      cout << endl << "> ERROR: file '" << file << "' is not in directory! Please retry." << endl;
      exit(1);
    }
  }

  else {
    exit(1);
  }
    
  return 0;
}

// errorChecker function
bool argInputErrorChecker (string type, bool& preemptive, bool verbose, bool quantaFlag, int& quanta) {
  if ((type != TYPE_DEFAULT) && (type != SJF) && (type != PRIORITY) && (type != RR)) {
    cout << endl << "> ERROR: '" << type << "' is not a valid type. Please retry using 'FCFS', 'SJF', 'Priority' or 'RR'!" << endl;
    return false;
  }

  if (type == RR) {
    preemptive = true;
  }

  if (quanta <= 0) {
    cout << endl << "> ERROR: a quanta of 0 or less makes no sense! Please retry with appropriate arguments!" << endl;
    return false;
  }

  if (quantaFlag) {
    if ((type == TYPE_DEFAULT) || (type == SJF) || (type == PRIORITY)) {
      cout << endl << "> ERROR: Type '" << type << "' does not need a quanta, please retry with appropriate arguments!" << endl;
      return false;
      }
  }
	
  if ((preemptive) && (type == TYPE_DEFAULT)) {
    cout << endl << "> ERROR: Type '" << type << "' cannot be preemptive by definition. Please retry using appropriate arguments!" << endl;
    return false;
  }

  return true;
}

  // fileParsing function
void fileParser (string currentLine, string& pid, string& arrTime, string& burTime, string& priority, int& index) {
  for (int i=2; i < currentLine.length(); ++i) {
    if (currentLine[i] != '\t') {
      pid = pid + currentLine[i];
    }

    else {
      index = i;
      break;
    }
  }
	
  for (int i=index; i < currentLine.length(); ++i) {
      if (currentLine[i] == '\t') {
      }

      else {
	index = i;
	break;
      }
  }

  for (int i=index; i < currentLine.length(); ++i) {
    if (currentLine[i] != '\t') {
      arrTime = arrTime + currentLine[i];
    }

    else {
      index = i;
      break;
    }
  }

  for (int i=index; i < currentLine.length(); ++i) {
      if (currentLine[i] == '\t') {
      }

      else {
	index = i;
	break;
      }
  }

  for (int i=index; i < currentLine.length(); ++i) {
    if (currentLine[i] != '\t') {
      burTime = burTime + currentLine[i];
    }

    else {
      index = i;
      break;
    }
  }

  for (int i=index; i < currentLine.length(); ++i) {
      if (currentLine[i] == '\t') {
      }

      else {
	index = i;
	break;
      }
  }

  for (int i=index; i < currentLine.length(); ++i) {
    if (currentLine[i] != '\t') {
      priority = priority + currentLine[i];
    }

    else {
      break;
    }
  }
}
