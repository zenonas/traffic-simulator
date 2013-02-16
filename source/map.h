/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: map.h
Description: This file includes the definition for the map class.

Copyright (c) King's College London
*/
#ifndef map_h
#define map_h

using namespace std;

class map
{
public:
   map();   
   ~map();
  
   void setMaxSpeed(int x);
   int getMaxSpeed();
   void ReadXMLFile();
   void ConstructMap();

private:
   roadNode Roads[];
   int MaxSpeed;
};

#endif