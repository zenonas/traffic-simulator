/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: trafficLight.cc
Description: This file includes the implementation for the trafficLight class.

Copyright (c) King's College London
*/
#include "trafficLight.h"

trafficLight::trafficLight(){
	
}

trafficLight::~trafficLight(){

}

void trafficLight::setState(int state){
	State=state;
}

int trafficLight::getState(){
	return State;
}


