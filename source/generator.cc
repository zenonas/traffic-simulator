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
   

  while(!thread_args->gen_finished) {

  	/*

  		STEP: 1 GET RATIOS
  		(NO OF VEHICLES, DRIVER TYPE RATIO, VEHICLE TYPE RATIO)

  		STEP 2 GET NUMBER OF VEHICLES/H NEEDED
		BASED ON THIS DECIDE HOW MANY VEHICLES NEED TO BE CREATE IN THIS ROUND

		STEP 3 DECIDE BASED RATIOS HOW MANY OF EACH VEHICLE TYPE YOU WILL CREATE

		STEP 4 CREATE THE VEHICLES AND STORE IN AN TEMP ARRAY OF OBJECTS

		STEP 5 RANDOMIZE THE OBJECTS IN THE ARRAY

		STEP 6 POP AND PUT IN THE QUEUE

  	*/

  }
   pthread_exit(NULL);
}