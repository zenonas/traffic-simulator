/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: Position.h
Description: This file includes the definition for the Position class

Copyright (c) King's College London
*/
#ifndef POSITION_H
#define POSITION_H

using namespace std;

class Position{

public:
	Position();
	~Position();
	int roadNodeID;
	int p;
	int lane;

};

#endif