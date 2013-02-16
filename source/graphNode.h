/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: graphNode.h
Description: This file includes the definition for the graphNode class.

Copyright (c) King's College London
*/

#include "graphNode.cc"
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

private:
   int CartesianX, CartesianY;
   int Type;
};