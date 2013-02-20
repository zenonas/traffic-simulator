/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 16/2/2013
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
#include "mapcreate.cc"
#include "map.cc"
#include "vehicle.cc"
#include "graphNode.cc"
#include "roadNode.cc"
#include "trafficLight.cc"

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include "../lib/DLList.cc"
#include <queue>
#include "th_structs.h"

using namespace std;
using namespace ogdf;
 

int main ()
{

/* DEFINING GENERATOR THREAD ARGUMENTS */

   gen_thread generator_args;
   generator_args.gen_finished = false;
   generator_args.max_no_vehicles = 20;
   generator_args.vehicle_ratios[0] = 0.85; // cars
   generator_args.vehicle_ratios[1] = 0.1; // bus
   generator_args.vehicle_ratios[2] = 0.05; // lorries
   generator_args.driver_ratios[0] = 0.65; //normal
   generator_args.driver_ratios[1] = 0.2; //cautious
   generator_args.driver_ratios[2] = 0.15; //aggressive (nai stin ellada imaste)
   generator_args.arg_changed = false;
   generator_args.sleep_time = 3; // this may change

/* DEFINING ENGINE THREAD ARGUEMENTS */

/* DEFINING I/O THREAD ARGUEMENT */

/* test graph code */



/* MULTI-THREADING STUFF */

   int rc;
   pthread_t threads[3];
   pthread_attr_t attr;
   void *status;

Graph G;
	GraphAttributes GA(G, GraphAttributes::nodeGraphics |	
		GraphAttributes::edgeGraphics );
 
	const int LEN = 11;
	for(int i = 1; i<LEN; ++i) {
		node left = G.newNode();
		GA.x(left) = -5*(i+1);
		GA.y(left) = -20*i;		
		GA.width(left) = 10*(i+1);
		GA.height(left) = 15;
 
		node bottom = G.newNode();
		GA.x(bottom) = 20*(LEN-i);		
		GA.y(bottom) = 5*(LEN+1-i);
		GA.width(bottom) = 15;
		GA.height(bottom) = 10*(LEN+1-i);
 
		edge e = G.newEdge(left,bottom);
		DPolyline &p = GA.bends(e);
		p.pushBack(DPoint(10,-20*i));
		p.pushBack(DPoint(20*(LEN-i),-10));
	}
 
	GA.writeGML("manual_graph.gml");


/* test graph code */

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
      cout << "Creating thread: Vehicle Generator... ";
      rc = pthread_create(&threads[0], NULL, generator, (void*)&generator_args);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      cout << "OK!" << endl;

      cout << "Creating thread: Engine... ";
      rc = pthread_create(&threads[1], NULL, engine, (void*)&generator_args);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      cout << "OK!" << endl;
      
      cout << "Creating thread: I/O... ";
      rc = pthread_create(&threads[2], NULL, inout, (void*)2);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      cout << "OK!" << endl;
   

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
   

   cout << "Main program exiting." << endl;
   pthread_exit(NULL);
}


