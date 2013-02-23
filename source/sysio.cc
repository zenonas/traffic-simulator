/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 22/2/2013
File: sysio.cc
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#include<string.h>
#include<stdlib.h>
#include<iostream> 
#include<limits>

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

    struct gen_thread *thread_args;
    thread_args = (struct gen_thread *)arguments;

    while(!thread_args->gen_finished)
    {
	cout << "Input a Command: ";
	cin >> command;
	while ( command != "SetNoVehicles" && command != "SetVehicleTRatio" &&
			command != "SetDriverTRatio" && command != "SetMaxSpeed" && 
			command != "ToggleTrafficLights" && command != "StopSimulation" &&
            command != "ShowStatistics")
	{
		cout << "Invalid Command. Input another Command: "; 
		cin >> command ; 
	}

	if (command == "SetNoVehicles")
	{
		cout << "Insert number of Vehicles: " << endl;
		while (!(cin >> num)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Insert number of Vehicles: ";
		}		
		//SetNumVehicles(num);
	}
	if (command == "SetVehicleTRatio")
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
		
		//SetVehicleTypeRatio(cratio, bratio, lratio);
	}

	if (command == "SetDriverTRatio")
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

		//SetDriverRatio(normalratio, cautiousratio, aggressiveratio);
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

	if (command == "StopSimulation"){
		thread_args->gen_finished = true;
	}
	if (command == "ShowStatistics"){
		//ShowStatistics(w);
	}
  }


   pthread_exit(NULL);
}
