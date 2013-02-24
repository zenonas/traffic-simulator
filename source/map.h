/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 24/2/2013
File: map.h
Description: This file includes the definition for the map class.

Copyright (c) King's College London
*/
#ifndef map_h
#define map_h

#include "roadNode.h"
# include <vector>
using namespace std;

class map
{
public:
   map();   
   ~map();
 
   void ReadXMLFile();
   void ConstructMap();
   vector< vector<int> > allPaths;

private:
   roadNode Roads[];
   vector<roadNode> unfRoads;
};

#endif