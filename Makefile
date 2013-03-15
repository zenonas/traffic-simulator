#/* Traffic Simulation System
#
#Group Project 7CCSMGPR - Team B
#Created: 22/2/2013
#Updated: 22/2/2013
#File: Makefile
#Description: This file handles the compilation of the project
#Copyright (c) King's College London
#
#------------------------------------------------------------------------------

CC=g++
CFLAGS = -g -Ilib
LDFLAG = -lpthread -lncurses -lpanel

#------------------------------------------------------------------------------

all: trafficsim

trafficsim: bin/main.o bin/vehicle.o bin/map.o bin/graphNode.o bin/roadNode.o bin/statistics.o bin/sysio.o bin/ResetTrafficLights.o bin/trafficLight.o
	@echo "Linking everything together to produce the Traffic Simulation System"
	$(CC) -o $@ $^ $(LDFLAG)

bin/main.o: source/main.cc
	@echo "Compiling the Main file"
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/vehicle.o: source/vehicle.cc
	@echo "Compiling the rest of the sources"
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/map.o: source/map.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/sysio.o: source/sysio.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/ResetTrafficLights.o: source/ResetTrafficLights.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/trafficLight.o: source/trafficLight.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/graphNode.o: source/graphNode.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/roadNode.o: source/roadNode.cc
	$(CC) -c $(CFLAGS) -o $@ $< 

bin/statistics.o: source/statistics.cc
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	clear
	@echo "Make is cleaning object files and the trafficsim binary"
	rm -f bin/*
	rm -r trafficsim
