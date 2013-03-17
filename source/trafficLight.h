/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: trafficLight.h
Description: This file includes the definition for the trafficLight class.

Copyright (c) King's College London
*/
#ifndef trafficLight_h
#define trafficLight_h

#include "position.h"
#include "roadNode.h"

using namespace std;

class trafficLight
{
public:
 
   trafficLight(); 
     
   ~trafficLight();
   void Wait();
   void setCartesianX(int x);
   int getCartesianX();
   void setCartesianY(int y);
   int getCartesianY();
   void setState(int state);
   int getState();
   void setTimer(int timer);
   int getTimer();
   void setPos(roadNode *roadnode);
   void setLane(int lane);
   Position getPos();

private:
  
	int CartesianX, CartesianY;  
	int Timer;
	int State;
   Position LightPos;

};

#endif
