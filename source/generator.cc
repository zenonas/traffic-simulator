/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: generator.cc
Description: This file specifies the car generator thead of the system. Please treat as a main file and avoid appending code here but rather include any classes you want to use.
Copyright (c) King's College London

*/
using namespace std;

void *generator(void *t)
{
   long tid;
   tid = (long)t;
   sleep(10);
   cout << "Generator Thread with id : " << tid << "  ...exiting " << endl;
   pthread_exit(NULL);
}