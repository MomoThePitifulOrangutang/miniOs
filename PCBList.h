// FILE: PCBList.h
// Group 5, Transy U
// CS 3234, Fall 2023
//
//
//	Interface for the PCB Linked List Class
//
//

#ifndef    PCBLIST_H
#define    PCBLIST_H

// set up the data type to be held in the list
#include <string>
#include <queue>
#include <cstring>
using namespace std;
typedef int Pid;
typedef int Arrival;
typedef int Burst;
typedef int Priority;
typedef queue<string> Addresses;

class PCBList {
public:
// public member functions

  // constructor
    PCBList (void);
         // postcondition: empty list set up, all class invariants hold
    
  //destructor
    ~PCBList (void);
         // postcondition: all dynamically allocated storage is deleted

  // mutators
void insert (const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses);
         // precondition: cursor pts at node that will precede new node
         // postcondition: node with newItem follows cursor node

bool remove (void);
         // precondition: cursor pts at node that precedes the victim
         // postcondition: victim removed and deleted

bool move (void);
         // postcondition: cursor pts one node further down the list

void moveToFront (void);
         // postcondition: cursor pts at first node in the list


  // accessors
bool get (Pid& foundPid, Arrival& foundArrTime, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses) const;
         // precondition: cursor precedes item to retrieve
         // postcondition: item holds data value from node following cursor node

void printDEBUG (void) const;
         // postcondition: data values contained in list are printed to screen


private:
// private data type
  // PCB
    struct PCB {
      Pid pid; 
      Arrival arrTime;
      Burst burTime;
      Priority priority;
      Addresses addressQueue;
      PCB    *next;
    };

// private  variables
    PCB *head, *tail, *cursor;

};
#endif
