/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 5/3/2013
Updated: 5/3/2013
File: carFits.cc
Description: This file contains the implementation for the carFits function of the Engine
Copyright (c) King's College London

*/
#include "th_structs.h"
#include "map.h"
#include <vector>
#include <iostream>

using namespace std;

vector<vehicle *> carsInRoadNode(vector<vehicle *> vIengine, roadNode *road) {
	vector<vehicle *> carList;
	for (int i=0; i<vIengine.size(); i++) {
		int id;
		id = vIengine[i]->getCurrentPosition().roadNodeID;
		if (id == road->getId())
			carList.push_back(vIengine[i]);
	}
	return carList;
}

bool carFits(vehicle *v, void *arguments) {

	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;

	return true;
}

