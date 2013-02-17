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
   struct gen_thread *p;
   p = (struct gen_thread *)arguments;
   
   bool finished = p->gen_finished;
   p->k = 3;

   cout << "Generator Thread with id : " << "1" << "  is created" << endl;
   

   if (finished == false) cout << "alo\n";

   pthread_exit(NULL);
}