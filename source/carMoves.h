/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 17/3/2013
Updated: 17/3/2013
File: carMoves.h
Description: This file contains functions used for the movement of vehicles (header file)
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
#include <time.h>

using namespace std;

int checkVehicle(vehicle *veh1, vehicle *veh2);
vector<vehicle *> carsInRoadNode(vector<vehicle *> vIengine, roadNode road);
int myNewLaneIs(Position cPos, roadNode *nextRoad,void *arguments);
double calcDistance(vector<int> Path, Position p1, Position p2, void *arguments);
void *nextObstacle(vehicle *cv, bool mylane, double &dist, int &retType, void *arguments);
bool carFits(vehicle *v, vector<vehicle *> vIengine,vector<roadNode> allRoads,void *arguments);
bool canIovertake(vehicle *v, vehicle *nextVehicle, double distanceFRONT, void *arguments);


int DriverDecision(vehicle* v, void *arguments);
int go(vehicle* v, int c, void *arguments, Position &newPos, double &newspeed, double distanceN, bool overtaking);

