/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 22/2/2013
File: sysio.cc
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <limits>

using namespace std;

void *inout(void *arguments)
{

    string command;
    int num;
    double crat, brat, lrat;
    double normalr, cautiousr, aggressiver;
    int max;
    int timedelay;
    string stp;
    string show;

    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;

    while(!thread_args->finished)
    {
	cout << "Input a Command: ";
	cin >> command;
	while ( command != "novehicles" && command != "vehicle-ratio" &&
			command != "driver-ratio" && command != "SetMaxSpeed" && 
			command != "ToggleTrafficLights" && command != "stop" &&
            command != "ShowStatistics")
	{
		cout << "Invalid Command. Input another Command: "; 
		cin >> command ; 
	}

	if (command == "novehicles")
	{
		cout << "Insert max number of Vehicles to be created: " << endl;
		while (!(cin >> num)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Insert max number of Vehicles to be created: ";
		}		
		thread_args->max_no_vehicles = num;
	}
	if (command == "vehicle-ratio")
	{
		do{
			cout << "Insert Car Ratio: ";
			while (!(cin >> crat)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Car Ratio: ";
			}
					
			cout << "Insert Bus Ratio: ";
			while (!(cin >> brat)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Bus Ratio: ";
			}
			cout << "Insert Lorry Ratio: ";
			while (!(cin >> lrat)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');				
				cout << "Invalid input! Insert Lorry Ratio: ";
			}
		}while (crat + brat + lrat != 1);
		
		thread_args->vehicle_ratios[0] = crat;
		thread_args->vehicle_ratios[1] = brat;
		thread_args->vehicle_ratios[2] = lrat;
	}

	if (command == "driver-ratio")
	{
		do{
			cout << "Insert Normal Driver Ratio: ";
			while (!(cin >> normalr)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Normal Driver Ratio: ";
			}
			cout << "Insert Cautious Driver Ratio: " << endl;
			while (!(cin >> cautiousr)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Cautious Driver Ratio: ";
			}
			cout << "Insert Aggressive Driver Ratio: ";
			while (!(cin >> aggressiver)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Aggressive Driver Ratio: ";
			}

		} while (normalr + cautiousr + aggressiver != 1);

		thread_args->driver_ratios[0] = normalr;
		thread_args->driver_ratios[1] = cautiousr;
		thread_args->driver_ratios[2] = aggressiver;
	}

	if (command == "SetMaxSpeed")
	{
		cout << "Insert Maximum Speed: ";
		while (!(cin >> max)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Maximum Speed: ";			
		}


		//SetMaxSpeed(speed);
	}

	if (command == "ToggleTrafficLights")
	{
		cout << "Insert Time Delay: ";
		while (!(cin >> timedelay)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Insert Time Delay: ";				
		}
		//SetTrafficLights(tdelay);
	}

	if (command == "stop"){
		//call for statistics
		thread_args->finished = true;
	}
	if (command == "ShowStatistics"){
		//ShowStatistics(w);
	}
  }

   pthread_exit(NULL);
}
