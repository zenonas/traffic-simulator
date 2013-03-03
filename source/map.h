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
 
   void constructMap();
   map returnMap();
   void printAllPaths();
   vector<vector<int> > getAllPaths();
   vector<roadNode> getunfRoads();
   vector<graphNode *> entryGraphNodes;
   bool created;

private:
   void ReadXMLFile();
   bool checkRoad(graphNode *);
   void findConnectedRoadNodes();
   void findAllPaths();
   void find_childs(vector<int> initial,int value,vector<vector<int> > array);

   vector<vector<int> > array;
   vector<roadNode> unfRoads;
   vector<vector<int> > allPaths;
};


#endif