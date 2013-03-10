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
#include "statistics.h"



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
   // test code for vehicle accelerate
   for(int q=0; q<vehiclesInEngine.size(); q++){
      vector<int> myPaths = vehiclesInEngine[q]->getPath();
      //cout << "MY PATH IS : ";
      for (int h=0; h<myPaths.size(); h++) {
         //cout << myPaths[h] << " ";
      }
      //cout << endl;
      int result = accelerate(vehiclesInEngine[q], 1, thread_args);
      //result = accelerate(vehiclesInEngine[q], -1, thread_args);
      //cout << "I ACCELERATED ONCE MY NEW POSITION IS: " << vehiclesInEngine[q]->getCurrentPosition().roadNodeID << " at position " << vehiclesInEngine[q]->getCurrentPosition().p << endl;
      if (result == 0) {
         //cout << "vgika apto xarti" << endl;
         vehiclesInEngine.erase(vehiclesInEngine.begin()+q);
      }      
   }    
   // test code for vehicle accelerate ends


   //vehiclesInEngine

   for(int i=0; i<vehiclesInEngine.size(); i++){    
      vector<int> vehicle1Path = vehiclesInEngine[i]->getPath();
      for (int k=0; k<vehiclesInEngine.size(); k++){
         vector<int> vehicle2Path = vehiclesInEngine[k]->getPath();
         int flag=0;
         for (int p=0; p<vehicle1Path.size(); p++){
            for (int q=0; q<vehicle2Path.size(); q++){                            
               if (vehicle1Path[p]==vehicle2Path[q] && i!=k && flag==0){
                  ///check current positions and calculate if affecting
                  Position positionVehicle1;
                  Position positionVehicle2;
                  positionVehicle1= vehiclesInEngine[i]->getCurrentPosition();
                  positionVehicle2= vehiclesInEngine[k]->getCurrentPosition();
                  int speedVehicle1 = vehiclesInEngine[i]->getCurrentSpeed();
                  int speedVehicle2 = vehiclesInEngine[k]->getCurrentSpeed();
                  int driver1 = vehiclesInEngine[i]->getDriverType();
                  int driver2 = vehiclesInEngine[k]->getDriverType();
                 

                 // cout << " CAR: " << i << " and " << k << endl;
                   //  Do the appopriate checks in order to update position of car i

                  
                  flag=1;
               }
            }
         }
      }
   } 
   



    // same path handling
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

thread_args->tick_count++;
thread_args->CurrentTimer++;

// Update time in engine for every single vehicle
for(int k=0; k<vehiclesInEngine.size(); k++){
  int newtimer = vehiclesInEngine[k]->getTimer() + 1;
  vehiclesInEngine[k]->setTimer(newtimer);
}


thread_args->simstats.CaptureStatistics(thread_args->mymap, vehiclesInEngine);
/*cout << "---- STATISTICS!!! ----" << endl;
cout << "Vehicles in Engine: " << S.getTotalVehicles() <<endl;
cout << "AvSpeed: " << S.getAvSpeed() <<endl;
cout << "AvTimeinEngine: " << S.getAvTimeinEngine() <<endl;
cout << "MostCommonExitP: " << S.getMostCommonExitP() <<endl;
cout << "MostCommonEntryP: " << S.getMostCommonEntryP() <<endl;

cout << "Vehicles: " << S.getVehicleTypeNum()[0] << " " << S.getVehicleTypeNum()[1] << " " << S.getVehicleTypeNum()[2] << endl;

cout << "Drivers: " << S.getDriverTypeNum()[0] << " " << S.getDriverTypeNum()[1] << " " << S.getDriverTypeNum()[2] << endl;

cout << "-----------------------" << endl; */

  sleep(thread_args->sleep_time);
}


   pthread_exit(NULL);
   
}
