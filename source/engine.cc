/* Traffic Simulation System
Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/3/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/

#include "engine.h"

using namespace std;

void *engine(void *arguments)
{
  struct thread_arguments *thread_args;
  thread_args = (struct thread_arguments *)arguments;
	while (thread_args->sim_paused)
    sleep(1);
  sleep(5);
  srand(time(NULL));
  vector<queue <vehicle *> > entryQueues;
  entryQueues.resize(thread_args->mymap.getunfRoads().size());
  thread_args->CurrentTimer=0;
  for (int i=0; i<thread_args->mymap.entryGraphNodes.size(); i++) {
   	queue<vehicle *> currentQueue;
   	entryQueues.push_back(currentQueue);
  }

  while (!thread_args->finished && thread_args->mymap.created == true) {
  	//CARS TAKEN OFF THE WAITING QUEUE AND SPLIT INTO THE SEPARATE QUEUES
  	while(!thread_args->VWaitingQ.empty()) {
      
    	vehicle *currentV = thread_args->VWaitingQ.front();
  	 	int queueToBe = currentV->getEntryPoint();
  	 	entryQueues[queueToBe-1].push(currentV);
  	 	thread_args->VWaitingQ.pop();
    }

	//START HANDLING THE ENTRY QUEUES
  	for (int k=0; k<entryQueues.size(); k++) { //iterate through all the entry queues
     //
  	  if(!entryQueues[k].empty()) { //this will never be easily empty need to have && carfits() here
        if (thread_args->vehiclesInEngine.size() == 0) { //first time car definitely fits
  			   thread_args->vehiclesInEngine.push_back(entryQueues[k].front());
  				 entryQueues[k].pop();
  			} 
        else if (carFits(entryQueues[k].front(), thread_args->vehiclesInEngine, thread_args->mymap.getunfRoads(), thread_args)) {
            thread_args->vehiclesInEngine.push_back(entryQueues[k].front());
				    entryQueues[k].pop();
				}
		  }  
	 }



    int re;
    vector<roadNode> roads = thread_args->mymap.getunfRoads();
  
  for(int q=0; q<thread_args->vehiclesInEngine.size(); q++){
    if (!thread_args->vehiclesInEngine[q]->updated) {
      re = DriverDecision(thread_args->vehiclesInEngine[q],thread_args);
      if (re == -1) {
        delete thread_args->vehiclesInEngine[q];
        thread_args->vehiclesInEngine.erase(thread_args->vehiclesInEngine.begin()+q);
        thread_args->simstats.addRemVehi();        
      }
    }  
  }
  
  for (int cv=0; cv<thread_args->vehiclesInEngine.size(); cv++){
    if (thread_args->vehiclesInEngine[cv]->crashed && thread_args->vehiclesInEngine[cv]->crash_timer == 5) {
      delete thread_args->vehiclesInEngine[cv];
      thread_args->vehiclesInEngine.erase(thread_args->vehiclesInEngine.begin()+cv);
      thread_args->simstats.addCrashedVehicle();                
    }
  }
    //} 
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
