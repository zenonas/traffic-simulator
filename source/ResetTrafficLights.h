/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: sysio.h
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#ifndef RTRAFFICL_H
#define RTRAFFICL_H

#include "th_structs.h"

void ResetTrafficLights(void *arguments);
void ToggleLights(void *arguments);


#endif