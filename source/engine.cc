/* Traffic Simulation System
Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/3/2013
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
  entryQueues.resize(thread_args->mymap.getunfRoads().size());
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
  		  if (thread_args->vehiclesInEngine.size() == 0) { //first time car definitely fits
  			   thread_args->vehiclesInEngine.push_back(entryQueues[k].front());
  				 entryQueues[k].pop();
  				 //updatePosition(vehiclesInEngine.back());
  			} 
        else if (carFits(entryQueues[k].front(), thread_args->vehiclesInEngine, thread_args->mymap.getunfRoads(), thread_args)) {
            thread_args->vehiclesInEngine.push_back(entryQueues[k].front());
				    entryQueues[k].pop();
				    //updatePosition(vehiclesInEngine.back());
				}
			
			maxe++;
		  }
	 }

   vector<roadNode> roads = thread_args->mymap.getunfRoads();
   // test code for vehicle accelerate
   for(int q=0; q<thread_args->vehiclesInEngine.size(); q++){
      vector<int> myPaths = thread_args->vehiclesInEngine[q]->getPath();
      int result;
      result = accelerate(thread_args->vehiclesInEngine[q],thread_args->vehiclesInEngine[q], 1, thread_args);
      if (result == 0) {
        delete thread_args->vehiclesInEngine[q];
        thread_args->vehiclesInEngine.erase(thread_args->vehiclesInEngine.begin()+q);
        thread_args->simstats.addRemVehi();
      }
   }    
   // test code for vehicle accelerate ends
   
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
  if (thread_args->mymap.trafficlights[i]->getTimer()!=0) {
    if((thread_args->CurrentTimer % thread_args->mymap.trafficlights[i]->getTimer())== 0 && thread_args->CurrentTimer !=0) {
		  if (thread_args->mymap.trafficlights[i]->getState() == 1) {
          thread_args->mymap.trafficlights[i]->setState(0);
          //thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()/2);
		  } else {
          thread_args->mymap.trafficlights[i]->setState(1);
          //thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()*2);
		  }
    } 
  }
  //cout << "TESTING CURRENT LIGHT: " << i << " STATE: " <<thread_args->mymap.trafficlights[i].getState() << endl;
}
  
/* TEST CODE FOR nextObstacle()
  int dist = 0;
  int retType = 0;
  void *obs = nextObstacle(v2,dist,retType,thread_args);  
  
  if (retType == 1) {
    vehicle *v = (vehicle *)obs;
  } else if (retType == 2) {
    trafficLight *tl = (trafficLight *)obs;
  }
Test code ends */
  thread_args->tick_count++;
  thread_args->CurrentTimer++;
  // Update time in engine for every single vehicle
  for(int k=0; k<thread_args->vehiclesInEngine.size(); k++){
    int newtimer = thread_args->vehiclesInEngine[k]->getTimer() + 1;
    thread_args->vehiclesInEngine[k]->setTimer(newtimer);
  }
  thread_args->simstats.CaptureStatistics(&thread_args->mymap, thread_args->vehiclesInEngine);
  sleep(1);

}

   pthread_exit(NULL);
   
}
