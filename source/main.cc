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

using namespace std;

int main ()
{
   int rc;
   pthread_t threads[3];
   pthread_attr_t attr;
   void *status;

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