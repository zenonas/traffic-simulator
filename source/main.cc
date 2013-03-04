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
#include "sysio.cc"
#include "map.h"
#include <queue>
#include "th_structs.h"

using namespace std;

int main ()
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
   th_args.sleep_time = 3; // this may change
   th_args.engine_change = false;
   
//
//read xml file to construct map

   //th_args.mymap.printAllPaths();

//get vector with all paths
   vector<vector<int> > paths = th_args.mymap.getAllPaths();
/* DEFINING ENGINE THREAD ARGUEMENTS */

/* DEFINING I/O THREAD ARGUEMENT */

/* test graph code */

/* MULTI-THREADING STUFF */

   int rc;
   pthread_t threads[3];
   pthread_attr_t attr;
   void *status;


/* test graph code */

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
 //     cout << "Creating thread: Vehicle Generator... ";
      rc = pthread_create(&threads[0], NULL, generator, (void*)&th_args);
      if (rc){
       cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
     // cout << "OK!" << endl;

   //   cout << "Creating thread: Engine... "; 
      rc = pthread_create(&threads[1], NULL, engine, (void*)&th_args);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      //cout << "OK!" << endl;
      
     // cout << "Creating thread: I/O... ";
      rc = pthread_create(&threads[2], NULL, inout, (void*)&th_args);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      //cout << "OK!" << endl;
   

   // free attribute and wait for the other threads
   pthread_attr_destroy(&attr);
 
      rc = pthread_join(threads[0], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         return(-1);
      }
      cout << "Vehicle Generator Thread completed and exiting with status :" << status << endl;
      
      rc = pthread_join(threads[1], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         return(-1);
      }
      cout << "Engine Thread completed and exiting with status :" << status << endl;
      
      rc = pthread_join(threads[2], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         return(-1);
      }
      cout << "I/O Thread completed and exiting with status :" << status << endl;
   
     /* while (!th_args.VWaitingQ.empty()) {
         cout << "(OUTSIDE THREAD) TYPE: " << th_args.VWaitingQ.front()->vehi_id << endl;
         th_args.VWaitingQ.pop();
      }*/
   cout << "Main program exiting." << endl;
   pthread_exit(NULL);
}


