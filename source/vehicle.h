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
#include "roadNode.h"
using namespace std;
struct Position
    {
        graphNode x;
        graphNode y;
        int p;
    };

class vehicle
{
public:
   vehicle(int id);   
   ~vehicle();
   
   void setType(int type);
   int getType();
   void setCurrentSpeed(int x);
   int getCurrentSpeed();
   void setDriverType(int type);
   int getDriverType();
   void setAcceleration(int x);
   int getAcceleration();
   void setCartesianPosition(int CartesianPosition[]);
   int* getCartesianPosition();
   void setCurrentPosition(Position C);
   Position getCurrentPosition();
   void setPreviousPosition(Position C);
   Position getPreviousPosition();
   void calculatePath();
   roadNode* getPath();

   int vehi_id;

private:
   int Type, CurrentSpeed, DriverType, Acceleration;
   int CartesianPosition[2];
   Position CurrentPosition, PreviousPosition;
   roadNode *Path[];
};

#endif