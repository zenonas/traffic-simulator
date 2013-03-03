/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 2/3/2013
File: generator.cc
Description: This file specifies the car generator thead of the system. Please treat as a main file and avoid appending code here but rather include any classes you want to use.
Copyright (c) King's College London

*/

#include "th_structs.h"
#include "vehicle.h"
using namespace std;


void *generator(void *arguments)
{  
   struct thread_arguments *thread_args;
   thread_args = (struct thread_arguments *)arguments;
   
  // cout << "Generator Thread with id : " << "1" << "  is created" << endl;
   srand(time(NULL));

  while(!thread_args->finished) {

  	/*

  		STEP: 1 GET RATIOS
  		(NO OF VEHICLES, DRIVER TYPE RATIO, VEHICLE TYPE RATIO)
  		- USING DIRECTLY THE STRUCT VALUES
  	*/

  	/*

  		STEP 2 GET NUMBER OF VEHICLES/H NEEDED
		BASED ON THIS DECIDE HOW MANY VEHICLES NEED TO BE CREATE IN THIS ROUND
	*/
		int actual_no_to_create = rand() % thread_args->max_no_vehicles + 1;
		if (actual_no_to_create < 10) actual_no_to_create = 10; //maybe revise
		vehicle* temp_array[actual_no_to_create];
		//cout << "I SHALL CREATE: " << actual_no_to_create << endl;
	/*	
		STEP 3 DECIDE BASED RATIOS HOW MANY OF EACH VEHICLE TYPE YOU WILL CREATE
		STEP 4 CREATE THE VEHICLES AND STORE IN AN TEMP ARRAY OF OBJECTS
	*/
		vector<roadNode *> roads;
		roads= thread_args->mymap.getunfRoads();
		for (int z=0; z<actual_no_to_create;z++) temp_array[z] = NULL; //initalize array to null pointers
		for (int i=0; i<actual_no_to_create;i++) {
			int entryP= rand() % roads.size() +1 ;
			int exitP= rand() % roads.size() + 1;
			temp_array[i] = new vehicle(i, entryP, exitP, thread_args->mymap);
			int type_no = rand() % 100 + 1;
			if (type_no <= thread_args->vehicle_ratios[0]*100) {
				temp_array[i]->setType(0); // car
			} else if ((type_no > thread_args->vehicle_ratios[0]*100) && (type_no <= ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) ) {
				temp_array[i]->setType(1); //bus
			} else if (type_no > ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) {
				temp_array[i]->setType(2);
			}
		}
		for (int y=0; y<actual_no_to_create; y++) {
			int driver_type = rand() % 100 + 1;
			if (driver_type <= thread_args->driver_ratios[0]*100) {
				temp_array[y]->setDriverType(0); // normal
			} else if ((driver_type > thread_args->driver_ratios[0]*100) && (driver_type <= ((thread_args->driver_ratios[0]*100) + (thread_args->driver_ratios[1]*100))) ) {
				temp_array[y]->setDriverType(1); // cautious
			} else if (driver_type > ((thread_args->driver_ratios[0]*100) + (thread_args->driver_ratios[1]*100))) {
				temp_array[y]->setDriverType(2); //aggressive
			}
		}
	/*
		STEP 5 PICK VEHICLES AT RANDOM AND PUSH IN QUEUE
	*/
		int curr_vehicles = actual_no_to_create;
		//for (int p=0; p<actual_no_to_create; p++) cout << "IN THREAD: " << temp_array[p]->vehi_id << endl;
		while (curr_vehicles > 0) {
			int rand_pick = rand() % curr_vehicles;
			thread_args->VWaitingQ.push(temp_array[rand_pick]);
			for (int j=rand_pick; j<=curr_vehicles-1; j++) {	
				temp_array[j]=temp_array[j+1];
				temp_array[j+1] = NULL;
			}
			curr_vehicles--;
		}	
	/* STEP 7: WAIT FOR THE NEXT ROUND DEPENDING ON THE SLEEP TIMER */

		sleep(thread_args->sleep_time);



  }
   pthread_exit(NULL);
}
