/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: vehicle.h
Description: This file includes the definition for the vehicle class.

Copyright (c) King's College London
*/

#ifndef vehicle_h
#define vehicle_h

#include "map.h"
#include "position.h"
#include <vector>

using namespace std;

class vehicle
{
public:
   vehicle(int id, int entryP, int exitP, map mymap);   
   ~vehicle();
   
   void setEntryPoint(int entryP);
   int getEntryPoint();
   void setExitPoint(int exitP);
   int getExitPoint();
   void setType(int type);
   int getType();
   void setCurrentSpeed(double x);
   double getCurrentSpeed();
   void setMaxSpeed(int speed);
   int getMaxSpeed();
   void setVLength(int length);
   int getVLength();
   void setDriverType(int type);
   int getDriverType();
   void setAcceleration(double x);
   double getAcceleration();
   void setCartesianPosition(int CartesianPosition[]);
   int* getCartesianPosition();
   void setCurrentPosition(Position C);
   Position getCurrentPosition();
   void setPreviousPosition(Position C);
   Position getPreviousPosition();
   void calculatePath(map mymap);
   vector<int> getPath();
   void printPath();
   void setTimer(int t);
   int getTimer();
   int decideLane(map mymap);
   int vehi_id;
   bool updated;

private:
   int Type, DriverType, Acceleration, MaxSpeed;
   int VLength;
   double CurrentSpeed;
   int CartesianPosition[2];
   int Timer;
   int entryPoint;
   int exitPoint;
   Position CurrentPosition, PreviousPosition;
   vector<int> Path;

};

#endif