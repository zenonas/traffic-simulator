/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: main.cc
Description: This file includes the main function of the system, handling our different threads.

Copyright (c) King's College London

*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "generator.cc"
#include "engine.cc"
#include "sysio.h"
#include "map.h"
#include <string.h>
#include <curses.h>
#include <queue>
#include "th_structs.h"

using namespace std;

int main (int argc, char *argv[])
{

/* DEFINING GENERATOR THREAD ARGUMENTS */

   thread_arguments th_args;
   th_args.finished = false;
   th_args.max_no_vehicles = 20;
   th_args.vehicle_ratios[0] = 0.7; // cars
   th_args.vehicle_ratios[1] = 0.25; // bus
   th_args.vehicle_ratios[2] = 0.05; // lorries
   th_args.driver_ratios[0] = 0.65; //normal
   th_args.driver_ratios[1] = 0.2; //cautious
   th_args.driver_ratios[2] = 0.15; //aggressive (nai stin ellada imaste)
   th_args.arg_changed = false;
   th_args.sleep_time = 5; // this may change
   th_args.tick_count = 0;
   th_args.engine_change = false;
   th_args.debug = false;
// Checking for debug mode
   if (argc > 1) {
      if (strcmp(argv[1],"debug") == 0) {
         cout << "Running Simulation without the UI in debug mode" <<endl;
         th_args.debug = true;
      }
   }

   if (th_args.debug) cout << "Traffic Lights: " << th_args.mymap.trafficlights.size() << endl;

/* MULTI-THREADING STUFF */

   int rc;
   pthread_t threads[3];
   pthread_attr_t attr;
   void *status;

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
   //THREAD GENERATOR
   rc = pthread_create(&threads[0], NULL, generator, (void*)&th_args);
   if (rc){
      cout << "Error:unable to create thread," << rc << endl;
      return(-1);
   }

   //THREAD ENGINE
   rc = pthread_create(&threads[1], NULL, engine, (void*)&th_args);
   if (rc){
      cout << "Error:unable to create thread," << rc << endl;
      return(-1);
   }
      
   //THREAD SYSIO
   if (th_args.debug == false) {
      rc = pthread_create(&threads[2], NULL, inout, (void*)&th_args);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
   }
   

   // free attribute and wait for the other threads
   pthread_attr_destroy(&attr);
   rc = pthread_join(threads[0], &status);
   if (rc){
      cout << "Error:unable to join," << rc << endl;
      return(-1);
   }
   if (th_args.debug) cout << "Vehicle Generator Thread completed and exiting with status :" << status << endl;   
   rc = pthread_join(threads[1], &status);
   if (rc){
      cout << "Error:unable to join," << rc << endl;
      return(-1);
   }
   if (th_args.debug) cout << "Engine Thread completed and exiting with status :" << status << endl;
   if (th_args.debug == false) {  
      rc = pthread_join(threads[2], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         return(-1);
      }
   }

   if (th_args.debug) cout << "Main program exiting." << endl;
   pthread_exit(NULL);

   endwin();    /* End curses mode   */
}


