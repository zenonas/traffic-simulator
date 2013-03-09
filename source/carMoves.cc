/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 5/3/2013
Updated: 8/3/2013
File: carMoves.cc
Description: This file contains functions used for the movement of vehicles
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

int accelerate(vehicle *v, int aRate, void *arguments) {
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int ticktime = thread_args->sleep_time;
    vector<roadNode> roads = thread_args->mymap.getunfRoads();

	int maxSpeed;
	if (v->getType() == 0) {
		maxSpeed = 120;
	} else if (v->getType() == 1) {
		maxSpeed = 80;
	} else if (v->getType() == 2) {
		maxSpeed = 65;
	}
	int cSpeed = v->getCurrentSpeed();
	int newSpeed = cSpeed + (aRate * ticktime);
	int roadMaxSpeed = roads[v->getCurrentPosition().roadNodeID].getMaxSpeed();
	if (newSpeed <= maxSpeed-10 && newSpeed <= roadMaxSpeed) {
		v->setCurrentSpeed(newSpeed); 
	} else {
		v->setCurrentSpeed(min(maxSpeed,roadMaxSpeed));
	}
	if (newSpeed<0)
		v->setCurrentSpeed(0);

	struct Position newPos;
	newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
	newPos.lane = v->getCurrentPosition().lane;
	newPos.p = v->getCurrentPosition().p;

	vector<int> vPath = v->getPath();
	if (newPos.roadNodeID == -1) {
		newPos.roadNodeID = vPath[0];
		newPos.p = 0;
		newPos.lane = 0;
	}
	int distanceToTravel = (cSpeed * ticktime) + ((aRate*pow(ticktime,2)/2));
	int z=0;
	bool roadChange = false;
	//cout << "distanceToTravel: " << distanceToTravel << endl;
	//cout << "LENGTH OF CURRENT ROAD NODE: " << newPos.roadNodeID << " is " << thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() << endl;
	//cout << "MY CARS CURRENT SPEED IS: " << v->getCurrentSpeed() << endl;
	while(distanceToTravel >= (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p)) {
		if (newPos.roadNodeID == vPath.back() && vPath.size() > 1) return 0;	
		int tempDistance = thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p;
		distanceToTravel -= tempDistance;
		for (z=0; z<vPath.size(); z++) {
			if (vPath[z] == newPos.roadNodeID) {
				if (z+1<vPath.size()) z++;
				else return 0; 
			newPos.roadNodeID = vPath[z];
			newPos.p = 0;
			break;
			}		
		}
		roadChange=true;
	} 
	if (roadChange) newPos.p = distanceToTravel;
		else newPos.p += distanceToTravel;
	v->setCurrentPosition(newPos);
	return 1;
}

int moveVehicle(vehicle *v, void *arguments) {
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int ticktime = thread_args->sleep_time;

	int cSpeed = v->getCurrentSpeed();
	
	if (cSpeed == 0) return 0; // cannot move a vehicle with 0 speed need to accelerate instead

	struct Position newPos;
	newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
	newPos.lane = v->getCurrentPosition().lane;
	newPos.p = v->getCurrentPosition().p;

	vector<int> vPath = v->getPath();
	if (newPos.roadNodeID == -1) {
		newPos.roadNodeID = vPath[0];
		newPos.p = 0;
		newPos.lane = 0;
	}
	int distanceToTravel = cSpeed * ticktime;
	int z=0;
	bool roadChange = false;
	cout << "distanceToTravel: " << distanceToTravel << endl;
	cout << "LENGTH OF CURRENT ROAD NODE: " << newPos.roadNodeID << " is " << thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() << endl;
	cout << "MY CARS CURRENT SPEED IS: " << v->getCurrentSpeed() << endl;
	while(distanceToTravel >= (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p)) {
		if (newPos.roadNodeID == vPath.back() && vPath.size() > 1) return 0;
		int tempDistance = thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p;
		distanceToTravel -= tempDistance;
		for (z=0; z<vPath.size(); z++) {
			if (vPath[z] == newPos.roadNodeID) {
				if (z+1<vPath.size()) z++;
				else return 0; 
			newPos.roadNodeID = vPath[z];
			newPos.p = 0;
			break;
			}		
		}
		roadChange=true;
	} 
	if (roadChange) newPos.p = distanceToTravel;
		else newPos.p += distanceToTravel;
	v->setCurrentPosition(newPos);
	return 1;
}

int checkVehicle(vehicle *veh1, vehicle *veh2){
     vector<int> vehicle1Path = veh1->getPath();
     vector<int> vehicle2Path = veh2->getPath();
     for (int p=veh1->getCurrentPosition().roadNodeID; p<vehicle1Path.size(); p++)
            for (int q=veh2->getCurrentPosition().roadNodeID; q<vehicle2Path.size(); q++)                           
               if (vehicle1Path[p]==vehicle2Path[q])
               	return 1;
               else return 0;
                

   }

