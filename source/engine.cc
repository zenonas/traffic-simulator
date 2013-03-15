/* Traffic Simulation System
Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 8/3/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/
#include "th_structs.h"
#include "map.h"
#include "carMoves.cc"
#include "roadNode.h"
#include "graphNode.h"
#include "statistics.h"
#include <vector>
#include <iostream>

using namespace std;

void *engine(void *arguments)
{
	sleep(5);
  struct thread_arguments *thread_args;
  thread_args = (struct thread_arguments *)arguments;
  vector<queue <vehicle *> > entryQueues;
  vector<vehicle *> vehiclesInEngine;
  thread_args->CurrentTimer=0;
 // thread_args->mymap.printAllPaths();
  for (int i=0; i<thread_args->mymap.entryGraphNodes.size(); i++) {
   	queue<vehicle *> currentQueue;
   	entryQueues.push_back(currentQueue);
  }

  vehicle *v1= new vehicle(1,7,1,thread_args->mymap);
  v1->setType(0);
  v1->setDriverType(0);
  vehicle *v2= new vehicle(0,6,3,thread_args->mymap);
  v2->setType(2);
  v2->setDriverType(2);
 
  cout <<endl;
  thread_args->VWaitingQ.push(v1);
  thread_args->VWaitingQ.push(v2);
  //thread_args->VWaitingQ.push(v3);
  while (!thread_args->finished && thread_args->mymap.created == true) {
  	int max_entries = 0;
  	//CARS TAKEN OFF THE WAITING QUEUE AND SPLIT INTO THE SEPARATE QUEUES
  	while(!thread_args->VWaitingQ.empty() && max_entries < thread_args->max_no_vehicles) {
    	vehicle *currentV = thread_args->VWaitingQ.front();
  	 	int queueToBe = currentV->getEntryPoint();
  	 	entryQueues[queueToBe-1].push(currentV);
  	 	thread_args->VWaitingQ.pop();
  	 	max_entries++;
    }
	//START HANDLING THE ENTRY QUEUES
  	int maxe = 0;
  	for (int k=0; k<entryQueues.size(); k++) { //iterate through all the entry queues
  		while(!entryQueues[k].empty() && maxe < 10) { //this will never be easily empty need to have && carfits() here
  		  if (vehiclesInEngine.size() == 0) { //first time car definitely fits
  			   vehiclesInEngine.push_back(entryQueues[k].front());
  				 entryQueues[k].pop();
  				 //updatePosition(vehiclesInEngine.back());
  			} 
        else if (carFits(entryQueues[k].front(), vehiclesInEngine, thread_args->mymap.getunfRoads(), thread_args)) {
				    vehiclesInEngine.push_back(entryQueues[k].front());
				    entryQueues[k].pop();
				    //updatePosition(vehiclesInEngine.back());
				}
			
			maxe++;
		}
	}

   vector<roadNode> roads = thread_args->mymap.getunfRoads();
   // test code for vehicle accelerate
  for(int q=0; q<vehiclesInEngine.size(); q++){
      vector<int> myPaths = vehiclesInEngine[q]->getPath();
     // cout << "\n\nMY PATH IS : ";
      for (int h=0; h<myPaths.size(); h++) {
         //cout << myPaths[h] << " ";
      }
      int result;
     //check every other vehicle
      for (int p=0; p<vehiclesInEngine.size(); p++)
        if (p!=q){
          //if they have same path
          if (checkVehicle(vehiclesInEngine[q],vehiclesInEngine[p]))
            {
              struct Position pos1;
              struct Position pos2;
              
              pos1 = vehiclesInEngine[q]->getCurrentPosition();
              pos2 = vehiclesInEngine[p]->getCurrentPosition();
              
              int speed1 = vehiclesInEngine[q]->getCurrentSpeed();
              int speed2 = vehiclesInEngine[p]->getCurrentSpeed();
              int length=1000;
              //if <0 then not in the map yet
              if (pos1.roadNodeID>0){
                //if the vehicles are in the same roadNode
                if (pos1.roadNodeID == pos2.roadNodeID){
                  //calculate their distance
                    if (pos2.p>pos1.p)
                      length = pos2.p - pos1.p;
                    else
                      length = 1000;
                }
                //if not in the same roadNode
               else {
                      for (int h=0; h<myPaths.size(); h++){
                        //find the roadnode for vehicle that I am checking
                          if (myPaths[h]==pos1.p)
                            //check if it is the next roadNode
                            if (pos2.roadNodeID==myPaths[h+1]){
                              length = pos2.p + (myPaths[h]-pos1.p);
                              break;
                            }
                            else length = 1000; 
                          }
                    }
                    //check if it can cover the distance in a tick
                if (length<speed2*thread_args->sleep_time){
                  //if yes then check others car speed and reduce speed to avoid crashing
                  if (speed2<speed1){
                    result = accelerate(vehiclesInEngine[q],vehiclesInEngine[p], -1, thread_args);
                   }
                  else
                  result = accelerate(vehiclesInEngine[q],vehiclesInEngine[p], 2, thread_args);
                }
                //can't cover the distance
                else{ 
                  result = accelerate(vehiclesInEngine[q],vehiclesInEngine[p], 2, thread_args);
                 }             
              }
              //not in the map yet
              else {
                result = accelerate(vehiclesInEngine[q],vehiclesInEngine[p], 2, thread_args);
               }
            }
          }
            else
            result = accelerate(vehiclesInEngine[q],vehiclesInEngine[p], 2, thread_args); 
      if (result == 0) {
         vehiclesInEngine.erase(vehiclesInEngine.begin()+q);
         vehicle *v1= new vehicle(3,1,2,thread_args->mymap);
         v1->setType(0);
         v1->setDriverType(0);
          thread_args->VWaitingQ.push(v1);
      }      
   }
    // check for intersections
   //we have to store them in an array and find a way to handle them
   //such as vehicles from different roadnodes and how to handle all together
   /*vector<roadNode> ROADS = thread_args->mymap.getunfRoads();
   for(int i=0; i<vehiclesInEngine.size(); i++){    
      vector<int> vehiclePath = vehiclesInEngine[i]->getPath();
      vector<int> intersection;
         for (int p=0; p<vehiclePath.size(); p++){
            for (int k=0; k<ROADS.size(); k++)
               if (ROADS[k].getId()==vehiclePath[p]){
                  graphNode A1 = ROADS[k].getgraphNodeA();
                  graphNode B1 = ROADS[k].getgraphNodeB();
                  int count = 1;
                  for (int s = 0; s < ROADS.size(); s++){
                     graphNode A2 = ROADS[s].getgraphNodeA();
                     graphNode B2 = ROADS[s].getgraphNodeB();
                     if (s!=k){
                        if ((A1.getCartesianX() == A2.getCartesianX() && A1.getCartesianY() == A2.getCartesianY()))                    
                           count++;                
                        if ((A1.getCartesianX() == B2.getCartesianX() && A1.getCartesianY() == B2.getCartesianY()))   
                           count++;
                        if ((B1.getCartesianX() == B2.getCartesianX() && B1.getCartesianY() == B2.getCartesianY()))     
                           count++;
                        if ((B1.getCartesianX() == A2.getCartesianX() && B1.getCartesianY() == A2.getCartesianY()))
                           count++;
                        if (count>2){
                           break;
                        }
                     }
                  }
                break;  
               }
         }
      }*/


  // traffic lights handling
  for(int i=0; i<thread_args->mymap.trafficlights.size(); i++) {
    if (thread_args->mymap.trafficlights[i].getTimer()!=0) {
      if((thread_args->CurrentTimer % thread_args->mymap.trafficlights[i].getTimer())== 0 && thread_args->CurrentTimer !=0) {
  		  if (thread_args->mymap.trafficlights[i].getState() == 1) {
            thread_args->mymap.trafficlights[i].setState(0);
            //thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()/2);
  		  } else {
            thread_args->mymap.trafficlights[i].setState(1);
            //thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()*2);
  		  }
      } 
    }
    //cout << "TESTING CURRENT LIGHT: " << i << " STATE: " <<thread_args->mymap.trafficlights[i].getState() << endl;
  }
  thread_args->tick_count++;
  thread_args->CurrentTimer++;
  // Update time in engine for every single vehicle
  for(int k=0; k<vehiclesInEngine.size(); k++){
    int newtimer = vehiclesInEngine[k]->getTimer() + 1;
    vehiclesInEngine[k]->setTimer(newtimer);
  }
  thread_args->simstats.CaptureStatistics(&thread_args->mymap, vehiclesInEngine);
  sleep(thread_args->sleep_time);
}

   pthread_exit(NULL);
   
}
