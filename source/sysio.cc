/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: sysio.cc
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
using namespace std;

void *inout(void *t)
{
   long tid;
   tid = (long)t;
   sleep(1);
   cout << "I/O Thread with id : " << tid << "  ...exiting " << endl;
   pthread_exit(NULL);
}