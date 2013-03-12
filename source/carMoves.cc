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

	

	struct Position newPos;
	newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
	newPos.lane = v->getCurrentPosition().lane;
	newPos.p = v->getCurrentPosition().p;

	vector<int> vPath = v->getPath();
	int nextRoadID=-1;
	for (int i=0; i<vPath.size(); i++)
		if (vPath[i] == newPos.roadNodeID)
			nextRoadID=vPath[i+1];

	int cSpeed = v->getCurrentSpeed();
	int roadMaxSpeed=-1;
	if (newPos.roadNodeID>0)
		roadMaxSpeed = roads[v->getCurrentPosition().roadNodeID-1].getMaxSpeed();
	int distanceToTravel=0;
	int newSpeed=0;
	
	newSpeed = cSpeed + aRate*ticktime;

	distanceToTravel = cSpeed*ticktime + (aRate*ticktime*ticktime)/2;
	//cout << "\ndistanceToTravel without speed limits: " << distanceToTravel << endl;
	//cout << "MY CARS SPEED was: " << v->getCurrentSpeed() << endl;
	//cout << "cars max speed : " <<v->getMaxSpeed()<<endl;


	if (cSpeed==v->getMaxSpeed() && cSpeed<=roadMaxSpeed){
		//check if turn in order to decelerate
		int remain = 0;
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<100)
			{
				remain = (cSpeed-40)/aRate;
				distanceToTravel = cSpeed*remain + ((aRate*remain*remain)/2);
				distanceToTravel = distanceToTravel + ((ticktime-remain) * 40);
				v->setCurrentSpeed(40); 
			}
		else
			distanceToTravel = cSpeed*ticktime;
		//cout << "eftasa to max speed tu car. actual distance: " << distanceToTravel<<endl;
	}
	else if (cSpeed==roadMaxSpeed && cSpeed<=v->getMaxSpeed() ){
		int remain = 0;
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<200)
			{
				remain = (cSpeed-40)/aRate;
				distanceToTravel = cSpeed*remain + ((aRate*remain*remain)/2);
				distanceToTravel = distanceToTravel + ((ticktime-remain) * 40);
				v->setCurrentSpeed(40); 
			}
			else
		distanceToTravel = cSpeed*ticktime;
		//cout << "eftasa to max speed tu road. actual distance: " << distanceToTravel<<endl;
	}
	else if (newSpeed>v->getMaxSpeed() && newSpeed<=roadMaxSpeed)
	{
		int remain = 0;
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<100)
			{
				remain = (cSpeed-40)/aRate;
				distanceToTravel = cSpeed*remain + ((aRate*remain*remain)/2);
				distanceToTravel = distanceToTravel + ((ticktime-remain) * 40);
				v->setCurrentSpeed(40); 
			}
			else{
			int temp = newSpeed-v->getMaxSpeed();
			int remain=temp/aRate;
			distanceToTravel = distanceToTravel - (remain*aRate +(aRate*remain*remain)/2);
			v->setCurrentSpeed(v->getMaxSpeed()); 
			//cout << "piga panw apo to max speed tu car. actual distance: " << distanceToTravel<<endl;
		}
	}
	else if (newSpeed>roadMaxSpeed && roadMaxSpeed>0 && newSpeed<=v->getMaxSpeed()){
			int remain = 0;
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<100)
			{
				remain = (cSpeed-40)/aRate;
				distanceToTravel = cSpeed*remain + ((aRate*remain*remain)/2);
				distanceToTravel = distanceToTravel + ((ticktime-remain) * 40);
				v->setCurrentSpeed(40); 
			}
			else{int temp = newSpeed-roadMaxSpeed;
			int remain=temp/aRate;
			distanceToTravel = distanceToTravel - (remain*aRate +(aRate*remain)/2);
			v->setCurrentSpeed(roadMaxSpeed); 
			//cout << "piga panw apo to max speed tu road. actual distance: " << distanceToTravel<<endl;
		}
	}
	else if (newSpeed>roadMaxSpeed && roadMaxSpeed>0 && newSpeed>=v->getMaxSpeed()){
			int remain = 0;
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<100)
			{
				remain = (cSpeed-40)/aRate;
				distanceToTravel = cSpeed*remain + ((aRate*remain*remain)/2); 
				distanceToTravel = distanceToTravel + ((ticktime-remain) * 40);
					v->setCurrentSpeed(40); 
			}
			else {int temp = newSpeed - max(roadMaxSpeed,v->getMaxSpeed());
			int remain;
			if (aRate!=0){
				remain=temp/aRate;
			distanceToTravel = distanceToTravel - (remain*aRate +(aRate*remain*remain)/2);
			}
			v->setCurrentSpeed(min(roadMaxSpeed,v->getMaxSpeed())); 
			//cout << "pio polli kai apo ta dio. actual distance: " << distanceToTravel<<endl;
		}
	}
		//if is not in the map what???
	else if (roadMaxSpeed<0)
		{
			distanceToTravel=0;
			//cout << "road0. distance: " << distanceToTravel<<endl;
		}
	
	
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

 