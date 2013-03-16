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
#include "trafficLight.h"
#include "position.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int checkVehicle(vehicle *veh1, vehicle *veh2){
     vector<int> vehicle1Path = veh1->getPath();
     vector<int> vehicle2Path = veh2->getPath();
     for (int p=0; p<vehicle1Path.size(); p++)
            for (int q=0; q<vehicle2Path.size(); q++)                           
               if (vehicle1Path[p]==vehicle2Path[q])	
               		return 1;
    return 0;
}

vector<vehicle *> carsInRoadNode(vector<vehicle *> vIengine, roadNode road) {
	vector<vehicle *> carList;
	for (int i=0; i<vIengine.size(); i++) {
		int id = vIengine[i]->getCurrentPosition().roadNodeID;
		if (id == road.getId())
			carList.push_back(vIengine[i]);
	}
	return carList;
}

int calcDistance(vector<int> Path, Position p1, Position p2, void *arguments) {
	struct thread_arguments *thread_args;
	thread_args = (struct thread_arguments *)arguments;
	int distance = 0;
	for (int i=0; i<Path.size(); i++) {
		if (Path[i] == p1.roadNodeID && Path[i] != p2.roadNodeID) {
			roadNode *cRoad = thread_args->mymap.getroadNode(Path[i]);
			distance = cRoad->getLength() - p1.p;
		} 
		if (Path[i] != p1.roadNodeID && Path[i] != p2.roadNodeID) {
			roadNode *cRoad = thread_args->mymap.getroadNode(Path[i]);
			distance += cRoad->getLength();
		}
		if (Path[i] != p1.roadNodeID && Path[i] == p2.roadNodeID) {
			roadNode *cRoad = thread_args->mymap.getroadNode(Path[i]);
			distance += (cRoad->getLength() - p2.p);
			break;
		}
		if (Path[i] == p1.roadNodeID && Path[i] == p2.roadNodeID) {
			distance = p1.p - p2.p;
			break;
		}
	}
	return distance;
}

