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
	/*while(!thread_args->VWaitingQ.empty) {

		//STEP 1: CALL THE SPLIT TO ENTRY POINT QUEUES FUNCTION
		
	}*/

      //STEP 2: manually create 5 vehicles
   
   vector<vehicle> tempVector;
   vector<roadNode> roads;
   roads= thread_args->mymap.getunfRoads();
   for (int i=0; i<5; i++){
      int entryP= rand() % roads.size() +1 ;
      int exitP= rand() % roads.size() + 1;
      vehicle myVehicle(i, entryP, exitP, thread_args->mymap);
      Position position;
      position.roadNodeID=entryP;
      position.lane=1;
      position.p=0;
      myVehicle.setCurrentPosition(position);
      tempVector.push_back(myVehicle);    
   }
   for (int i=0; i<tempVector.size(); i++){
      cout << "\nVehicle " << i+1 << ": ";
      tempVector[i].printPath();
   }
   cout << endl;

   //STEP 3: for every car in the engine (tempVector), check every other car
   //        and if they have part of same path do...
   for(int i=0; i<tempVector.size(); i++){    
      vector<int> vehicle1Path = tempVector[i].getPath();
      for (int k=0; k<tempVector.size(); k++){
         vector<int> vehicle2Path = tempVector[k].getPath();
         int flag=0;
         for (int p=0; p<vehicle1Path.size(); p++){
            for (int q=0; q<vehicle2Path.size(); q++){                            
               if (vehicle1Path[p]==vehicle2Path[q] && i!=k && flag==0){
                  ///check current positions and calculate if affecting
                  Position positionVehicle1;
                  Position positionVehicle2;
                  positionVehicle1= tempVector[i].getCurrentPosition();
                  positionVehicle2= tempVector[k].getCurrentPosition();
                  int speedVehicle1 = tempVector[i].getCurrentSpeed();
                  int speedVehicle2 = tempVector[k].getCurrentSpeed();
                  int driver1 = tempVector[i].getDriverType();
                  int driver2 = tempVector[k].getDriverType();
                  /*
                     Do the appopriate checks in order to update position of car i

                  */
                  flag=1;
               }
            }
         }
      }
   }


	sleep(thread_args->sleep_time);
}
   pthread_exit(NULL);
}
