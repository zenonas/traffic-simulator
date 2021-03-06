/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 23/2/2013
File: th_structs.h
Description: This file includes the main function of the system, handling our different threads.

Copyright (c) King's College London

*/

#ifndef A_TH_STRC
#define A_TH_STRC

#include "vehicle.h"
#include "statistics.h"
#include "map.h"
#include <curses.h>
#include <queue>

struct thread_arguments {
      bool finished; //global finished
      bool engine_change;
      int max_no_vehicles; 
      double vehicle_ratios[3];
      double driver_ratios[3];
      bool arg_changed;
      double sleep_time;
      int tick_count;
      queue<vehicle *> VWaitingQ;
      map mymap;
      int CurrentTimer;
      statistics simstats;
      bool debug;
      vector<vehicle *> vehiclesInEngine;
      bool sim_paused;

};



#endif

