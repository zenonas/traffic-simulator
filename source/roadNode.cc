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
	A.Type = a.getType();
	A.CartesianX = a.getCartesianX;
	A.CartesianY = a.getCartesianY;
}

graphNode roadNode::getgraphNodeA(){
	return A;
}

void roadNode::setgraphNodeB(graphNode b){
	B.Type= b.setType;
	B.CartesianX = b.getCartesianX;
	B.CartesianY = b.getCartesianY;
}

graphNode roadNode::getgraphNodeA(){
	return B;
}

void roadNode::setLength(int l){
	Length=l;
}

int roadNode::getLength(){
	return Length;
}


