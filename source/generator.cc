/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: generator.cc
Description: This file specifies the car generator thead of the system. Please treat as a main file and avoid appending code here but rather include any classes you want to use.
Copyright (c) King's College London

*/
#include "th_structs.h"
#include "vehicle.h"


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
		vehicle* temp_array[actual_no_to_create];
	/*
		STEP 3 DECIDE BASED RATIOS HOW MANY OF EACH VEHICLE TYPE YOU WILL CREATE
		STEP 4 CREATE THE VEHICLES AND STORE IN AN TEMP ARRAY OF OBJECTS
	*/
		for (int z=0; z<actual_no_to_create;z++) temp_array[z] = NULL; //initalize array to null pointers

		for (int i=0; i<actual_no_to_create;i++) {
			temp_array[i] = new vehicle();
			int type_no = rand() % 100 + 1;
			cout << "MY TYPE NO IS:" << type_no << endl;
			if (type_no <= thread_args->vehicle_ratios[0]*100) {
				temp_array[i]->setType(0); // car
			} else if ((type_no > thread_args->vehicle_ratios[0]*100) && (type_no <= ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) ) {
				temp_array[i]->setType(1); //bus
			} else if (type_no > ((thread_args->vehicle_ratios[0]*100) + (thread_args->vehicle_ratios[1]*100))) {
				temp_array[i]->setType(2);
			}
	/*
		STEP 5 SAVE IN TEMP ARRAY AND SHUFFLE
	*/
	//		for (int j=0; j<actual_no_to_create; j++) {
	//			if (temp_array[j] == NULL) temp_array[j] = new_vehicle;
	//		}		
		}

		for (int k=0; k<actual_no_to_create; k++) {
			cout <<  temp_array[k]->getType() << endl;
		}
	/*
		

		

		STEP 6 POP AND PUT IN THE QUEUE

  	*/
	/* STEP 7: WAIT FOR THE NEXT ROUND DEPENDING ON THE SLEEP TIMER */
		sleep(thread_args->sleep_time);

  }
   pthread_exit(NULL);
}