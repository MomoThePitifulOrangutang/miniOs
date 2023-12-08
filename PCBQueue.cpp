//  FILE: PCBQueue.cpp
//  J Hall, K Goebel, M Baird, Transy U
//  CS 3074, Fall 2023
//
//      Implementation for PCBQueue Class
//
#include "PCBQueue.h"
#include <iostream>
using namespace std;

PCBQueue::PCBQueue (void) {
    qCount = 0;
}

PCBQueue::~PCBQueue (void) {
}

void PCBQueue::push (const char* schedulerType, const Pid newPid, const Arrival newArrTime, const Burst newBurTime, const Priority newPriority, const Addresses newAddresses) {
    Pid nextPid;
    Arrival nextArrTime;
    Burst nextBurTime;
    Priority nextPriority;
    Addresses nextAddresses;
    pcbList.moveToFront();
    for (int i = 0; i < (qCount + 1); ++i) {
        if (!pcbList.get(nextPid, nextArrTime, nextBurTime, nextPriority, nextAddresses)){
          pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
          ++qCount;
          return;
        }
        
        else if (newArrTime < nextArrTime) {
          pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
          ++qCount;
          return;
        }
        
        else if ((newArrTime == nextArrTime) && ((!strcmp(schedulerType, SCHEDULER_TYPE_DEFAULT)) || (!strcmp(schedulerType, RR)))) {
          if (newPid < nextPid) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
        }
        
        else if ((newArrTime == nextArrTime) && (!strcmp(schedulerType, SJF))) {
          if (newBurTime < nextBurTime) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
          
          else if ((newBurTime == nextBurTime) && (newPid < nextPid)) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
        }
        
        else if ((newArrTime == nextArrTime) && (!strcmp(schedulerType, PRIORITY))) {
          if (newPriority > nextPriority) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
          
          else if ((newPriority == nextPriority) && (newPid < nextPid)) {
            pcbList.insert(newPid, newArrTime, newBurTime, newPriority, newAddresses);
            ++qCount;
            return;
          }
        }
        
        pcbList.move();
        
    }
}

bool PCBQueue::pop (Pid& foundPid, Arrival& foundArrTime, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses){
    pcbList.moveToFront();
    if (!pcbList.get (foundPid, foundArrTime, foundBurTime, foundPriority, foundAddresses)) {
        return false;
    }

    pcbList.remove();
    --qCount;
    return true;

}

int PCBQueue::queueCount (void) {
    return qCount;
}
