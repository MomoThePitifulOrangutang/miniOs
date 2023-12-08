/*
FILE: fifo.h
BY: Zach Drury, David Schwab, Dylan Mordhorst
FOR: OS, Transy U, 2023
Purpose: Interface: Simulated page replacer method: FIFO
*/


#include <queue>
#include <iostream>
#include <string>
using namespace std;

// takes: memory address queue, frame 'table'(array), page 'table'(array), amount of frames and pages, and size of frames
// produces: the total number of page faults that occured from the FIFO paging method
int fifo (queue<string> addresses, Frame frames[], Page pages[], int framecount, int framesize, int pagecount);

// takes: memory address being examined, frame 'table', page 'table', amount of frames and pages, and size of frames, queue next table to be replaced, point to the number of faults
// produces: true if frame was found, false if not; updated frame table with new pages inserted or not depending on the memory address, as well as update fault count
bool fifo_find_frame (string currentAddress, Frame frames[], Page pages[], int framecount, int framesize, int pagecount, queue<int> &outQueue, int &faults);

// takes: an address, the amount of pages, size of frames, and the page table
// produces: the number page that the memory address belongs to
Page fifo_find_page (int address, int pagecount, int framesize, Page pages[]);