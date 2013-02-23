/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: engine.cc
Description: This file specifies the engine thread of the system. Please treat as a "main" file and include any additional stuff you create rather than appending here.

Copyright (c) King's College London

*/
#include "th_structs.h"

using namespace std;

void *engine(void *arguments)
{
   struct thread_arguments *thread_args;
   thread_args = (struct thread_arguments *)arguments;
   
while (!thread_args->finished) {



	sleep(thread_args->sleep_time);
}
   pthread_exit(NULL);
}
