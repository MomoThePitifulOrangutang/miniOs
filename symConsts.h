// FILE: symConsts.h
// J Hall, K Goebel, M Baird, Transy U
// CS 3704, Fall 2023
//
//
//	File that provides symbollic constants necessary for miniOS.cpp and pageReplacementSimulator.cpp files
//

#define SCHEDULER_TYPE "--schedulerType"
#define PREEMPTIVE "--preemptive"
#define QUANTA "--quanta"
#define SJF "SJF"
#define PRIORITY "Priority"
#define RR "RR"
#define SCHEDULER_TYPE_DEFAULT "FCFS"
#define QUANTA_DEFAULT 10
#define PREEMPTIVE_DEFAULT false
#define MAX_PCBS 250

#define PAGER_TYPE "--pagerType"
#define FRAMES "--frames"
#define PAGES "--pages"
#define FRAMESIZE "--framesize" 
#define LRU "LRU"
#define MFU "MFU"
#define RANDOM "Random"
#define PAGER_TYPE_DEFAULT "FIFO"
#define FRAMES_DEFAULT 3
#define PAGES_DEFAULT 8
#define FRAMESIZE_DEFAULT 512
#define MAX_FRAMES 65536

#define VERBOSE "--verbose"
#define VERBOSE_DEFAULT false
#define INPUT_FILE_DEFAULT "final.in"
