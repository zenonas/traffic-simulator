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
#include <math.h>

using namespace rapidxml;
using namespace std;

#define PI 3.14159265

map::map(){
	ReadXMLFile();
	findConnectedRoadNodes();
	findAllPaths();
	findTrafficLights();
	created = true;
}

map::~map(){
 
}


void map::ReadXMLFile()
{
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("xmlfile2.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Map");
	// Iterate over the brewerys
	int j=0;
	vector<int> entryP;

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
				for (xml_node<> * timer_node = node_node->first_node("Timer"); timer_node; timer_node =timer_node->next_sibling("Timer"))
				{ 
					newgraphNodeB.setTimer(atoi(timer_node->value()));
				}
			}	
			else
			{
				for (xml_node<> * type_node = node_node->first_node("Type"); type_node; type_node =type_node->next_sibling("Type"))
				{ 
					newgraphNodeA.setType(atoi(type_node->value())); 
				}	
				for (xml_node<> * timer_node = node_node->first_node("Timer"); timer_node; timer_node =timer_node->next_sibling("Timer"))
				{ 
					newgraphNodeA.setTimer(atoi(timer_node->value()));
				}
			}
			i++;
				

			newgraphNodeA.setRoad(j+1);
			newgraphNodeB.setRoad(j+1);
			newroadNode.setgraphNodeA(newgraphNodeA);
			newroadNode.setgraphNodeB(newgraphNodeB);
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
		
		if (entryGraphNodes.size() == 0) {
			if (unfRoads[i].getgraphNodeA().getType() == 1) entryGraphNodes.push_back(unfRoads[i].getgraphNodeA());
			if (unfRoads[i].getgraphNodeB().getType() == 1) entryGraphNodes.push_back(unfRoads[i].getgraphNodeB());
		} 
		else {
			int flagA=0;
			int flagB=0;
		for (int zz=0; zz<entryGraphNodes.size(); zz++) {
			if (unfRoads[i].getgraphNodeA().getType() == 1)
				if (unfRoads[i].getgraphNodeA().getCartesianX() == entryGraphNodes[zz].getCartesianX() && unfRoads[i].getgraphNodeA().getCartesianY() == entryGraphNodes[zz].getCartesianY()) 
					flagA=1;
			if (unfRoads[i].getgraphNodeB().getType() == 1)
				if (unfRoads[i].getgraphNodeB().getCartesianX() == entryGraphNodes[zz].getCartesianX() && unfRoads[i].getgraphNodeB().getCartesianY() == entryGraphNodes[zz].getCartesianY())
					flagB=1;
		}
			if (flagA == 0 && unfRoads[i].getgraphNodeA().getType() == 1) entryGraphNodes.push_back(unfRoads[i].getgraphNodeA());
			if (flagB == 0 && unfRoads[i].getgraphNodeB().getType() == 1) entryGraphNodes.push_back(unfRoads[i].getgraphNodeB());
 		}
 	}
 
}

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
			temp.clear();
		if (i != j) { //so that we don't match the same roadNodes
			if ((graphNodeATestFirst.getCartesianX() == graphNodeAMatcher.getCartesianX() && graphNodeATestFirst.getCartesianY() == graphNodeAMatcher.getCartesianY())) 
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}
			else if ((graphNodeATestFirst.getCartesianX() == graphNodeBMatcher.getCartesianX() && graphNodeATestFirst.getCartesianY() == graphNodeBMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}			
			else if ((graphNodeBTestFirst.getCartesianX() == graphNodeBMatcher.getCartesianX() && graphNodeBTestFirst.getCartesianY() == graphNodeBMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}			
			else if ((graphNodeBTestFirst.getCartesianX() == graphNodeAMatcher.getCartesianX() && graphNodeBTestFirst.getCartesianY() == graphNodeAMatcher.getCartesianY()))
			{
				temp.push_back(unfRoads[i].getId());
				temp.push_back(unfRoads[j].getId());
				array.push_back( temp);
			}
			
		}	
	}
}

}

//find all paths
void map::findAllPaths (){
	allPaths.clear();
	vector<int> initial;
	//cout << "Find all possible paths...\n";
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
	//cout << "Print all possible paths for every entry roadNode...\n";
	for(int k=0; k<allPaths.size(); k++){
		cout << k << ": ";
		for(int l=0; l<allPaths[k].size(); l++){
			cout << allPaths[k][l] << " ";
		}
		length=0;
		speed=0;
	}
}


