/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
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
#include "rapidxml.hpp"

 
using namespace rapidxml;
using namespace std;

map::map(){

}

map::~map(){

}

void map::setMaxSpeed(int x){
	MaxSpeed=x;
}

int map::getMaxSpeed(){
	return MaxSpeed;
}

void map::ReadXMLFile()
{
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
	for (xml_node<> * road_node = root_node->first_node("Road"); road_node; road_node =road_node->next_sibling("Road"))
	{
		 roadNode newroadNode;
		 graphNode newgraphNodeA;
		 graphNode newgraphNodeB;
		 
        printf("This is the road %s\n",road_node->first_attribute("name")->value());
        
		int i=0;	
        for (xml_node<> * node_node = road_node->first_node("Node"); node_node; node_node =node_node->next_sibling("Node"))
	    {  
             printf("This is node %s \n",node_node->first_attribute("name")->value());
             if (i%2==0)
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
              	
              	if(i%2==0)
              	{
				cout <<"XB="<<newgraphNodeA.getCartesianX()<<endl;
				cout<<"YB="<<newgraphNodeA.getCartesianY()<<endl;
				 for (xml_node<> * type_node = node_node->first_node("Type"); type_node; type_node =type_node->next_sibling("Type"))
				{ 
					newgraphNodeB.setType(atoi(type_node->value()));
					cout <<"Type="<<newgraphNodeB.getType()<<endl;
				}
				}	
				else
				{
				cout <<"XA="<<newgraphNodeB.getCartesianX()<<endl;
				cout<<"YA="<<newgraphNodeB.getCartesianY()<<endl;
				 for (xml_node<> * type_node = node_node->first_node("Type"); type_node; type_node =type_node->next_sibling("Type"))
				{ 
					newgraphNodeA.setType(atoi(type_node->value()));
					cout <<"Type="<<newgraphNodeA.getType()<<endl;
				}
				}
				
				
		    newroadNode.setgraphNodeA(newgraphNodeA);
	        newroadNode.setgraphNodeB(newgraphNodeB);
	      
       }
        for (xml_node<> * length= road_node->first_node("Length"); length; length=length->next_sibling()){
	       
	        newroadNode.setLength(atoi(length->value()));
	       cout <<"New Length="<<newroadNode.getLength()<<endl;}
	       
	          
	    
      cout<<endl;
	}
}

void map::ConstructMap(){
	ReadXMLFile();
}