void *nextObstacle(vehicle *cv, int &dist, int &retType, void *arguments) {
	void *obs;
	struct thread_arguments *thread_args;
	thread_args = (struct thread_arguments *)arguments;
	int minDistanceV = 0;
	int minDistanceTL = 0;
	bool nextVfound = false;
	bool nextTLfound = false;
	vehicle *vObs;
	trafficLight *tlObs;
	vector<int> cvPath = cv->getPath();
	int startat;
	// first find current point in path
	for (int x=0; x<cvPath.size(); x++) {
		if (cv->getCurrentPosition().roadNodeID == cvPath[x]) {
			startat = x;
			break;
		}
	}
	// from current point move on
	for (int p=startat; p<cvPath.size(); p++) {
		int tempDistanceV;
		roadNode *road = thread_args->mymap.getroadNode(cvPath[p]);
		vector<vehicle *> roadNodeVehicles = carsInRoadNode(thread_args->vehiclesInEngine, *road);
		if (cv->getCurrentPosition().roadNodeID == cvPath[p] && roadNodeVehicles.size() > 1) {
			for (int y=0; y<roadNodeVehicles.size(); y++) {
				if (cv->vehi_id != roadNodeVehicles[y]->vehi_id) {
					tempDistanceV = calcDistance(cv->getPath(), cv->getCurrentPosition(), roadNodeVehicles[y]->getCurrentPosition(), thread_args);
					if (tempDistanceV < minDistanceV){
						minDistanceV = abs(tempDistanceV);
						vObs = roadNodeVehicles[y];
						nextVfound = true;
					}
				}
			}
		} else if (roadNodeVehicles.size() > 0) {
			for (int y=0; y<roadNodeVehicles.size(); y++) {
				if (cv->vehi_id != roadNodeVehicles[y]->vehi_id) {
					tempDistanceV = calcDistance(cv->getPath(), cv->getCurrentPosition(), roadNodeVehicles[y]->getCurrentPosition(), thread_args);
					if (tempDistanceV < minDistanceV){
						minDistanceV = abs(tempDistanceV);
						vObs = roadNodeVehicles[y];
						nextVfound = true;
					}
				}
			}
		}
	}
	for (int tl=startat; tl<cvPath.size(); tl++){
		for (int z = 0; z<thread_args->mymap.trafficlights.size(); z++) {
			if (thread_args->mymap.trafficlights[z]->getPos().roadNodeID == cvPath[tl] && thread_args->mymap.trafficlights[z]->getState() == 0)  {
				int tempDistanceTL = calcDistance(cv->getPath(), cv->getCurrentPosition(), thread_args->mymap.trafficlights[z]->getPos(), thread_args);
				if (tempDistanceTL < minDistanceTL){
					minDistanceTL = abs(tempDistanceTL);
					tlObs = thread_args->mymap.trafficlights[z];
					nextTLfound = true;
				}
			}
		}
	}
	if ((minDistanceV < minDistanceTL && nextVfound == true) || (minDistanceTL == 0 && nextVfound == true)) {
		dist = minDistanceV;
		retType = 1;
		obs = vObs;
	} else if ((minDistanceV > minDistanceTL && nextTLfound == true) || (minDistanceV == 0 && nextTLfound == true)) {
		dist = minDistanceTL;
		retType = 2;
		obs = tlObs;
	} else {
		dist = 0;
		retType = 0;
		obs = NULL;
	}
	return obs;
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
		int spaceAvailable = closestP;
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

	//find the next roadnode to check if there is a turn
	int nextRoadID=-1;
	for (int i=0; i<vPath.size(); i++)
		if (vPath[i] == newPos.roadNodeID)
			nextRoadID=vPath[i+1];

	float cSpeed = v->getCurrentSpeed();
	float newSpeed=0;
	int distanceToTravel=0;

	//get the vehicle's acceleration if the vehicle can accelerate
	//else the vehicle's acceleration will pass to this function
	if (aRate==1)
		aRate = v->getAcceleration();
	else if(aRate==-1){
		aRate = (-1) * v->getAcceleration();
		//cout << "reduce speed";
		float remain = (cSpeed-s->getCurrentSpeed())/aRate;
	//	cout << "remain1:" <<remain;
		distanceToTravel =  cSpeed*(ticktime-remain) + (remain*remain*aRate)/2 + (remain)*cSpeed;
		v->setCurrentSpeed(s->getCurrentSpeed());
	}
	int roadMaxSpeed=-1;
	//get roadNode maximum speed
	if (newPos.roadNodeID>0)
		roadMaxSpeed = roads[v->getCurrentPosition().roadNodeID-1].getMaxSpeed();

	if (cSpeed==v->getMaxSpeed() && cSpeed<=roadMaxSpeed){
		
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				float remain = 0;
				remain = (cSpeed-11)/v->getAcceleration();
			//	cout << "remain2:" <<remain;
				distanceToTravel =  cSpeed*(ticktime-remain) + (remain*remain*(0-aRate))/2.0 + remain*11;
				v->setCurrentSpeed(11); 
			}
		else
			distanceToTravel = cSpeed*ticktime;	
	}
	else if (cSpeed==roadMaxSpeed && cSpeed<=v->getMaxSpeed() ){
		
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				float remain = 0;
				remain = (cSpeed-11)/v->getAcceleration();
				distanceToTravel =  cSpeed*(ticktime-remain) + (remain*remain*(0-aRate))/2.0 + remain*11;
				v->setCurrentSpeed(11); 
			}
		else{
				distanceToTravel = cSpeed*ticktime;		
		}
	}
	else if (cSpeed<=v->getMaxSpeed() && cSpeed<=roadMaxSpeed)
	{
		
		//check if two roadnodes form a turn
		if (thread_args->mymap.checkTurn(newPos.roadNodeID, nextRoadID) && (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength()-newPos.p)<cSpeed*ticktime)
			{
				float remain = 0;
				remain = (cSpeed-11)/v->getAcceleration();
				distanceToTravel =  cSpeed*(ticktime-remain) + (remain*remain*(0-aRate))/2.0 + remain*11;		v->setCurrentSpeed(11); 
			}
		else{
			float remain = (min(v->getMaxSpeed(),roadMaxSpeed) - cSpeed) / aRate;
			if (remain>ticktime){
				distanceToTravel = ticktime*ticktime*aRate/2;
				v->setCurrentSpeed(ticktime*aRate);
			}
			else{
				distanceToTravel = remain*cSpeed + (remain*remain*aRate)/2;
				distanceToTravel = distanceToTravel + min(v->getMaxSpeed(),roadMaxSpeed)*(ticktime-remain);
				v->setCurrentSpeed(min(v->getMaxSpeed(),roadMaxSpeed)); 
			}
		}
	}
		//if is not in the map what???
	else if (roadMaxSpeed<0)
		{
			distanceToTravel=0;
			//cout << "road0. distance: " << distanceToTravel<<endl;
		}
	//else v->setCurrentSpeed(newSpeed);
	
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
		else{ newPos.p += distanceToTravel;
		//	cout << "distance: " << distanceToTravel << " newpos " <<newPos.p;

		}
	v->setCurrentPosition(newPos);
	return 1;
}


 