/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: sysio.cc
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <curses.h>
#include <limits>
#include "ResetTrafficLights.cc"


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


	initscr();   /* Start curses mode */
	 start_color();

    init_pair(1, COLOR_GREEN, COLOR_WHITE );
    init_pair(2, COLOR_WHITE, COLOR_BLUE );
    init_pair(3, COLOR_CYAN,  COLOR_WHITE );

    //attron( COLOR_PAIR(2) | A_BLINK );
    bkgd(   COLOR_PAIR(2)); // Green Text on a White Screen
	printw("                            Traffic Simulation System                         \n");
	printw("------------------------------------------------------------------------------\n");
	printw("TEAM B: Zinon Kyprianou, Panikos Lazarou, Maria Leventopoulou, Adesinmisola Ogunsanya, Kosmas Tsakmakidis\n");
	printw("build 0101: 9/3/2013\n");
	printw("------------------------------------------------------------------------------\n");
	printw("Simulation started\n");
	refresh();   /* Print it on to the real screen */
	getch();  /* Wait for user input */
    while(!thread_args->finished)
    {
    refresh();   /* Print it on to the real screen */
    /*cout << "Select one of the following commands:\n";
	cout << "1. SetNoVehicles\n";
	cout << "2. SetVehicleTRatio\n";
	cout << "3. SetDriverTRatio\n";
	cout << "4. ToggleTrafficLights\n";
	cout << "5. StopSimulation\n";
	cout << "6. ShowStatistics\n";
	cout << "7. Exit\n";
*/
	cin >> command;
	while ( command != "SetNoVehicles" && command != "1"
			&& command != "SetVehicleTRatio" && command != "2"
			&& command != "SetDriverTRatio" && command != "3"
			&& command != "ToggleTrafficLights" && command != "4"
			&& command != "StopSimulation" && command != "5"
			&& command != "ShowStatistics" && command != "6"
			&& command != "Exit" && command != "7")
	{
		cout << "Invalid Command. Input another Command: "; 
		cin >> command ; 
	}

	if (command == "novehicles" || command == "1")
	{
		cout << "Insert max number of Vehicles to be created: " << endl;
		while (!(cin >> num)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Insert max number of Vehicles to be created: ";
		}		
		thread_args->max_no_vehicles = num;
	}
	if (command == "vehicle-ratio" || command == "2")
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

	if (command == "driver-ratio" || command == "3")
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

	if (command == "ToggleTrafficLights" || command == "4")
	{

		ToggleLights(thread_args,thread_args->CurrentTimer);
		
	}


	if (command == "stop" || command == "5"){
		//call for statistics
		thread_args->finished = true;
	}
	if (command == "ShowStatistics" || command == "6"){
		//ShowStatistics(w);
	}
	if (command == "Exit" || command == "7"){
		//Terminate Simulation
	}
  }

   pthread_exit(NULL);
}
