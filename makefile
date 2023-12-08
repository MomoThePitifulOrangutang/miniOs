# FILE: makefile [for miniOS]
# J Hall, K Goebel, M Baird, Transy U
# CS 3074, Fall 2023
#
#	Build's an executable miniOS file by ensuring .o and output files are recompiled if source code is changed.
#
# target: miniOS's executable file [miniOS]
miniOS: miniOS.o PCBList.o PCBQueue.o  utilities.o fcfs.o sjf.o priority.o rr.o Frame.o Page.o fifo.o lru.o mfu.o random.o
	g++ miniOS.o PCBList.o PCBQueue.o utilities.o fcfs.o sjf.o priority.o rr.o Frame.o Page.o fifo.o lru.o mfu.o random.o -o miniOS

# target: miniOS's object file [miniOS.o]
miniOS.o: miniOS.cpp miniOS.h symConsts.h PCBList.h PCBQueue.h utilities.h fcfs.h sjf.h priority.h rr.h Frame.h Page.h fifo.h lru.h mfu.h random.h
	g++ -c miniOS.cpp 
	
# target: PCBQueue's object file [PCBQueue.o]
PCBQueue.o: PCBQueue.cpp PCBQueue.h PCBList.h symConsts.h
	g++ -c PCBQueue.cpp
	
# target PCBList's object file [PCBList.o]
PCBList.o: PCBList.cpp PCBList.h
	g++ -c PCBList.cpp
