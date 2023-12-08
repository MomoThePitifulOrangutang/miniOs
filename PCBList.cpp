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

PCBList::PCBList (void) {
	head = new PCB;
        head -> next = 0;
	tail = head;
	cursor = head;
}

PCBList::~PCBList (void) {
    moveToFront();
    while (remove()){
    }
    delete head;
    cursor = 0;
    head = 0;
    tail = 0;
}

bool PCBList::get (Pid& foundPid, Arrival& foundArrTime, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses) const {
    if (cursor -> next == 0) {
        return false;
    }
    
    foundPid = cursor -> next -> pid;
    foundArrTime = cursor -> next -> arrTime;
    foundBurTime = cursor -> next -> burTime;
    foundPriority = cursor -> next -> priority;
    foundAddresses = cursor -> next -> addressQueue;
    return true;
}

void PCBList::insert (const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses) {
    PCB *temp = new PCB;
    temp -> pid = newPid;
    temp -> arrTime = newArrTime;
    temp -> burTime = newBurTime;
    temp -> priority = newPriority;
    temp -> addressQueue = newAddresses;
    temp -> next = cursor -> next;
    cursor -> next = temp;
    
    // ensures class invariant #3 by setting tail to what will become the last node in the list if cursor points to the tail node
    if (tail == cursor) {
        tail = tail -> next;
    }
}

bool PCBList::remove (void){
    PCB *victim = cursor -> next;
        if (victim == 0) {
            return false;
        }

      // ensures class invariant #3 by setting tail to what will become the last node in the list if cursor -> next points to the tail node
        if (victim == tail) {
            tail = cursor;
        }

      // ensures no memory leaks by ensuring that cursor will have a next pointer and that the next node in the list will have at least 1 pointer to it
    cursor -> next = cursor -> next -> next;
    delete victim;
    return true;
}

bool PCBList::move (void){
    if (cursor -> next == 0) {
        return false;
    }

    cursor = cursor -> next;
    return true;
}

void PCBList::moveToFront (void){
    cursor = head;
}
