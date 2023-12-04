# FILE: makefile [for miniOS]
# J Hall, K Goebel, M Baird, Transy U
# CS 3074, Fall 2023
#
#	Build's an executable miniOS file by ensuring .o and output files are recompiled if source code is changed.
#
# target: miniOS's executable file [miniOS]
miniOS: miniOS.o utilities.o fcfs.o sjf.o priority.o rr.o
	g++ miniOS.o utilities.o fcfs.o sjf.o priority.o rr.o  -o miniOS

# target: miniOS's object file [miniOS.o]
miniOS.o: miniOS.cpp miniOS.h symConsts.h utilities.h fcfs.h sjf.h priority.h rr.h
	g++ -c miniOS.cpp 

			
# target: pageTable's object file [pageTable.o]
#pageTable.o: pageTable.cpp pageTable.h
#	g++ -c pageTable.cpp 
	
# target: pageReplacementSimulator's object file [pageReplacementSimulator.o]
#pageReplacementSimulator.o: pageReplacementSimulator.cpp pageReplacementSimulator.h
#	g++ -c pageReplacementSimulator.cpp 
