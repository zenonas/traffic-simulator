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

#include "graphNode.h"
using namespace std;

class vehicle
{
public:
   vehicle();   
   ~vehicle();
   
   struct Position
    {
        graphNode x;
        graphNode y;
        int p;
    };
   
   void setType(int type);
   int getType();
   void setCurrentSpeed(int x);
   int getCurrentSpeed();
   void setDriverType(int type);
   int getDriverType();
   void setAcceleration(int x);
   int getAcceleration();
   void setCartesianPosition(int CartesianPosition[]);
   int getCartesianPosition();
   void setCurrentPosition(Position C);
   Position getCurrentPosition();
   void setPreviousPosition(Position C);
   Position getPreviousPosition();
   void calculatePath();
   roadNode getPath();

private:
   int Type, CurrentSpeed, DriverType, Acceleration;
   int CartesianPosition[2];
   Position CurrentPosition, PreviousPosition;
   roadNode Path[];
};

#endif