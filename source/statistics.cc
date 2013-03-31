/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 08/2/2013
Updated: 08/2/2013
File: statistics.cc
Description: This file includes the implementation for the statistics class.

Copyright (c) King's College London
*/

#include "statistics.h"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <math.h>

statistics::statistics(){
	VehMap = NULL;
	vehiclesCrashed = 0;
	vehicesRemoved = 0;
	vehicletypenum.resize(3);
	drivertypenum.resize(3);

   	avspeed =0;
    avtimeinengine =0;
    most_visited_road = -1;
    most_common_exitP = 0;
    most_common_entryP = 0;
    total = 0;
}

statistics::~statistics(){

	
}

void statistics::CaptureStatistics(map* mymap, vector<vehicle *> vehiclesInEngine){

	VehMap = mymap;
	VehEng = vehiclesInEngine;
	int j;
	double speedsum = 0;
	double timesum = 0;
	vector<int> countEntryP(VehMap->getunfRoads().size());
	vector<int> countExitP(VehMap->getunfRoads().size());
	for(j=0; j< VehMap->getunfRoads().size(); j++)
	{
		countEntryP[j] = 0;
		countExitP[j] = 0;
	}
	for(j=0; j<3; j++)
	{
		vehicletypenum[j] = 0;
		drivertypenum[j] = 0;
	}



	for(int i=0; i< vehiclesInEngine.size(); i++){
		speedsum += vehiclesInEngine[i]->getCurrentSpeed();
		timesum += vehiclesInEngine[i]->getTimer();
		int entryp =  vehiclesInEngine[i]->getEntryPoint() -1;
		int exitp = vehiclesInEngine[i]->getExitPoint() -1 ;
		countEntryP[entryp]++;
		countExitP[exitp]++;	


		vehicletypenum[vehiclesInEngine[i]->getType()]++;
		drivertypenum[vehiclesInEngine[i]->getDriverType()]++;

	}
	most_common_entryP = 0;
	most_common_exitP = 0;
	int tempcarsexit = countExitP[0];
	int tempcarsentry = countEntryP[0];
	for(int k=1; k<countEntryP.size(); k++)
	{
		if(countEntryP[k]>tempcarsentry)
		{
			tempcarsentry = countEntryP[k];
			most_common_entryP = k;
		}
		if(countExitP[k]>tempcarsexit)
		{
			tempcarsexit = countEntryP[k];
			most_common_exitP = k;
		}

	}
	most_common_entryP++;
	most_common_exitP++;
	if(vehiclesInEngine.size()!=0)
	{
		avspeed = double(speedsum / vehiclesInEngine.size());
		avtimeinengine = double(timesum / vehiclesInEngine.size());
	}
	total = vehiclesInEngine.size();

}


double statistics::getAvSpeed(){
	return avspeed;
}
   
double statistics::getAvTimeinEngine(){
	return avtimeinengine;
}

/* NOT DONE */
int statistics::getMostVisitedRoad(){
	return 0;
}

int statistics::getMostCommonExitP(){
	return most_common_exitP;
}

int statistics::getMostCommonEntryP(){
	return most_common_entryP;
}

int statistics::getVehicleTypeNum(int vehicleType){
	return vehicletypenum[vehicleType];
}
   
int statistics::getDriverTypeNum(int driverType){
	return drivertypenum[driverType];
} 

int statistics::getTotalVehicles(){
	return total;
}

void statistics::addRemVehi(){
	vehicesRemoved++;
}

int statistics::getRemVehi(){
	return vehicesRemoved;
}

void statistics::addCrashedVehicle(){
	vehiclesCrashed++;
}

int statistics::getTotalCrashedVehicles(){
	return vehiclesCrashed;
}

map* statistics::getMap(){
	return VehMap;
}

vector<vehicle *> statistics::getVehiclesInEngine(){
	return VehEng;
}

