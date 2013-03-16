/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: roadNode.cc
Description: This file includes the implementation for the roadNode class.

Copyright (c) King's College London
*/
#include "roadNode.h"
#include "graphNode.h"

roadNode::roadNode(){
	
}

roadNode::~roadNode(){

}

void roadNode::setgraphNodeA(graphNode a){
	A.setType(a.getType());
	A.setTimer(a.getTimer());
	A.setState(a.getState());
	A.setCartesianX(a.getCartesianX());
	A.setCartesianY(a.getCartesianY());
	A.setRoad(a.getRoad());
}

graphNode roadNode::getgraphNodeA(){
	return A;
}

void roadNode::setgraphNodeB(graphNode b){
	B.setType(b.getType());
	B.setTimer(b.getTimer());
	B.setState(b.getState());
	B.setCartesianX(b.getCartesianX());
	B.setCartesianY(b.getCartesianY());
	B.setRoad(b.getRoad());
}

graphNode roadNode::getgraphNodeB(){
	return B;
}

void roadNode::setLength(int l){
	Length=l;
}

int roadNode::getLength(){
	return Length;
}

void roadNode::setMaxSpeed(int s){
	MaxSpeed=s;
}

int roadNode::getMaxSpeed(){
	return MaxSpeed;
}

void roadNode::setId(int id){
	Id=id;
}

int roadNode::getId(){
	return Id;
}

