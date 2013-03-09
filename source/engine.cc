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
   for (int i=0; i<thread_args->mymap.entryGraphNodes.size(); i++) {
   	queue<vehicle *> currentQueue;
   	entryQueues.push_back(currentQueue);
   }

vehicle *v1= new vehicle(0,1,3,thread_args->mymap);
v1->setType(0);

vehicle *v2= new vehicle(1,2,3,thread_args->mymap);
v2->setType(0);
thread_args->VWaitingQ.push(v1);
thread_args->VWaitingQ.push(v2);
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
			} else {
				if (carFits(entryQueues[k].front(), vehiclesInEngine, thread_args->mymap.getunfRoads(), thread_args)) {
				  vehiclesInEngine.push_back(entryQueues[k].front());
				  entryQueues[k].pop();
				//updatePosition(vehiclesInEngine.back());
				}
			}
			maxe++;
		}
	}
   vector<roadNode> roads = thread_args->mymap.getunfRoads();
   // test code for vehicle accelerate
   for(int q=0; q<vehiclesInEngine.size(); q++){
      vector<int> myPaths = vehiclesInEngine[q]->getPath();
      cout << "MY PATH IS : ";
      for (int h=0; h<myPaths.size(); h++) {
         cout << myPaths[h] << " ";
      }
      int result;
      cout << endl;
      for (int p=0; p<vehiclesInEngine.size(); p++)
        if (p!=q)
          if (checkVehicle(vehiclesInEngine[q],vehiclesInEngine[p]))
            {
              struct Position pos1;
              struct Position pos2;
              
              pos1 = vehiclesInEngine[q]->getCurrentPosition();
              pos2 = vehiclesInEngine[p]->getCurrentPosition();
              
              int speed1 = vehiclesInEngine[q]->getCurrentSpeed();
              int speed2 = vehiclesInEngine[p]->getCurrentSpeed();
              int length;
              if (pos1.roadNodeID>0)
              {
                cout <<"\n\nVehicle ahead road car " <<q<<" at "<< pos1.roadNodeID << " l: "<<roads[pos1.roadNodeID-1].getLength()<<" pos: " << pos1.p << " road id: "<< pos2.roadNodeID<<" l: " <<roads[pos2.roadNodeID-1].getLength()<< " pos: " << pos2.p;
                if (pos1.roadNodeID == pos2.roadNodeID)
                length = pos2.p - pos1.p;
                else
                length = (roads[pos1.roadNodeID].getLength() - pos1.p) + pos2.p;
                cout << "Length: " << length;

                if (length<100){
                  result = moveVehicle(vehiclesInEngine[q], thread_args);
                cout << "I MOVED ONCE MY NEW POSITION IS: " << vehiclesInEngine[q]->getCurrentPosition().roadNodeID << " at position " << vehiclesInEngine[q]->getCurrentPosition().p << endl;
                }
                else
                 { 
                  result = accelerate(vehiclesInEngine[q], 20, thread_args);
                cout << "I ACCELERATED ONCE MY NEW POSITION IS: " << vehiclesInEngine[q]->getCurrentPosition().roadNodeID << " at position " << vehiclesInEngine[q]->getCurrentPosition().p << endl;
                  }
                if (result == 0) {
                  cout << "vgika apo to xarti" << endl;
                  vehiclesInEngine.erase(vehiclesInEngine.begin()+q);
                }
               break;
              }
            }
            else if (vehiclesInEngine[q]->getCurrentSpeed()<roads[vehiclesInEngine[q]->getCurrentPosition().roadNodeID].getMaxSpeed())
            {
              result = accelerate(vehiclesInEngine[q], 20, thread_args);
              cout << "I acc ONCE MY NEW POSITION IS: " << vehiclesInEngine[q]->getCurrentPosition().roadNodeID << " at position " << vehiclesInEngine[q]->getCurrentPosition().p << endl;
            }
            else
            {  
              result = moveVehicle(vehiclesInEngine[q], thread_args);
              cout << "I move ONCE MY NEW POSITION IS: " << vehiclesInEngine[q]->getCurrentPosition().roadNodeID << " at position " << vehiclesInEngine[q]->getCurrentPosition().p << endl;
            }
      if (result == 0) {
         cout << "vgika apo to xarti" << endl;
         vehiclesInEngine.erase(vehiclesInEngine.begin()+q);
      }      
   }    
   // test code for vehicle accelerate ends
  
    // intersection?
   vector<roadNode> ROADS = thread_args->mymap.getunfRoads();

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
      }


// traffic lights handling
for(int i=0; i<thread_args->mymap.trafficlights.size(); i++) {
  if (thread_args->mymap.trafficlights[i].getTimer()!=0) {
    if((thread_args->CurrentTimer % thread_args->mymap.trafficlights[i].getTimer())== 0 && thread_args->CurrentTimer !=0) {
		  if (thread_args->mymap.trafficlights[i].getState() == 1) {
          thread_args->mymap.trafficlights[i].setState(0);
          thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()/2);
		  } else {
          thread_args->mymap.trafficlights[i].setState(1);
          thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()*2);
		  }
    } 
  }
  //cout << "TESTING CURRENT LIGHT: " << i << " STATE: " <<thread_args->mymap.trafficlights[i].getState() << endl;
}
  thread_args->CurrentTimer++;
  sleep(thread_args->sleep_time);
}


   pthread_exit(NULL);
   
}
