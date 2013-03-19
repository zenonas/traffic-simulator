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

using namespace std;

int checkVehicle(vehicle *veh1, vehicle *veh2);
vector<vehicle *> carsInRoadNode(vector<vehicle *> vIengine, roadNode road);
int myNewLaneIs(Position cPos, roadNode *nextRoad,void *arguments);
int calcDistance(vector<int> Path, Position p1, Position p2, void *arguments);
void *nextObstacle(vehicle *cv, int &dist, int &retType, void *arguments);
bool carFits(vehicle *v, vector<vehicle *> vIengine,vector<roadNode> allRoads,void *arguments);
void *nextObstacleOL(vehicle *cv, int &dist, int &retType, void *arguments);
bool canIovertake(vehicle *v, void *nextObs, int distanceFRONT, void *arguments);
double move(vehicle *v, double targetSpeed, void *arguments);
double speedForMinGap(vehicle *v, double distanceTarget, void *arguments);
bool DriverDecision(vehicle* v, void *arguments);