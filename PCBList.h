// FILE: PCBList.h
// J Hall, K Goebel, M Baird, Transy U
// CS 3234, Fall 2023
//
//
//	Interface for the PCB Linked List Class
//
// Class Invariants:
//   1. Head always points to the empty head node
//   2. Cursor always points to some node in the list
//   3. Tail always points to the last node in the list
//   4. Last node in list always has a 0 next pointer
//

#ifndef    PCBLIST_H
#define    PCBLIST_H

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

  // constructor takes in nothing. This fn initializes head node and makes all state variables follow class invariants
    PCBList (void);
         // postcondition: empty list set up, all class invariants hold
    
  // destructor takes in nothing. This fn moves the cursor to the front of queue, then calls remove until unable to, deallocating all memory used up by the queue, then deletes the head
    ~PCBList (void);
         // postcondition: all dynamically allocated storage is deleted

  // accessor
    // get fn takes in a pid placeholder, an arrival time placeholder, a burst time placeholder, a priority placeholder, and an address queue placeholder. This fn sets each placeholder to the appropriate variable stored in the next PCB of the linked list. Returns true if cursor -> next is not 0, returns false otherwise. This ensures that garbage will not fill the placeholders if the cursor is the last node in the linked list. 
bool get (Pid& foundPid, Arrival& foundArrTime, Burst& foundBurTime, Priority& foundPriority, Addresses& foundAddresses) const;
         // precondition: cursor precedes item to retrieve

  // mutators
    // insert fn takes in a pid integer, an arrival time integer, a burst time integer, a priority integer, and a queue of address strings. This fn declares a new PCB, and sets this PCB's data values to the appropriate parameters, then adds the PCB in after the cursor. Returns nothing
void insert (const Pid& newPid, const Arrival& newArrTime, const Burst& newBurTime, const Priority& newPriority, const Addresses& newAddresses);
         // precondition: cursor points at node that will precede new node

    // remove fn takes in nothing. This fn declares a PCB named victim, and sets this PCB equal to cursor -> next. Cursor -> next is then set to the node after the victim node, and the victim node is deleted. Returns true if victim node was deleted, returns false if cursor == tail.
bool remove (void);
         // precondition: cursor points at node that precedes the victim

    // move fn takes in nothing. This fn sets cursor to cursor -> next. Returns true if cursor was set to cursor -> next, returns false if cursor == tail.
bool move (void);
         // postcondition: cursor points one node further down the linked list

    // moveToFront fn takes in nothing. This fn sets the cursor to the head node. Returns nothing
void moveToFront (void);

private:
    struct PCB {
      Pid pid; 
      Arrival arrTime;
      Burst burTime;
      Priority priority;
      Addresses addressQueue;
      PCB    *next;
    };

// private variables
    PCB *head, *tail, *cursor;

};
#endif
