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
#include <iostream>

using namespace std;

class trafficLight
{
public:
 
   trafficLight(); 
     
   ~trafficLight();
   void Wait();
   void setState();
   int getState();

private:
  


   int Timer;
};

#endif
