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
   struct thread_arguments *thread_args;
   thread_args = (struct thread_arguments *)arguments;

   vector<vector <vehicle *> > entryQueues;
   for (int i=0; i<thread_args->mymap.entryGraphNodes.size(); i++) {
   	vector<vehicle *> currentQueue;
   	entryQueues.push_back(currentQueue);
   }

while (!thread_args->finished && thread_args->mymap.created == true) {
/*
	while(!thread_args->VWaitingQ.empty()) {
	 	vehicle *currentV = thread_args->VWaitingQ.front();
	 	
	 	int queueToBe = currentV->getEntryPoint();
	 	entryQueues[queueToBe].push_back(currentV);
	 		for(int k=0; k<entryQueues.size(); k++)
				for(int l=0; l<entryQueues[k].size(); l++) {
			//	cout << "THIS IS IT:" << entryQueues[k][l]->getEntryPoint() << endl;
	 	}
		//STEP 1: CALL THE SPLIT TO ENTRY POINT QUEUES FUNCTION

		//STEP 2: 
	
	 	thread_args->VWaitingQ.pop();
	}

*/
	sleep(thread_args->sleep_time);
}
   pthread_exit(NULL);
}
