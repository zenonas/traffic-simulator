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
vehicle *v1 = new vehicle(0,2,3,thread_args->mymap);
vehicle *v2 = new vehicle(1,1,3,thread_args->mymap);
v1->setDriverType(0);
v1->setType(1);
v2->setDriverType(0);
v2->setType(0);
//thread_args->VWaitingQ.push(v1);
thread_args->VWaitingQ.push(v2);

vehicle *v3 = new vehicle(2,3,2,thread_args->mymap);
vehicle *v4 = new vehicle(3,6,3,thread_args->mymap);
v3->setDriverType(0);
v3->setType(0);
v4->setDriverType(0);
v4->setType(0);
//thread_args->VWaitingQ.push(v3);
//thread_args->VWaitingQ.push(v4);

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

  		while(!entryQueues[k].empty() && maxe < 2) { //this will never be easily empty need to have && carfits() here
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
   for(int q=0; q<thread_args->vehiclesInEngine.size(); q++){
      int result;
      int distance=0;
      int type=0;
      void *obstacle;
      obstacle = nextObstacle(thread_args->vehiclesInEngine[q], distance, type, thread_args); 

      // if vehicle check the distance. If less than the distance that you can cover then reduce speed
      if (type==1)
      {
         if (distance < (thread_args->vehiclesInEngine[q]->getMaxSpeed()*thread_args->sleep_time))
            {             
              result = accelerate(thread_args->vehiclesInEngine[q], obstacle, -1, distance, thread_args);        
          } else
           result = accelerate(thread_args->vehiclesInEngine[q], obstacle, 1, distance, thread_args);
      }
      // if traffic lights then reduce to 0 speed
      else if (type==2){
          float remain = (thread_args->vehiclesInEngine[q]->getMaxSpeed() / thread_args->vehiclesInEngine[q]->getAcceleration());
          float d = thread_args->vehiclesInEngine[q]->getMaxSpeed()*remain + (thread_args->vehiclesInEngine[q]->getAcceleration()*remain*remain) / 2;
          if (distance < remain*thread_args->vehiclesInEngine[q]->getMaxSpeed()*thread_args->sleep_time + d)
              {
                result = accelerate(thread_args->vehiclesInEngine[q], obstacle, 0, distance, thread_args);                
              } 
          else
             result = accelerate(thread_args->vehiclesInEngine[q], obstacle, 1, distance, thread_args);
      }
      //move with the maximum possible speed
      else
        result = accelerate(thread_args->vehiclesInEngine[q], obstacle, 1, distance, thread_args);
      
      //vehicle out of map

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

}

   pthread_exit(NULL);
   
}
