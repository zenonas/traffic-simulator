/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: roadNode.h
Description: This file includes the definition for the roadNode class.

Copyright (c) King's College London
*/
#ifndef roadNode_h
#define roadNode_h

#include "graphNode.h"
using namespace std;

class roadNode
{
public:
   roadNode();   
   ~roadNode();
   
   void setgraphNodeA(graphNode a);
   graphNode getgraphNodeA();
   void setgraphNodeB(graphNode b);
   graphNode getgraphNodeB();
   void setLength(int l);
   int getLength();
   void setMaxSpeed(int x);
   int getMaxSpeed();
   void setId(int x);
   int getId();
   

private:
   int Length;
   int MaxSpeed;
   int Id;
   graphNode A,B;
};

#endif