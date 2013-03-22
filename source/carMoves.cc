/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 5/3/2013
Updated: 19/3/2013
File: carMoves.cc
Description: This file contains functions used for the movement of vehicles
Copyright (c) King's College London

*/

#include "carMoves.h"

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

int myNewLaneIs(Position cPos, roadNode *nextRoad,void *arguments) {
	struct thread_arguments *thread_args;
	thread_args = (struct thread_arguments *)arguments;
	roadNode *cRoad = thread_args->mymap.getroadNode(cPos.roadNodeID);
	// find non common graphnodes

	if (cPos.roadNodeID == -1) 
		return cPos.lane;
		
	if ((cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX() && cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY()) && (cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX() && cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY()))
	{
		return cPos.lane;
	} 
	else if ((cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX() && cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())) 
	{
		if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX() && cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
	}
	else if((cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX() && cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())) 
	{
		if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX() && cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeB().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeB().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
	}
	else if((cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX() && cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())) 
	{
		if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX() && cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeB().getCartesianY())
			return cPos.lane;
	}
	else if ((cRoad->getgraphNodeB().getCartesianX() == nextRoad->getgraphNodeB().getCartesianX() && cRoad->getgraphNodeB().getCartesianY() == nextRoad->getgraphNodeB().getCartesianY())) 
	{
		if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX() && cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			if (cPos.lane == 1) return 0;
				else return 1;
		else if (cRoad->getgraphNodeA().getCartesianX() < nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() > nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() > nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() == nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
		else if (cRoad->getgraphNodeA().getCartesianX() == nextRoad->getgraphNodeA().getCartesianX()&& cRoad->getgraphNodeA().getCartesianY() < nextRoad->getgraphNodeA().getCartesianY())
			return cPos.lane;
	} 
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
			distance += p2.p;
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
	int correctLane;
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
		correctLane = myNewLaneIs(cv->getCurrentPosition(), road, thread_args);
		if (cv->getCurrentPosition().roadNodeID == cvPath[p] && roadNodeVehicles.size() > 1) {
			for (int y=0; y<roadNodeVehicles.size(); y++) {
				if (cv->vehi_id != roadNodeVehicles[y]->vehi_id && roadNodeVehicles[y]->getCurrentPosition().lane == correctLane) {
					tempDistanceV = calcDistance(cv->getPath(), cv->getCurrentPosition(), roadNodeVehicles[y]->getCurrentPosition(), thread_args);
					if (tempDistanceV < minDistanceV){
						minDistanceV = abs(tempDistanceV);
						vObs = roadNodeVehicles[y];
						nextVfound = true;
					}
				}
			}
			break;
		} else if (cv->getCurrentPosition().roadNodeID != cvPath[p] && roadNodeVehicles.size() > 0) {
			for (int y=0; y<roadNodeVehicles.size(); y++) {
				if (roadNodeVehicles[y]->getCurrentPosition().lane == correctLane) {
					tempDistanceV = calcDistance(cv->getPath(), cv->getCurrentPosition(), roadNodeVehicles[y]->getCurrentPosition(), thread_args);
					if (tempDistanceV < minDistanceV){
						minDistanceV = abs(tempDistanceV);
						vObs = roadNodeVehicles[y];
						nextVfound = true;
					}
				}
			}
			break;
		}

	}
	for (int tl=startat; tl<cvPath.size(); tl++){
		correctLane = myNewLaneIs(cv->getCurrentPosition(), thread_args->mymap.getroadNode(cvPath[tl]), thread_args);

		for (int z = 0; z<thread_args->mymap.trafficlights.size(); z++) {
			if (thread_args->mymap.trafficlights[z]->getPos().roadNodeID == cvPath[tl] && thread_args->mymap.trafficlights[z]->getState() == 0 &&  thread_args->mymap.trafficlights[z]->getPos().lane == correctLane)  {
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

bool canIovertake(vehicle *v, void *nextObs, int distanceFRONT, void *arguments){
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int distanceOL;
	int distanceTHIRD;
	int retType;
	int retTypeTHIRD;
	void *OLobstacle;
	void *thirdObstacle;
	vehicle *nextVehicle = (vehicle *)nextObs;
	vehicle *VehicleOL;
	vehicle *thirdVehicle;
	trafficLight *thirdTL;
	OLobstacle = nextObstacle(nextVehicle,distanceOL, retType,thread_args);
	thirdObstacle = nextObstacle(nextVehicle,distanceTHIRD,retTypeTHIRD,thread_args);
	if (retType == 1) {
		VehicleOL = (vehicle *)OLobstacle;
	} else if (retType == 2) {
		OLobstacle = NULL;
	}
	if (retTypeTHIRD == 1) {
		vehicle *thirdVehicle = (vehicle *)thirdObstacle;
	} else if (retTypeTHIRD == 2) {
		trafficLight *thirdTL = (trafficLight *)thirdObstacle;
	}
	double timeToAcs = (v->getMaxSpeed() - v->getCurrentSpeed())/v->getAcceleration();
	double distanceTravelledWhileAccellerating = (timeToAcs *v->getCurrentSpeed()) + ((v->getAcceleration() * timeToAcs * timeToAcs)/2.0);
	double restOfTheDistance = (thread_args->sleep_time - timeToAcs) * v->getMaxSpeed();
	int gap;
	if (v->getDriverType() == 0) gap = 10; else gap = 3;
	double totalDistance = distanceTravelledWhileAccellerating + restOfTheDistance + gap;

	if (v->getDriverType() == 1) {
		return false; 
	} else if ((v->getDriverType() == 0 && nextVehicle->getDriverType() == 1) || v->getDriverType() == 2) {
		if (OLobstacle == NULL && thirdObstacle == NULL) return true; // no on coming car and no car infront of the on going vehicle
		if (OLobstacle == NULL && thirdObstacle != NULL) {
			if (retTypeTHIRD == 1) {
				distanceTHIRD += (thirdVehicle->getCurrentSpeed() * thread_args->sleep_time);
			} 
			if (totalDistance < distanceTHIRD) return true; else if (totalDistance >= distanceTHIRD) return false;
		}
		if (OLobstacle != NULL && thirdObstacle == NULL) {
			distanceOL -= (thread_args->sleep_time * VehicleOL->getMaxSpeed());
			distanceOL += distanceFRONT;
			if (totalDistance < distanceOL) return true; else if (totalDistance >= distanceOL) return false;
		}
		if (OLobstacle != NULL && thirdObstacle != NULL) {
			distanceOL -= (thread_args->sleep_time * VehicleOL->getMaxSpeed());
			distanceOL += distanceFRONT;
			if (totalDistance < distanceOL) {
				if (totalDistance < distanceTHIRD && retTypeTHIRD == 2) {
					return true;
				} else if (totalDistance >= distanceTHIRD && retTypeTHIRD == 2) {
					return false;
				}
				if (retTypeTHIRD == 1) {
					distanceTHIRD += (thirdVehicle->getCurrentSpeed() * thread_args->sleep_time);
					if (totalDistance < distanceTHIRD) {
						return true;
					} else if (totalDistance >= distanceTHIRD) {
						return false;
					}
				}
			}
		}
	} 
}




int DriverDecision(vehicle* v, void *arguments)
{	
	struct thread_arguments *thread_args;
	thread_args =(struct thread_arguments *)arguments;
	int distance;
	int NextType;
	void *obstacle;
	obstacle = nextObstacle(v, distance, NextType, thread_args); 
	int re;
	//vehicle *nextVehicle;
	trafficLight *nextTL;
	vector<int> vPath = v->getPath();
	//cout << "META: " << NextType << endl;

	Position newPos;
	double newspeed;
	if (NextType == 0) {
		double max = thread_args->mymap.getroadNode(v->getCurrentPosition().roadNodeID)->getMaxSpeed();
		if (v->getCurrentSpeed() == max){
			re = go(v, 3, thread_args, newPos, newspeed);
			v->setCurrentSpeed(newspeed);
			v->setCurrentPosition(newPos);
		}
		else{
			re = go(v, 1, thread_args, newPos, newspeed);
			if (newspeed > max )
				v->setCurrentSpeed(max);
			else
				v->setCurrentSpeed(newspeed);
			v->setCurrentPosition(newPos);
		}
		v->updated = true;
	} else if (NextType == 1) {
		cout << "I SEE YOU CAR";
		// DEN EXEI GINEI AKOMA
		/*
		nextVehicle = (vehicle *)obstacle;
		if (nextVehicle->updated) {
			result = move(v, speedForMinGap(v, distance, thread_args), thread_args);
			v->updated = true;
			return true;
		} else {
			DriverDecision(nextVehicle, thread_args);
		}
		*/
	} else if (NextType == 2) {

		nextTL = (trafficLight *)obstacle;
		double max = thread_args->mymap.getroadNode(v->getCurrentPosition().roadNodeID)->getMaxSpeed();
		double d = (v->getCurrentSpeed() *v->getCurrentSpeed() )/(2*v->getAcceleration());

		if(distance - max*thread_args->sleep_time  > d){	
			if (v->getCurrentSpeed() == max)
				re= go(v, 3, thread_args, newPos, newspeed);
			else
				re =go(v, 1, thread_args, newPos, newspeed);

			if (newspeed > max )
				v->setCurrentSpeed(max);
			else
				v->setCurrentSpeed(newspeed);
			v->setCurrentPosition(newPos);

		}else{	
			re = go(v, 2, thread_args, newPos, newspeed);
			v->setCurrentSpeed(newspeed);
			v->setCurrentPosition(newPos);
		}

		v->updated = true;
	} 
	return re;
}




int go(vehicle* v, int c, void *arguments, Position &newPos, double &newspeed){

struct thread_arguments *thread_args;
thread_args =(struct thread_arguments *)arguments;

double distanceToTravel;

newPos.roadNodeID = v->getCurrentPosition().roadNodeID;
newPos.lane = v->getCurrentPosition().lane;
newPos.p = v->getCurrentPosition().p;
vector<int> vPath = v->getPath();


// ACCELERATION
if (c == 1){
	newspeed = v->getCurrentSpeed() + v->getAcceleration() * thread_args->sleep_time;
	distanceToTravel = v->getCurrentSpeed() * thread_args->sleep_time + (v->getAcceleration()* thread_args->sleep_time*thread_args->sleep_time)/2;
}
// DECELERATION
else if (c == 2){
	newspeed = v->getCurrentSpeed() - v->getAcceleration() * thread_args->sleep_time;
	distanceToTravel = v->getCurrentSpeed() * thread_args->sleep_time - (v->getAcceleration()* thread_args->sleep_time*thread_args->sleep_time)/2;
}
else if (c == 3){
	newspeed = v->getCurrentSpeed();
	distanceToTravel = v->getCurrentSpeed() * thread_args->sleep_time;
}

if (newspeed <= 0) {
	newspeed = 0;
	return 1;
}

int z=0;
bool roadChange = false;
while(distanceToTravel >= (thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p)) {
	if (newPos.roadNodeID == vPath.back() && vPath.size() > 1) return -1;	
	int tempDistance = thread_args->mymap.getroadNode(newPos.roadNodeID)->getLength() - newPos.p;
	distanceToTravel -= tempDistance;
	for (z=0; z<vPath.size(); z++) {
		if (vPath[z] == newPos.roadNodeID) {
			if (z+1<vPath.size()) 
				z++;
			else 
				return -1; 
			newPos.roadNodeID = vPath[z];
			newPos.p = 0;
			newPos.lane = myNewLaneIs(v->getCurrentPosition(),thread_args->mymap.getroadNode(vPath[z]),thread_args);
			break;
		}		
	}
	roadChange=true;
} 
	
if (roadChange) 
	newPos.p = distanceToTravel;
else
	newPos.p += distanceToTravel;
return 1;
}

