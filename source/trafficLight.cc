/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: trafficLight.cc
Description: This file includes the implementation for the trafficLight class.

Copyright (c) King's College London
*/
#include "trafficLight.h"
#include <time.h>
#include <stdlib.h>

trafficLight::trafficLight(){

	State = rand()%2;	
}

trafficLight::~trafficLight(){

}

void trafficLight::setState(int state){
	State=state;
}

int trafficLight::getState(){
	return State;
}

void trafficLight::setTimer(int timer){
	Timer=timer;
}

int trafficLight::getTimer(){
	return Timer;
}
void trafficLight::setCartesianX(int x){
	CartesianX=x;
}

int trafficLight::getCartesianX(){
	return CartesianX;
}

void trafficLight::setCartesianY(int y){
	CartesianY=y;
}

int trafficLight::getCartesianY(){
	return CartesianY;
}

void trafficLight::setLane(int lane) {
	LightPos.lane = lane;
}

void trafficLight::setPos(roadNode *roadnode){
	LightPos.roadNodeID = roadnode->getId();
	LightPos.p = roadnode->getLength();
	if (roadnode->getgraphNodeA().getCartesianX() < roadnode->getgraphNodeB().getCartesianX()){
		LightPos.lane = 0;
	} else if (roadnode->getgraphNodeA().getCartesianX() > roadnode->getgraphNodeB().getCartesianX()){
		LightPos.lane = 1;
	} else if (roadnode->getgraphNodeA().getCartesianY() < roadnode->getgraphNodeB().getCartesianY()) {
		LightPos.lane = 0;
	} else if (roadnode->getgraphNodeA().getCartesianY() > roadnode->getgraphNodeB().getCartesianY()){
		LightPos.lane = 1;
	}
}

Position trafficLight::getPos(){
	return LightPos;
}