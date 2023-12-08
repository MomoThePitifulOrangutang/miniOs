// FILE: PCBQueue.h
// J Hall, K Goebel, M Baird, Transy U
// CS 2444, Fall 2022
//
//     Interface for PCBQueue Class
//
#ifndef    PCBQUEUE_H
#define    PCBQUEUE_H

#include "PCBList.h"
#include "symConsts.h"
using namespace std;

class PCBQueue {

public:
  // constructor takes in nothing. This fn initializes the qCount variable to 0
    PCBQueue (void);

  // destructor
    ~PCBQueue (void);

  // accessors
    // queueCount fn takes in nothing. This function only returns the qCount variable, which holds the number of PCB's in the queue
    int queueCount (void);

  // mutators
    // push fn takes in a scheduler type, a pid, an arrival time, a burst time, a priority and a queue of addresses for a process. This fn calls get on the PCB list. If get returns false, this means the queue is empty, so this fn just calls insert on the PCB List, and increments the qCount, placing the new PCB at the front of the queue. If get returns true, this means at least one PCB is already in the queue, so the program then compares the arrival time of the process being pushed into the queue with the arrival time of the next process in the queue. If the new arrival time is less than the next arrival time, this fn calls insert on the PCB List, placing the new PCB before the next PCB. If the arrival times are equal however, depending on the scheduling type, this fn will sort by the appropriate variable (pid for FCFS or RR, burst time for SJF, and priority for Priority) and call insert on the PCB List, placing the new PCB where it should go to have the queue sorted properly for the specified scheduler type. Returns nothing
    void push (const char* schedulerType, const Pid newPid, const Arrival newArrTime, const Burst newBurTime, const Priority newPriority, const Addresses newAddresses);

    // pop fn takes in a pid placeholder, an arrival time placeholder, a burst time placeholder, a priority placeholder, and an address queue placeholder. This function moves the cursor to front of the linked list container, then calls get on the PCB List, calls remove on the PCB List, and decrements qCount. Returns false if get fails, returns true otherwise
    bool pop (Pid& foundPid, Arrival& foundArrTime, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses);

private:
    PCBList pcbList;
    int qCount;
};

#endif
