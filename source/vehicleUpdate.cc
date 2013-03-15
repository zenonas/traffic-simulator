/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/3/2013
Updated: 15/3/2013
File: vehicleUpdate.cc
Description: This file includes the implementation for the vehicleUpdate class

Copyright (c) King's College London
*/
#include "vehicleUpdate.h"

vehicleUpdate::vehicleUpdate(int v, int obj, Position newpos, double newspeed, double newaccs){

	setVehicle(v);
	setobsChkd(obj);
	setnewPos(newpos);
	setnewSpeed(newspeed);
	setnewAccs(newaccs);

}

vehicleUpdate::~vehicleUpdate(){

}

void vehicleUpdate::setVehicle(int v) {
	vehi_id=v;
}
int vehicleUpdate::getVehicle() {
	return vehi_id;
}

void vehicleUpdate::setobsChkd(int obj){
	obsChkd = obj;
}
int vehicleUpdate::getObsChkd(){	
	return obsChkd;
}

void vehicleUpdate::setnewSpeed(double newspeed){
	newSpeed=newspeed;
}
double vehicleUpdate::getnewSpeed(){
	return newSpeed;
}

void vehicleUpdate::setnewAccs(double newaccs){
	newAccs=newaccs;
}
double vehicleUpdate::getnewAccs(){
	return newAccs;
}

void vehicleUpdate::setnewPos(Position newpos){
	newPos=newpos;
}
Position vehicleUpdate::getnewPos(){
	return newPos;
}
  