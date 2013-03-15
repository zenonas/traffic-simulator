/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: vehicleUpdate.h
Description: This file includes the definition for the vehicleUpdate class.

Copyright (c) King's College London
*/
#ifndef vehicleUpdate_h
#define vehicleUpdate_h

#include "vehicle.h"

using namespace std;

class vehicleUpdate
{
public:
 
   vehicleUpdate(int v, int obj, Position newpos,double newspeed, double newaccs);   
   ~vehicleUpdate();
   void setVehicle(int v);
   int getVehicle();
   void setobsChkd(int obj);
   int getObsChkd();
   void setnewSpeed(double newspeed);
   double getnewSpeed();
   void setnewAccs(double newaccs);
   double getnewAccs();
   void setnewPos(Position newpos);
   Position getnewPos();

private:
  
  int vehi_id, obsChkd;
  double newSpeed, newAccs;
  Position newPos;

};

#endif
