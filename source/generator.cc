/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: generator.cc
Description: This file specifies the car generator thead of the system. Please treat as a main file and avoid appending code here but rather include any classes you want to use.
Copyright (c) King's College London

*/
#include "th_structs.h"

using namespace std;


void *generator(void *arguments)
{  
   struct gen_thread *thread_args;
   thread_args = (struct gen_thread *)arguments;
   
   cout << "Generator Thread with id : " << "1" << "  is created" << endl;
   srand(time(NULL));

  while(!thread_args->gen_finished) {

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
	/*
		STEP 3 DECIDE BASED RATIOS HOW MANY OF EACH VEHICLE TYPE YOU WILL CREATE
	*/
		for (int i=1; i<=actual_no_to_create;i++) {
		//	Vehicle new_vehicle;
			int type_no = rand() % 100 + 1;
			cout << "MY TYPE NO IS:" << type_no << endl;
			if (type_no <= thread_args->vehicle_ratios[0]*100) {
		//		new_vehicle.setType(0); // car
				cout << "I AM A CAR\n";
			} else if ((type_no > thread_args->vehicle_ratios[0]*100) && (type_no <= ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) ) {
		//		new_vehicle.setType(1); //bus
				cout << "I AM A BUS\n";
			} else if (type_no > ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) {
		//		new_vehicle.setType(2);
				cout << "I AM A LORRY\n";
			}
		}


	/*
		STEP 4 CREATE THE VEHICLES AND STORE IN AN TEMP ARRAY OF OBJECTS

		STEP 5 RANDOMIZE THE OBJECTS IN THE ARRAY

		STEP 6 POP AND PUT IN THE QUEUE

  	*/
	/* STEP 7: WAIT FOR THE NEXT ROUND DEPENDING ON THE SLEEP TIMER */
		sleep(thread_args->sleep_time);

  }
   pthread_exit(NULL);
}