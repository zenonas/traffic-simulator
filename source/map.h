/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 23/2/2013
File: map.h
Description: This file includes the definition for the map class.

Copyright (c) King's College London
*/
#ifndef map_h
#define map_h

#include "roadNode.h"
#include <DLList.h>
# include <vector>
using namespace std;

class map
{
public:
   map();   
   ~map();
 
   void ReadXMLFile();
   void ConstructMap();
vector<DChain<int> > AllPaths; 

private:
   roadNode Roads[];
};

#endif