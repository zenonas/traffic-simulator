/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 8/3/2013
Updated: 8/3/2013
File: statistics.h
Description: This file includes the definition for the statistics class.

Copyright (c) King's College London
*/

#ifndef statistics_h
#define statistics_h

#include <vector>
#include "map.h"
#include "vehicle.h"
#include "statistics.h"

using namespace std;

class statistics
{
public:
   statistics();
   ~statistics();
   void CaptureStatistics(map* mymap, vector<vehicle *> vehiclesInEngine);
   void RecordToSQL();

   double getAvSpeed();
   double getAvTimeinEngine();
   int getMostVisitedRoad();
   int getMostCommonExitP();
   int getMostCommonEntryP();
   int getVehicleTypeNum(int vehicleType);
   int getDriverTypeNum(int driverType); 
   int getTotalVehicles();
   int getRemVehi();
   int getTotalCrashedVehicles();
   void addCrashedVehicle();
   void addRemVehi();
   map* getMap();
   vector<vehicle *> getVehiclesInEngine();

private:
   map* VehMap;
   vector<vehicle *> VehEng;
   double avspeed;
   int vehicesRemoved;
   int vehiclesCrashed;
   double avtimeinengine;
   int most_visited_road;
   int most_common_exitP;
   int most_common_entryP;
   vector<int> vehicletypenum;
   vector<int> drivertypenum;
   int total; 
};


#endif