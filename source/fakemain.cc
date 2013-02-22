/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: main.cc
Description: This file includes the main function of the system, handling our different threads.

Copyright (c) King's College London

*/
#include <iostream>
#include <pthread.h>
#include "generator.cc"
#include "engine.cc"
#include "sysio.cc"
#include "mapcreate.cc"
#include "map.cc"
#include "vehicle.cc"
#include "graphNode.cc"
#include "roadNode.cc"
#include "trafficLight.cc"
//#include <ogdf/basic/Graph.h>
//#include <ogdf/basic/GraphAttributes.h>
//#include "../lib/DLList.cc"
//#include <queue>


using namespace std;
//using namespace ogdf;


int main ()
{
   int rc;
   pthread_t threads[3];
   pthread_attr_t attr;
   void *status;
   map mymap;
   mymap.ReadXMLFile();

/* test graph code
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
 
	return 0;
*/

/* test graph code */

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
      cout << "Creating thread: Vehicle Generator... ";
      rc = pthread_create(&threads[0], NULL, generator, (void*)0);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         return(-1);
      }
      cout << "OK!" << endl;
      
      cout << "Creating thread: Engine... ";
      rc = pthread_create(&threads[1], NULL, engine, (void*)1);
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

