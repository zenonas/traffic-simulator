/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: map.cc
Description: This file includes the implementation for the map class.

Copyright (c) King's College London
*/

map::map(int MaxSpeed){
	setMaxSpeed();
}

map::~map(){

}

void map::setMaxSpeed(int x){
	MaxSpeed=x;
}

int map::getMaxSpeed(){
	return MaxSpeed;
}

void map::ReadXMLFile(){
	
}

void map::ConstructMap(){
	ReadXMLFile();
}

