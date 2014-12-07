OBJS = main.o SSFunctions.o Initialize.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

stellarStructure : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o stellarStructure
	mkdir -p data

SSFuntions.o : SSFunctions.h SSFunctions.cpp
	$(CC) $(CFLAGS) SSFunctions.cpp

main.o : main.cpp Initialize.h SSFunctions.h
	$(CC) $(CFLAGS) main.cpp

Initialize.o : Initialize.h Initialize.cpp
	$(CC) $(CFLAGS) Initialize.cpp
