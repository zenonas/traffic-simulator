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
#include "vehicle.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

vector<vehicle *> carsInRoadNode(vector<vehicle *> vIengine, roadNode road) {
	vector<vehicle *> carList;
	for (int i=0; i<vIengine.size(); i++) {
		int id = vIengine[i]->getCurrentPosition().roadNodeID;
		if (id == road.getId())
			carList.push_back(vIengine[i]);
	}
	return carList;
}

bool carFits(vehicle *v, vector<vehicle *> vIengine,vector<roadNode> allRoads,void *arguments) {

	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	// need to find the road node
	int entryId = v->getCurrentPosition().roadNodeID;
	int i;
	for (i=0; i<allRoads.size(); i++) {
		if (entryId == allRoads[i].getId()) {
			//found road
			break;
		}
	}

	// i have a road and a vehicle
	vector<vehicle *> vehiclesInMyRoadNode = carsInRoadNode(vIengine,allRoads[i]);
	if (vehiclesInMyRoadNode.size() == 0) {
		return true;
	} else {
		int closestP = vehiclesInMyRoadNode[0]->getCurrentPosition().p;
		for (int k=0; k<vehiclesInMyRoadNode.size(); k++) {
			if (closestP > vehiclesInMyRoadNode[k]->getCurrentPosition().p && v->getCurrentPosition().lane == vehiclesInMyRoadNode[k]->getCurrentPosition().lane) {
				vehicle *closestV = vehiclesInMyRoadNode[k];
				closestP = vehiclesInMyRoadNode[k]->getCurrentPosition().p;
			}
		}
		int spaceAvailable = allRoads[1].getLength() - closestP;
		int safeDist = 1;

		if (v->getType() == 0) {
			spaceAvailable = spaceAvailable - safeDist - 10;		
		} else if (v->getType() == 1) {
			spaceAvailable = spaceAvailable - safeDist - 15;		
		} else if (v->getType() == 2) {
			spaceAvailable = spaceAvailable - safeDist - 20;		
		}

		if (spaceAvailable >= 0) {
			return true;
		}
		return false;
	}
}

void accelerate(vehicle *v, int dSpeed, void *arguments) {
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int ticktime = thread_args->sleep_time;
	int maxAcs;
	if (v->getType() == 0) {
		maxAcs = 15;
	} else if (v->getType() == 1) {
		maxAcs = 10;
	} else if (v->getType() == 2) {
		maxAcs = 5;
	}
	int maxSpeed;
	if (v->getType() == 0) {
		maxSpeed = 120;
	} else if (v->getType() == 1) {
		maxSpeed = 80;
	} else if (v->getType() == 2) {
		maxSpeed = 65;
	}

	int cAccs = v->getAcceleration();
	int cSpeed = v->getCurrentSpeed();
	int newSpeed;
	//if current speed && acceleration is 0 start accelerate to desired speed
	if (cSpeed == 0 && cAccs == 0) {
		newSpeed = maxAccs * ticktime;
		if (newSpeed < dSpeed) {
			cAccs = maxAccs;
		}	
	} else if (cSpeed < dSpeed && cAccs == 0) {
		newSpeed = cSpeed + (maxAccs * ticktime);
		if (newSpeed < dSpeed) cAccs = maxAccs;
	}
	//if current speed is not 0 start accelerate to desired speed

	//if current speed

	

	
	if (newSpeed <= maxSpeed) {
		v->setCurrentSpeed(newSpeed); 
	} else {
		v->setCurrentSpeed(maxSpeed);
	}
	struct Position newPos;
	newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
	newPos.lane = v->getCurrentPosition().lane;
	newPos.p = v->getCurrentPosition().p;

	vector<int> vPath = v->getPath();
	if (newPos.roadNodeID == -1) {
		cout << "my vPath[0] IS: " << vPath[0] << endl;
		newPos.roadNodeID = vPath[0];
		newPos.p = 0;
		newPos.lane = 0;
	}
	(+((1/2)*cAccs*pow(ticktime,2));
	int distanceToTravel = newPos.p + ((1/2)*cAccs*pow(ticktime,2));
	cout << "distanceToTravel: " << distanceToTravel << endl;
	int z;
	do{
		if (distanceToTravel > thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()) {
			int tempDistance = thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - v->getCurrentPosition().p;
			distanceToTravel -= tempDistance;
		}
		for (z=0; z<vPath.size(); z++) 
			if (vPath[z] == newPos.roadNodeID)
				break;		
		z++;
		if (z > vPath.size()) {
			break; // efiges
		} else {
		newPos.roadNodeID = vPath[z];
		}
	} while(distanceToTravel > thread_args->mymap.getroadNode(vPath[z])->getLength());
	newPos.p = distanceToTravel;
	cout << " i am here: " << newPos.p << " and " << newPos.roadNodeID<< endl;
	v->setCurrentPosition(newPos);
}

