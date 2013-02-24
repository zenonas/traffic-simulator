/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 24/2/2013
File: map.cc
Description: This file includes the implementation for the map class.

Copyright (c) King's College London
*/
#include "map.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <rapidxml.hpp>

using namespace rapidxml;
using namespace std;

map::map(){
	  
}

map::~map(){
 
}


void map::ReadXMLFile()
{
	for (int i = 0; i < 10; i++) {
    vector<int> onePath; // Create an empty row
    for (int j = 0; j < 20; j++) {
        onePath.push_back(i * j); // Add an element (column) to the row
    }
    allPaths.push_back(onePath); // Add the row to the main vector
}
	cout << "Parsing my road..." << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("xmlfile.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Map");
	// Iterate over the brewerys
	int j=0;
	int l=0;
	for (xml_node<> * road_node = root_node->first_node("Road"); road_node; road_node =road_node->next_sibling("Road"))
	{
		l++;
	}
	for (xml_node<> * road_node = root_node->first_node("Road"); road_node; road_node =road_node->next_sibling("Road"))
	{
		 roadNode newroadNode;
		 graphNode newgraphNodeA;
		 graphNode newgraphNodeB;

		int i=0;	

        for (xml_node<> * node_node = road_node->first_node("Node"); node_node; node_node =node_node->next_sibling("Node"))
	    {  
             if (i%2!=0)
			 {
				for (xml_node<> * point_node = node_node->first_node("Point"); point_node; point_node =point_node->next_sibling("Point"))
				{
					if (strcmp(point_node->first_attribute("name")->value(),"x")==0)
					{
						newgraphNodeB.setCartesianX(atoi(point_node->value()));
					}
					else if(strcmp(point_node->first_attribute("name")->value(),"y")==0)
						newgraphNodeB.setCartesianY(atoi(point_node->value()));
				}
						
			}
			else
			{
				for (xml_node<> * point_node = node_node->first_node("Point"); point_node; point_node =point_node->next_sibling("Point"))
				{
					if (strcmp(point_node->first_attribute("name")->value(),"x")==0)
					{
						newgraphNodeA.setCartesianX(atoi(point_node->value()));
					}
					else if(strcmp(point_node->first_attribute("name")->value(),"y")==0)
							newgraphNodeA.setCartesianY(atoi(point_node->value()));
				}
              
            }
              	i++;
              	
              	if(i%2!=0)
              	{
				 for (xml_node<> * type_node = node_node->first_node("Type"); type_node; type_node =type_node->next_sibling("Type"))
				{ 
					newgraphNodeB.setType(atoi(type_node->value()));
				}
				}	
				else
				{
				
				 for (xml_node<> * type_node = node_node->first_node("Type"); type_node; type_node =type_node->next_sibling("Type"))
				{ 
					newgraphNodeA.setType(atoi(type_node->value()));
				}	
				}			
				
		    newroadNode.setgraphNodeA(newgraphNodeA);
			newroadNode.setgraphNodeB(newgraphNodeB);
			
			graphNode newgraphNodeAnew;
			newgraphNodeAnew = newroadNode.getgraphNodeA();
	      
       }
        for (xml_node<> * length= road_node->first_node("Length"); length; length=length->next_sibling()){
	       newroadNode.setLength(atoi(length->value()));
		   }
    
	for (xml_node<> * maxSpeed= road_node->first_node("MaxSpeed"); maxSpeed; maxSpeed=maxSpeed->next_sibling()){
	       newroadNode.setMaxSpeed(atoi(maxSpeed->value()));
		   }
		  newroadNode.setId(j+1);
	unfRoads.push_back(newroadNode);
	j++;
	}
	
	for (int i=0; i<l; i++){
	graphNode newgraphNodeAa;
	graphNode newgraphNodeAb;
	newgraphNodeAa = unfRoads[i].getgraphNodeA();
//	cout<< "A(" << newgraphNodeAa.getCartesianX() << "," <<newgraphNodeAa.getCartesianY()<<") Type:"<<newgraphNodeAa.getType() <<"  -  ";
	newgraphNodeAb = unfRoads[i].getgraphNodeB();
//	cout<< "B(" << newgraphNodeAb.getCartesianX() << "," <<newgraphNodeAb.getCartesianY() << ") Type:"<<newgraphNodeAb.getType() << "\nL: " << arrayRoads[i].getLength() << " Speed: " << arrayRoads[i].getMaxSpeed();
	cout<< "B(" << newgraphNodeAb.getCartesianX() << "," <<newgraphNodeAb.getCartesianY() <<") Type:"<<newgraphNodeAb.getType() << " Id:"<< unfRoads[i].getId()<<" L: " << unfRoads[i].getLength() << " Speed: " << unfRoads[i].getMaxSpeed()<<endl;
	}
	ConstructMap();
}

void map::ConstructMap(){

for (int i=0; i<unfRoads.size(); i++){
	graphNode graphNodeATestFirst;
	graphNode graphNodeBTestFirst;
	graphNodeATestFirst = unfRoads[i].getgraphNodeA();
	graphNodeBTestFirst = unfRoads[i].getgraphNodeB();
	for (int j=0; i<unfRoads.size(); i++){
		graphNode graphNodeAMatcher;
		graphNode graphNodeBMatcher;
		graphNodeAMatcher = unfRoads[j].getgraphNodeA();
		graphNodeBMatcher = unfRoads[j].getgraphNodeB();
		if (i != j) { //so that we don't match the same roadNodes
			if ((graphNodeATestFirst.getCartesianX() == graphNodeAMatcher.getCartesianX() || graphNodeBTestFirst.getCartesianX() == graphNodeBMatcher.getCartesianX())) {
				//we know that the x matches
				if ((graphNodeATestFirst.getCartesianY() == graphNodeAMatcher.getCartesianY() || graphNodeBTestFirst.getCartesianY() == graphNodeBMatcher.getCartesianY())) {
				 /*we now know we have have the two edges connected
				HERE YOU NEED A VECTOR OR 2-DIMENSIONAL ARRAY
				TO STORE THE 2 MATCHING IDS
				FROM THAT HUGE TABLE WE WILL BUILD THE FILTERED PATHS IN THE allPaths vector i defined
				*/
					cout << "match: " << unfRoads[i].getId() << "with " << unfRoads[j].getId() << endl;
				}					
			}			
		}
			

		
			
		}	
	}
}


