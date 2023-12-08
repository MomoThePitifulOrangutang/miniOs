// FILE: PCBList.cpp
// GROUP 5, Transy U
// CS 3074, Fall 2023
//
//
//	Implementation of the PCB Linked List class
//
//

#include "PCBList.h"
#include <iostream>
using namespace std;

// public member functions

  // constructor
    // initializes head node and makes all state variables follow class invariants
PCBList::PCBList (void) {
	head = new PCB;
        head -> next = 0;
	tail = head;
	cursor = head;
}

  // destructor
PCBList::~PCBList (void) {
    moveToFront();
    while (remove()){
    }
    delete head;
    cursor = 0;
    head = 0;
    tail = 0;
}

bool PCBList::get (Pid& foundPid, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses) const {
    if (cursor -> next == 0) {
        return false;
    }
    
    foundPid = cursor -> next -> pid;
    foundBurTime = cursor -> next -> burTime;
    foundPriority = cursor -> next -> priority;
    foundAddresses = cursor -> next -> addressQueue;
    return true;
}

void PCBList::printDEBUG (void) const{
    for (PCB *temp = head -> next; temp; temp = temp -> next) {
      cout << temp -> pid << ' ' << temp -> arrTime << ' ' << temp -> burTime << ' ' << temp -> priority << endl;
    }
}


void PCBList::insert (const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses) {

      // makes new node and inputs reference data in as new node's data
    PCB *temp = new PCB;
    temp -> pid = newPid;
    temp -> arrTime = newArrTime;
    temp -> burTime = newBurTime;
    temp -> priority = newPriority;
    temp -> addressQueue = newAddresses;

      // sticks the new node in between the cursor node and the following node
    temp -> next = cursor -> next;
    cursor -> next = temp;

      // ensures class invariant #3 by making the new node the tail
    if (tail == cursor) {
        tail = tail -> next;
    }
}

    // remove fn
bool PCBList::remove (void){

      // makes node after cursor the target of removal
    PCB *victim = cursor -> next;

      // fails if cursor is also tail
        if (victim == 0) {
            return false;
        }

      // ensures class invariant #3 by setting tail to what will become the last node in list if cursor next pointer is tail
        if (victim == tail) {
            tail = cursor;
        }

      // ensures no memory leaks so cursor will have a next pointer and next node in list will have at least 1 pointer to it
    cursor -> next = cursor -> next -> next;

      // removes the node after cursor
    delete victim;
    return true;
}

    // move fn
bool PCBList::move (void){

      // fails if cursor is tail
    if (cursor -> next == 0) {
        return false;
    }

      // moves cursor over to the next node in the list
    cursor = cursor -> next;
    return true;
}

    // moveToFront fn
      // sets cursor to first node in the list (not first REAL node)
void PCBList::moveToFront (void){
    cursor = head;
}
