//  FILE: PCBQueue.cpp
//  Group 5, Transy U
//  CS 3074, Fall 2023
//
//      Implementation for PCBQueue Class
//
#include "PCBQueue.h"
#include <iostream>
using namespace std;

//// public member fns ////

  // constructor
PCBQueue::PCBQueue (void) {
    qCount = 0;
}

  // destructor
PCBQueue::~PCBQueue (void) {
}


  // mutators

    // put fn
void PCBQueue::push (const char* schedulerType, const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses) {
    Pid nextPid;
    Arrival nextArrTime;
    Burst nextBurTime;
    Priority nextPriority;
    Addresses nextAddresses;
    
      // cursor moved to head node
    pcbList.moveToFront();

      // compare the new priority value with the values of the other priorities of the PCBs in the queue until its spot is found
    for (int i = 0; i < (qCount + 1); ++i) {
        if (!pcbList.get(nextPid, nextBurTime, nextPriority, nextAddresses)){
          cout << endl << "EMPTYQUEUE: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
          pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
          ++qCount;
          return;
        }
        
        else if (newArrTime < nextArrTime) {
          pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
          cout << endl << "ARR: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
          ++qCount;
          return;
        }
        
        else if ((newArrTime == nextArrTime) && ((!strcmp(schedulerType, SCHEDULER_TYPE_DEFAULT)) || (!strcmp(schedulerType, RR)))) {
          if (newPid < nextPid) {
            cout << endl << "FCFS/RR: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
        }
        
        else if ((newArrTime == nextArrTime) && (!strcmp(schedulerType, SJF))) {
          if (newBurTime < nextBurTime) {
            cout << endl << "SJF: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
          
          else if ((newBurTime == nextBurTime) && (newPid < nextPid)) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            cout << endl << "SJF: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
            ++qCount;
            return;
          }
        }
        
        else if ((newArrTime == nextArrTime) && (!strcmp(schedulerType, PRIORITY))) {
          if (newPriority > nextPriority) {
            cout << endl << "PRI: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
          
          else if ((newPriority == nextPriority) && (newPid < nextPid)) {
            cout << endl << "PRI: P_" << newPid << " currently being stuck before P_" << nextPid << endl;
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
        }
        
        pcbList.move();
        
    }
}

    // get fn
bool PCBQueue::pop (Pid& foundPid, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses){

      // cursor moved to head node
    pcbList.moveToFront();

      // calls get from PCBList and returns false if get fails
    if (!pcbList.get (foundPid, foundBurTime, foundPriority, foundAddresses)) {
        return false;
    }

      // removes first real node in queue
    pcbList.remove();
    --qCount;
    return true;

}

    // queueCount
int PCBQueue::queueCount (void) {
    return qCount;
}

      // debug fn
void PCBQueue::printDEBUG (void) const{
    pcbList.printDEBUG();
}
