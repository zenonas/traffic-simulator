/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 2/3/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/
#include "th_structs.h"
#include "map.h"
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
				// DELETE THE NON COMMENTED LINES JUST FOR TESTS
				vehiclesInEngine.push_back(entryQueues[k].front());
				entryQueues[k].pop();
				/*if (carFits() == true) {
				vehiclesInEngine.push_back(entryQueues[k].front());
				entryQueues[k].pop();
				updatePosition(vehiclesInEngine.back());
				}*/
			}
			maxe++;
		}
	}
	//
	/*
	for(int k=0; k<entryQueues.size(); k++)
		for(int l=0; l<entryQueues[k].size(); l++) 
			cout << "CAR WITH ID:" << entryQueues[k][l]->vehi_id << " will enter queue: " << entryQueues[k][l]->getEntryPoint() << endl;
*/

   //STEP 3: for every car in the engine (vehiclesInEngine), check every other car
   //        and if they have part of same path do...
   for (int i=0; i<vehiclesInEngine.size(); i++){
      cout << "\nVehicle " << i+1 << ": ";
      vehiclesInEngine[i]->printPath();
   }
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


	sleep(thread_args->sleep_time);
	cout << thread_args->VWaitingQ.size() << " testing " << entryQueues.size() << " and " << entryQueues[0].size() << " and " << entryQueues[1].size() << " and " << entryQueues[2].size() << " and " << entryQueues[3].size() << endl;
	cout << "CURRENT CARS IN MAP: " << vehiclesInEngine.size() << endl;
}
   pthread_exit(NULL);
}
