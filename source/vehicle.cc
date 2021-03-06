/* 
Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: vehicle.cc
Description: This file includes the implementation for the vehicle class.

Copyright (c) King's College London
*/

#include "vehicle.h"
#include <iostream>
#include <vector>
using namespace std;

vehicle::vehicle(int id, int entryP, int exitP, map mymap){
	vehi_id = id;
	CurrentSpeed = 0;
	Acceleration = 0;
	entryPoint = entryP;
	exitPoint = exitP;

	calculatePath(mymap);
	//initialize current pos
	CurrentPosition.roadNodeID = entryPoint;
	CurrentPosition.p=0;
	CurrentPosition.lane = decideLane(mymap);
	//cout << "I return pos lane: " << CurrentPosition.lane << endl;
	Timer = 0;
	updated = false;
	crash_timer = 0;
	crashed = false;
}

vehicle::~vehicle(){

}

void vehicle::setEntryPoint(int entryP){
	entryPoint=entryP;
}

void vehicle::setExitPoint(int exitP){
	exitPoint=exitP;
}

int vehicle::decideLane(map mymap){
	roadNode *entry = mymap.getroadNode(entryPoint);
	if (entry->getgraphNodeA().getCartesianX() < entry->getgraphNodeB().getCartesianX()){
		return 0;
	} else if (entry->getgraphNodeA().getCartesianX() > entry->getgraphNodeB().getCartesianX()){
		return 1;
	} else if (entry->getgraphNodeA().getCartesianY() < entry->getgraphNodeB().getCartesianY()) {
		return 0;
	} else if (entry->getgraphNodeA().getCartesianY() > entry->getgraphNodeB().getCartesianY()){
		return 1;
	}
}

int vehicle::getEntryPoint(){
	return entryPoint;
}

int vehicle::getExitPoint(){
	return exitPoint;
}

void vehicle::setType(int type){
	Type=type;
	if (type == 0){
		setMaxSpeed(45);
		VLength = 4;
		//after 5 sec will  have 72km/h
		setAcceleration(4);
	}
	else if (type == 1){
		setMaxSpeed(27);
		VLength = 12;
		//after 5 sec will  have 54km/h
		setAcceleration(2);
	}
	else if (type == 2){
		setMaxSpeed(20);
		VLength = 16;
		//after 5 sec will  have 36km/h
		setAcceleration(1);	
	}
}

void vehicle::setMaxSpeed(int speed){
	MaxSpeed=speed;
}

int vehicle::getMaxSpeed(){
	return MaxSpeed;
}

void vehicle::setVLength(int length){
	VLength = length;
}

int vehicle::getVLength(){
	return VLength;
}

int vehicle::getType(){
	return Type;
}

void vehicle::setCurrentSpeed(double x){
	CurrentSpeed=x;
}

double vehicle::getCurrentSpeed(){
	return CurrentSpeed;
}

void vehicle::setDriverType(int type){
	DriverType=type;
}

int vehicle::getDriverType(){
	return DriverType;
}

void vehicle::setAcceleration(double x){
	Acceleration=x;
}

double vehicle::getAcceleration(){
	return Acceleration;
}

void vehicle::setCartesianPosition(int cartesianPosition[]){
	CartesianPosition[0]=cartesianPosition[0];
	CartesianPosition[1]=cartesianPosition[1];
}

int* vehicle::getCartesianPosition(){
	return CartesianPosition;
}

void vehicle::setCurrentPosition(Position pos){
	CurrentPosition.roadNodeID=pos.roadNodeID;
	CurrentPosition.lane =pos.lane;
	CurrentPosition.p =pos.p;
}

Position vehicle::getCurrentPosition(){
	return CurrentPosition;
}

void vehicle::setPreviousPosition(Position pos){
	CurrentPosition.roadNodeID=pos.roadNodeID;
	CurrentPosition.lane =pos.lane;
	CurrentPosition.p =pos.p;
}

Position vehicle::getPreviousPosition(){
	return PreviousPosition;
}

//calculate path depending on total LENGTH
void vehicle::calculatePath(map mymap){
	//IN HERE WE NEED TO FILL ALL THE ATTRIBUTES 
	// CONCERNING THE MAP
	vector<vector<int> > paths = mymap.getAllPaths();
	vector<roadNode> unfRoads = mymap.getunfRoads();
	int length=0;
	int shortest=1000000;
	int p=0;
	int position=0;
	for(int k=0; k<paths.size(); k++){
		//check only paths starting from vehicles entry point
		if (paths[k][0]==getEntryPoint()){
			length=0;
			int pos=0;
			for(int l=0; l<paths[k].size(); l++)
				if (paths[k][l]!=getExitPoint()){
					length+= unfRoads[paths[k][l]-1].getLength();
					pos++;
				}
				else if (length<shortest){
 					shortest=length;
					p=k;					
					position=pos;
					pos++;
				}
		}
	}
	for(int x=0; x<=position; x++)
	Path.push_back(paths[p][x]);
}

void vehicle::printPath(){

	int length=0;
	cout << "Path: ";
	for (int i=0; i<Path.size(); i++){
		cout << Path[i] << " ";
	}
}

vector<int> vehicle::getPath(){
	return Path;
}

int vehicle::getTimer(){
	return Timer;
}

void vehicle::setTimer(int t){
	Timer = t;
}