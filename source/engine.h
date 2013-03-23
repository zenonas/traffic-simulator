/* Traffic Simulation System
Group Project 7CCSMGPR - Team B
Created: 23/3/2013
Updated: 23/3/2013
File: engine.h
Description: This is the header file for the simulation engine.

Copyright (c) King's College London

*/

#ifndef _ENGINE_H
#define _ENGINE_H

#include "th_structs.h"
#include "map.h"
#include "carMoves.h"
#include "roadNode.h"
#include "graphNode.h"
#include "statistics.h"
#include <vector>
#include <iostream>

using namespace std;

void *engine(void *arguments);

#endif