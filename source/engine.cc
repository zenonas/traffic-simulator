/* Traffic Simulation System
Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 17/3/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/
#include "th_structs.h"
#include "map.h"
#include "carMoves.h"
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

  vehicle *v1 = new vehicle(0,3,1,thread_args->mymap);
  vehicle *v2 = new vehicle(1,1,3,thread_args->mymap);
  vehicle *v3 = new vehicle(2,1,3,thread_args->mymap);
  v1->setType(0); 
  v2->setType(0);
  v3->setType(0);
  v1->setDriverType(0);
  v2->setDriverType(1); 
  v3->setDriverType(2);
  thread_args->VWaitingQ.push(v1); 
  thread_args->VWaitingQ.push(v2);

   
  //vehicle *v3 = new vehicle(0,2,1,thread-args->mymap);
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

  		while(!entryQueues[k].empty() && maxe < 1) { //this will never be easily empty need to have && carfits() here
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
    int re;
    vector<roadNode> roads = thread_args->mymap.getunfRoads();

    if (thread_args->tick_count == 5) {
      thread_args->vehiclesInEngine.push_back(v3);
      vehicle *tempv3 = thread_args->vehiclesInEngine[2];
      vehicle *tempv2 = thread_args->vehiclesInEngine[1];
      vehicle *tempv1 = thread_args->vehiclesInEngine[0];
      thread_args->vehiclesInEngine[0] = tempv3;
      thread_args->vehiclesInEngine[2] = tempv2;
      thread_args->vehiclesInEngine[1] = tempv1;
    }

    for(int q=0; q<thread_args->vehiclesInEngine.size(); q++){
      if (!thread_args->vehiclesInEngine[q]->updated){
        re = DriverDecision(thread_args->vehiclesInEngine[q],thread_args);
      }

    }    

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
  

  thread_args->tick_count++;
  thread_args->CurrentTimer++;
  // Update time in engine for every single vehicle
  for(int k=0; k<thread_args->vehiclesInEngine.size(); k++){
    int newtimer = thread_args->vehiclesInEngine[k]->getTimer() + 1;
    thread_args->vehiclesInEngine[k]->setTimer(newtimer);
  }
  thread_args->simstats.CaptureStatistics(&thread_args->mymap, thread_args->vehiclesInEngine);
  while (thread_args->sim_paused) {
    sleep(1);
  }
  sleep(1);
   for(int yy=0; yy<thread_args->vehiclesInEngine.size(); yy++)
        thread_args->vehiclesInEngine[yy]->updated = false;

}

   pthread_exit(NULL);
   
}
