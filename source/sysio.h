/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: sysio.h
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#ifndef SYSIO_H
#define SYSIO_H

#include <curses.h>
#include "th_structs.h"

void updateVehicles(WINDOW *vehiclestats, void *arguments);
void updateRoadNodes(WINDOW *roadnodestats, void *arguments);
void updateTrafficLights(WINDOW *trafficlstats, void *arguments);
int maxVehicleChange(WINDOW *cmdbox,void *arguments);
int setVehicleRatio(WINDOW *cmdbox,void *arguments);
int setDriverRatio(WINDOW *cmdbox,void *arguments);
int changeSimTime(WINDOW *cmdbox,void *arguments);
void *inout(void *arguments);


#endif