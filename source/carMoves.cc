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

//instead of the arate we have to pass the target speed
//if in front there are traffic lights then the target speed will be 0
//if in front there is a car with speed x then the target speed will be ...
int accelerate(vehicle *v,vehicle *s, float aRate, void *arguments) {
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int ticktime = thread_args->sleep_time;
    vector<roadNode> roads = thread_args->mymap.getunfRoads();

	struct Position newPos;
	newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
	newPos.lane = v->getCurrentPosition().lane;
	newPos.p = v->getCurrentPosition().p;

	vector<int> vPath = v->getPath();

	//find the next roadnode to check if there us a turn
	int nextRoadID=-1;
	for (int i=0; i<vPath.size(); i++)
		if (vPath[i] == newPos.roadNodeID)
			nextRoadID=vPath[i+1];

	float cSpeed = v->getCurrentSpeed();
	float newSpeed=0;
	int distanceToTravel=0;

	//get the vehicle's acceleration if the vehicle can accelerate
	//else the vehicle's acceleration will pass to this function
	if (aRate>0)
		aRate = v->getAcceleration();
	//calculate new speed given acceleration rate
	newSpeed = cSpeed + aRate*ticktime;
	//calculate distance to driver with current speed and a given acceleration rate
	distanceToTravel = cSpeed*ticktime + (aRate*ticktime*ticktime)/2;

	int roadMaxSpeed=-1;
	//get roadNode maximum speed
	if (newPos.roadNodeID>0)
		roadMaxSpeed = roads[v->getCurrentPosition().roadNodeID-1].getMaxSpeed();

	// this means that may crash with the following car
	if (aRate==-1){
		//cout << "reduce speed";
		float remain = (cSpeed-s->getCurrentSpeed())/v->getAcceleration();
	//	cout << "remain1:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(-aRate))/2 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(s->getCurrentSpeed());
	}
	else if (cSpeed==v->getMaxSpeed() && cSpeed<=roadMaxSpeed){
		//check if turn in order to decelerate
		float remain = 0;
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				remain = (cSpeed-11)/aRate;
			//	cout << "remain2:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(-aRate))/2 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(11); 
			}
		else
			distanceToTravel = cSpeed*ticktime;	
		//cout << "eftasa to max speed tu car. actual distance: " << distanceToTravel<<endl;
		}
	else if (cSpeed==roadMaxSpeed && cSpeed<=v->getMaxSpeed() ){
		float remain = 0.0;
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				remain = ((float) cSpeed-11.0)/(float)aRate;
			//	cout << "aRate: " <<aRate;
		//		cout << "remain3:" <<endl<<remain<<endl;
		distanceToTravel =  cSpeed*remain + (remain*remain*(0-aRate))/2.0 + (ticktime-remain)*11.0;
		//cout << "distance: " <<distanceToTravel<<" cspeed: " <<cSpeed<<" tick: "<<ticktime;
		v->setCurrentSpeed(11); 
			}
			else
		distanceToTravel = cSpeed*ticktime;
		//cout << "eftasa to max speed tu road. actual distance: " << distanceToTravel<<endl;
	}
	else if (newSpeed>v->getMaxSpeed() && newSpeed<=roadMaxSpeed)
	{
		float remain = 0;
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				remain = (cSpeed-11)/aRate;
	//			cout << "remain4:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(0-aRate))/2.0 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(11); 
			}
			else{
			float temp = newSpeed-v->getMaxSpeed();
			float remain=temp/aRate;
	//		cout << "remain5:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(-aRate))/2 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(v->getMaxSpeed()); 
			//cout << "piga panw apo to max speed tu car. actual distance: " << distanceToTravel<<endl;
		}
	}
	else if (newSpeed>roadMaxSpeed && roadMaxSpeed>0 && newSpeed<=v->getMaxSpeed()){
			float remain = 0;
			//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				remain = (cSpeed-11)/aRate;
		//		cout << "remain6:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(-aRate))/2 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(11); 
			}
			else{float temp = newSpeed-roadMaxSpeed;
			float remain=temp/aRate;
			distanceToTravel = distanceToTravel - (remain*aRate +(aRate*remain)/2);
			v->setCurrentSpeed(roadMaxSpeed); 
			//cout << "piga panw apo to max speed tu road. actual distance: " << distanceToTravel<<endl;
		}
	}
	else if (newSpeed>roadMaxSpeed && roadMaxSpeed>0 && newSpeed>=v->getMaxSpeed()){
			float remain = 0;
			//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				remain = (cSpeed-11)/aRate;
			//	cout << "remain7:" <<remain;
		distanceToTravel =  cSpeed*remain + (remain*remain*(-aRate))/2 + (ticktime-remain)*v->getCurrentSpeed();
		v->setCurrentSpeed(11); 
			}
			else {float temp = newSpeed - max(roadMaxSpeed,v->getMaxSpeed());
			float remain;
			if (aRate!=0){
		//		cout << "what";
				remain=temp/aRate;
			distanceToTravel = distanceToTravel - (remain*aRate +(aRate*remain*remain)/2);
			}
			v->setCurrentSpeed(min(roadMaxSpeed,v->getMaxSpeed())); 
			if (newSpeed < v->getCurrentSpeed()) v->setCurrentSpeed(newSpeed);
			//cout << "pio polli kai apo ta dio. actual distance: " << distanceToTravel<<endl;
		}
	}

		//if is not in the map what???
	else if (roadMaxSpeed<0)
		{
			distanceToTravel=0;
			//cout << "road0. distance: " << distanceToTravel<<endl;
		}
	else v->setCurrentSpeed(newSpeed);
	
	
	if (newPos.roadNodeID == -1) {
		newPos.roadNodeID = vPath[0];
		newPos.p = 0;
		newPos.lane = 0;
	}
	
	int z=0;
	bool roadChange = false;
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

/*
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
}*/

int checkVehicle(vehicle *veh1, vehicle *veh2){
     vector<int> vehicle1Path = veh1->getPath();
     vector<int> vehicle2Path = veh2->getPath();
     for (int p=0; p<vehicle1Path.size(); p++)
            for (int q=0; q<vehicle2Path.size(); q++)                           
               if (vehicle1Path[p]==vehicle2Path[q])	
               		return 1;
    return 0;
   }

 