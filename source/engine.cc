/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 15/2/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/
#include "th_structs.h"

using namespace std;

void *engine(void *arguments)
{
   struct thread_arguments *p;
   p = (struct thread_arguments *)arguments;
   sleep(5);

  
   pthread_exit(NULL);
}
