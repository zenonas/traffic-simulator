/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: vehicle.cc
Description: This file includes the implementation for the vehicle class.

Copyright (c) King's College London
*/

#include "vehicle.h"
#include "roadNode.h"
#include "graphNode.h"

vehicle::vehicle(){
	
	

}

vehicle::~vehicle(){

}

void vehicle::setType(int type){
	Type=type;
}

int vehicle::getType(){
	return Type;
}

void vehicle::setCurrentSpeed(int x){
	CurrentSpeed=x;
}

int vehicle::getCurrentSpeed(){
	return CurrentSpeed;
}

void vehicle::setDriverType(int type){
	DriverType=type;
}

int vehicle::getDriverType(){
	return DriverType;
}

void vehicle::setAcceleration(int x){
	Acceleration=x;
}

int vehicle::getAcceleration(){
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
	CurrentPosition.x =pos.x;
	CurrentPosition.y =pos.y;
	CurrentPosition.p =pos.p;
}

Position vehicle::getCurrentPosition(){
	return CurrentPosition;
}

void vehicle::setPreviousPosition(Position pos){
	PreviousPosition.x =pos.x;
	PreviousPosition.y =pos.y;
	PreviousPosition.p =pos.p;
}

Position vehicle::getPreviousPosition(){
	return PreviousPosition;
}

void vehicle::calculatePath(){
	cout << "Calculate Path";
}

roadNode* vehicle::getPath(){
	return Path;
}
