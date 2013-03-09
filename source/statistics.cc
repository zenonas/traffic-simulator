/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 08/2/2013
Updated: 08/2/2013
File: statistics.cc
Description: This file includes the implementation for the statistics class.

Copyright (c) King's College London
*/

#include "statistics.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

statistics::statistics(){


}

statistics::~statistics(){

	
}

void statistics::CaptureStatistics(map& mymap, vector<vehicle *> vehiclesInEngine){
// Testing
	cout << "Testing:" << endl;
	mymap.printAllPaths();


}