//get us input two roadNodes and returns 1 if they make turn and 0 if no.
//if the two roadNodes are not connected then return -1;
int map::checkTurn(int roadNode1Id, int roadNode2Id){
	for (int i=0; i<unfRoads.size(); i++)
		if (unfRoads[i].getId() == roadNode1Id)
			for (int j=0; j<unfRoads.size(); j++)
				if (unfRoads[j].getId() == roadNode2Id){
					graphNode A1 = unfRoads[i].getgraphNodeA();
					graphNode B1 = unfRoads[i].getgraphNodeB();
					graphNode A2 = unfRoads[j].getgraphNodeA();
					graphNode B2 = unfRoads[j].getgraphNodeB();
					if ((A1.getCartesianX() == A2.getCartesianX() && A1.getCartesianY() == A2.getCartesianY())) 
					{			
						float deltaY = (B2.getCartesianY() - B1.getCartesianY());
						float deltaX = (B2.getCartesianX() - B1.getCartesianX());
						int len1 = unfRoads[i].getLength();
						int len2 = unfRoads[j].getLength();
						int len3 = sqrt(deltaY*deltaY+deltaX*deltaX);
						int result = (len1*len1 + len2*len2 - len3*len3 ) / (2*len1*len2);
						if (result == -1)
						{
							return 0;
						}
						else {
							return 1;
						}
					}
					if ((A1.getCartesianX() == B2.getCartesianX() && A1.getCartesianY() == B2.getCartesianY()))
					{
						float deltaY = (A2.getCartesianY() - B1.getCartesianY());
						float deltaX = (A2.getCartesianX() - B1.getCartesianX());
						int len1 = unfRoads[i].getLength();
						int len2 = unfRoads[j].getLength();
						int len3 = sqrt(deltaY*deltaY+deltaX*deltaX);
						int result = (len1*len1 + len2*len2 - len3*len3 ) / (2*len1*len2);
						if (result == -1)
						{
							return 0;
						}
						else {
							return 1;
						}	
					}			
					if ((B1.getCartesianX() == B2.getCartesianX() && B1.getCartesianY() == B2.getCartesianY()))
					{
						float deltaY = (A2.getCartesianY() - A1.getCartesianY());
						float deltaX = (A2.getCartesianX() - A1.getCartesianX());
						int len1 = unfRoads[i].getLength();
						int len2 = unfRoads[j].getLength();
						int len3 = sqrt(deltaY*deltaY+deltaX*deltaX);
						int result = (len1*len1 + len2*len2 - len3*len3 ) / (2*len1*len2);
						if (result == -1)
						{
							return 0;
						}
						else {
							return 1;
						}
					}			
					if ((B1.getCartesianX() == A2.getCartesianX() && B1.getCartesianY() == A2.getCartesianY()))
					{
						float deltaY = abs(B2.getCartesianY() - A1.getCartesianY());
						float deltaX = abs(B2.getCartesianX() - A1.getCartesianX());
						int len1 = unfRoads[i].getLength();
						int len2 = unfRoads[j].getLength();
						int len3 = sqrt(deltaY*deltaY+deltaX*deltaX);
						int result = (len1*len1 + len2*len2 - len3*len3 ) / (2*len1*len2);
						//when -1 is straight
						if (result == -1)
						{
							return 0;
						}
						else {
							return 1;
						}
					}
					else {
						return 0;
					}
				}
}


//return vector that contains allPaths
vector<vector<int> > map::getAllPaths (){
	return allPaths;
}

vector<roadNode> map::getunfRoads(){
	return unfRoads;
}

void map::adjustTLlane(trafficLight *tlA, trafficLight *tlB){
	if (tlA->getCartesianX() > tlB->getCartesianX()) {
		tlA->setLane(0);
		tlB->setLane(1);
	} else if (tlA->getCartesianX() < tlB->getCartesianX()) {
		tlA->setLane(1);
		tlB->setLane(0);
	} else if (tlA->getCartesianY() > tlB->getCartesianY()) {
		tlA->setLane(0);
		tlB->setLane(1);
	} else if (tlA->getCartesianY() < tlB->getCartesianY()) {
		tlA->setLane(1);
		tlB->setLane(0);
	}
}

void map::findTrafficLights(){
	graphNode a;
	graphNode b;
	for (int i=0; i<unfRoads.size(); i++)
	{
		a = unfRoads[i].getgraphNodeA();
		b = unfRoads[i].getgraphNodeB();
		int count = 0;
		trafficLight *newTrafficLightA;
		trafficLight *newTrafficLightB;
		if(a.getType()==2) {
			newTrafficLightA = new trafficLight();
			newTrafficLightA->setCartesianX(a.getCartesianX());
			newTrafficLightA->setCartesianY(a.getCartesianY());
			newTrafficLightA->setTimer(a.getTimer());
			newTrafficLightA->setPos(getroadNode(unfRoads[i].getId()));
			trafficlights.push_back(newTrafficLightA);
			count++;
		}
		if(b.getType()==2) {
			newTrafficLightB = new trafficLight();
			newTrafficLightB->setCartesianX(b.getCartesianX());
			newTrafficLightB->setCartesianY(b.getCartesianY());
			newTrafficLightB->setTimer(b.getTimer());
			newTrafficLightB->setPos(getroadNode(unfRoads[i].getId()));
			trafficlights.push_back(newTrafficLightB);
			count++;
		}
		if (count == 2) {
			adjustTLlane(newTrafficLightA,newTrafficLightB);
		}
	}
}

roadNode *map::getroadNode(int id) {
	for (int i=0; i<unfRoads.size(); i++) {
		if (unfRoads[i].getId() == id) {
			return &unfRoads[i];
		}
	}
}


