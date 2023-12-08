// FILE: PCBQueue.h
// J Hall, Transy U
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
// public member functions //

  // constructor
    PCBQueue (void);

  // destructor
    ~PCBQueue (void);

  // mutators
    // put
    void push (const char* schedulerType, const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses);
      //postcondition: reference parameter added to queue in descending order

    // get
    bool pop (Pid& foundPid, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses);
      //postcondition: front-most member of queue copied as reference parameter and removed from queue

  // accessors
    // queueCount
    int queueCount (void);
    
    // debug
    void printDEBUG (void) const;
    //postcondition: starting at front of queue, all members printed until unable

private:
    PCBList pcbList;
    int qCount;
};

#endif
