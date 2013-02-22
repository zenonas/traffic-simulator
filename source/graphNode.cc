/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: graphNode.cc
Description: This file includes the implementation for the graphNode class.

Copyright (c) King's College London
*/
#include "graphNode.h"
#include "trafficLight.h"

graphNode::graphNode(){
	
}

graphNode::~graphNode(){

}

void graphNode::setCartesianX(int x){
	CartesianX=x;
}

int graphNode::getCartesianX(){
	return CartesianX;
}

void graphNode::setCartesianY(int y){
	CartesianY=y;
}

int graphNode::getCartesianY(){
	return CartesianY;
}

void graphNode::setType(int type){
	Type=type;
}

int graphNode::getType(){
	return Type;
}

void graphNode::setTrafficLight(trafficLight* t){
	trafficLights=t;
}

trafficLight* graphNode::getTrafficLight(){
	return trafficLights;
}




