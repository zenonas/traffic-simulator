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

   vector<vector <vehicle *> > entryQueues;
   for (int i=0; i<thread_args->mymap.entryGraphNodes.size(); i++) {
   	vector<vehicle *> currentQueue;
   	entryQueues.push_back(currentQueue);
   }

while (!thread_args->finished && thread_args->mymap.created == true) {
	int max_entries = 0;
	while(!thread_args->VWaitingQ.empty() && max_entries < thread_args->max_no_vehicles) {
	 	vehicle *currentV = thread_args->VWaitingQ.front();
	 	
	 	int queueToBe = currentV->getEntryPoint();
	 	entryQueues[queueToBe-1].push_back(currentV);
	 		/*
	 		for(int k=0; k<entryQueues.size(); k++)
				for(int l=0; l<entryQueues[k].size(); l++) {
					cout << "THIS IS IT:" << entryQueues[k][l]->getEntryPoint() << endl;
	 	}
	 	*/

		//STEP 1: CALL THE SPLIT TO ENTRY POINT QUEUES FUNCTION

		//STEP 2: 
	
	 	thread_args->VWaitingQ.pop();

	 	max_entries++;
	}
	/*
	for(int k=0; k<entryQueues.size(); k++)
		for(int l=0; l<entryQueues[k].size(); l++) 
			cout << "CAR WITH ID:" << entryQueues[k][l]->vehi_id << " will enter queue: " << entryQueues[k][l]->getEntryPoint() << endl;
*/


	sleep(thread_args->sleep_time);
	cout << "testing" << endl;
}
   pthread_exit(NULL);
}
