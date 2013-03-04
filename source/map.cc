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
	ReadXMLFile();
	findConnectedRoadNodes();
	findAllPaths();
}

map::~map(){
 
}


void map::ReadXMLFile()
{
	cout << "Parsing my road..." << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("xmlfile3.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Map");
	// Iterate over the brewerys
	int j=0;

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
			i++;						
			newroadNode.setgraphNodeA(newgraphNodeA);
			newroadNode.setgraphNodeB(newgraphNodeB);

			graphNode newgraphNodeAnew;
			newgraphNodeAnew = newroadNode.getgraphNodeA();      
		}
		for (xml_node<> * length= road_node->first_node("Length"); length; length=length->next_sibling("Length")){
			newroadNode.setLength(atoi(length->value()));
		} 
		for (xml_node<> * maxSpeed= road_node->first_node("MaxSpeed"); maxSpeed; maxSpeed=maxSpeed->next_sibling("MaxSpeed")){
			newroadNode.setMaxSpeed(atoi(maxSpeed->value()));
		}
		newroadNode.setId(j+1);
		unfRoads.push_back(newroadNode);
		j++;
	}
	for (int i=0; i<unfRoads.size(); i++){
		cout << "MY A GRAPH NODE WITH ID: " << unfRoads[i].getId() << "HAS COORDS: " << unfRoads[i].getgraphNodeA().getCartesianX() << " AND: " << unfRoads[i].getgraphNodeA().getCartesianY() << " TYPE: " << unfRoads[i].getgraphNodeA().getType() << endl;
		cout << "MY B GRAPH NODE WITH ID: " << unfRoads[i].getId() << "HAS COORDS: " << unfRoads[i].getgraphNodeB().getCartesianX() << " AND: " << unfRoads[i].getgraphNodeB().getCartesianY() << " TYPE: " << unfRoads[i].getgraphNodeB().getType() << endl;
		for (int zz=0; zz<unfRoads.size(); zz++) {
			if (i != zz) {
				if (unfRoads[i].getgraphNodeA().getType() == 1)
					if (unfRoads[i].getgraphNodeA().getCartesianX() == unfRoads[zz].getgraphNodeA().getCartesianX() && unfRoads[i].getgraphNodeA().getCartesianY() == unfRoads[i].getgraphNodeA().getCartesianY()) 
						entryGraphNodes.push_back(unfRoads[i].getgraphNodeA());
				if (unfRoads[i].getgraphNodeB().getType() == 1)
					if (unfRoads[i].getgraphNodeB().getCartesianX() == unfRoads[zz].getgraphNodeB().getCartesianX() && unfRoads[i].getgraphNodeB().getCartesianY() == unfRoads[i].getgraphNodeB().getCartesianY()) 
						entryGraphNodes.push_back(unfRoads[i].getgraphNodeB());
			}
		}
	}
		for (int zz=0; zz<entryGraphNodes.size(); zz++){
		cout << "MY entry point is: " << entryGraphNodes[zz].getType() << endl;
	}
		cout << "TOTAL ENTRY POINTS: " << entryGraphNodes.size() << endl;
}
/*
bool map::checkRoad(vector<roadNodes *unfRoads> ){
	for (int i = 0; i<entryGraphNodes.size(); i++) {
		if ((g.getCartesianX() == entryGraphNodes[i].getCartesianX()) && (g.getCartesianY() == entryGraphNodes[i].getCartesianY())) {
			return false;
		}
	}

	return true;
}
*/
void map::findConnectedRoadNodes(){
	vector<int> temp;
	graphNode graphNodeATestFirst;
	graphNode graphNodeBTestFirst;
	graphNode graphNodeAMatcher;
	graphNode graphNodeBMatcher;
	for (int i=0; i<unfRoads.size(); i++){
		graphNodeATestFirst = unfRoads[i].getgraphNodeA();
		graphNodeBTestFirst = unfRoads[i].getgraphNodeB();
		for (int j=0; j<unfRoads.size(); j++){
			graphNodeAMatcher = unfRoads[j].getgraphNodeA();
			graphNodeBMatcher = unfRoads[j].getgraphNodeB();
		if (i != j) { //so that we don't match the same roadNodes
			if ((graphNodeATestFirst.getCartesianX() == graphNodeAMatcher.getCartesianX() && graphNodeATestFirst.getCartesianY() == graphNodeAMatcher.getCartesianY())) 
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}
			if ((graphNodeATestFirst.getCartesianX() == graphNodeBMatcher.getCartesianX() && graphNodeATestFirst.getCartesianY() == graphNodeBMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}			
			if ((graphNodeBTestFirst.getCartesianX() == graphNodeBMatcher.getCartesianX() && graphNodeBTestFirst.getCartesianY() == graphNodeBMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}			
			if ((graphNodeBTestFirst.getCartesianX() == graphNodeAMatcher.getCartesianX() && graphNodeBTestFirst.getCartesianY() == graphNodeAMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}
			temp.clear();
		}	
	}
}
//print our array with connected roadnodes
/*for(int k=0; k<array.size(); k++){
	for(int l=0; l<2; l++)
		cout << array[k][l] << " ";
cout << endl;
}*/
}

//find all paths
void map::findAllPaths (){
	allPaths.clear();
	vector<int> initial;
	cout << "Find all possible paths...\n";
	//call function that finds all possible paths
	for (int s=0; s<unfRoads.size(); s++){
		initial.push_back(unfRoads[s].getId());
		find_childs(initial,unfRoads[s].getId(),array);
		initial.clear();
	}
}
//find all connected roadNodes with 'value' and contruct a path
void map::find_childs(vector<int> initial, int value,vector<vector<int> > array){
	vector<int> childs;
	for(int k=0; k<array.size(); k++){
		if(array[k][0] == value){
			bool loop = false;
			for(int j=0; j<initial.size(); j++)
				if(initial[j]==array[k][1])
					loop = true;
                //prevent from going back
				if(!loop){
					childs.push_back(array[k][1]);
					initial.push_back(array[k][1]);
					find_childs(initial,array[k][1],array);
					initial.pop_back();
				}               
		}
	}
	if(childs.size()==0){
		allPaths.push_back(initial);
		return;
	}
}


//print all possible paths
void map::printAllPaths(){
	int length=0, speed=0;
	cout << "Print all possible paths for every entry roadNode...\n";
	for(int k=0; k<allPaths.size(); k++){
		cout << k << ": ";
		for(int l=0; l<allPaths[k].size(); l++){
			cout << allPaths[k][l] << " ";
			for (int i=0; i<unfRoads.size(); i++)
				if (unfRoads[i].getId() == allPaths[k][l])
					length = length + unfRoads[allPaths[k][l]-1].getLength();				
		}
		cout << "\t\tTotalLength:" << length << endl;
		length=0;
		speed=0;
	}
}

//return vector that contains allPaths
vector<vector<int> > map::getAllPaths (){
	return allPaths;
}

vector<roadNode> map::getunfRoads(){
	return unfRoads;
}