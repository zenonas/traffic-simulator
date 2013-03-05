/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: graphNode.h
Description: This file includes the definition for the graphNode class.

Copyright (c) King's College London
*/
#ifndef graphNode_h
#define graphNode_h

#include "trafficLight.h"
#include <vector>
using namespace std;

class graphNode
{
public:
   graphNode();   
   ~graphNode();
   
   void setCartesianX(int x);
   int getCartesianX();
   void setCartesianY(int y);
   int getCartesianY();
   void setType(int type);
   int getType();
   void setTimer(int timer);
   int getTimer();
   void setTrafficLight(trafficLight* t);
   //trafficLight* getTrafficLight(); //???????

private:
   int CartesianX, CartesianY;
   int Timer;
   int Type; // 0: nothing 1: entry/exit point and traffic light 2: only traffic light
   //trafficLight will be null if not trafficLight
};

#endif
