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
#include <stdio.h>
#include <form.h>
#include <panel.h>
#include <curses.h>
#include <limits>
#include "statistics.h"
#include "ResetTrafficLights.cc"


using namespace std;

void *inout(void *arguments)
{

    int num;
    double crat, brat, lrat;
    double normalr, cautiousr, aggressiver;
    int max;
    int timedelay;
    string stp;
    string show;
    vector<int> vehicleTypesStats;
    vector<int> driverTypeStats;

    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
      initscr();   /* Start curses mode */
    
  
    WINDOW * mainwin, * headerwin, *stdstats, *cmdin;
    WINDOW *vehiclestats, *roadnodestats;
    PANEL *panels[2];
    PANEL  *top;
    int      ch;
    /*  Set the dimensions and initial
    position for our child window   */

    int      width = 23, height = 7;
    int      rows  = 25, cols   = 80;
    int      midpointx = COLS/ 2;
    int      midpointy = LINES / 2;


    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
    }
    

    /*  Switch off echoing and enable keypad (for arrow keys)  */
    cbreak();
    raw();
    nodelay(mainwin,TRUE);
    noecho();
    keypad(mainwin, TRUE);
    box(vehiclestats,0,0);
    box(roadnodestats,0,0);
    panels[0]=new_panel(vehiclestats);
    panels[1]=new_panel(roadnodestats);
    set_panel_userptr(panels[0], panels[1]);
    set_panel_userptr(panels[1], panels[0]);

    update_panels();
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_WHITE );
    init_pair(2, COLOR_WHITE, COLOR_BLUE );
    init_pair(3, COLOR_CYAN,  COLOR_WHITE );

    //attron( COLOR_PAIR(2) | A_BLINK );
    bkgd(   COLOR_PAIR(2)); // Green Text on a White Screen
    /*  Make our child window, and add
    a border and some text to it.   */

    headerwin = subwin(mainwin, 7, COLS-4, 1, 2);
    stdstats = subwin(mainwin,6, COLS-4,8,2);
    cmdin = subwin(mainwin,3,COLS-4,LINES-4,2);
    wborder(mainwin, 0, 0, 0, 0, 0, 0, 0, 0);
    box(headerwin, 0, 0);
    box(stdstats,0,0);
    box(cmdin,0,0);
    mvwaddstr(headerwin, 1, midpointx-12,"Traffic Simulation System");
    mvwaddstr(headerwin, 2, 2,"TEAM B: Zinon Kyprianou, Panikos Lazarou, Maria Leventopoulou,");
    mvwaddstr(headerwin, 3, 10,"Adesinmisola Ogunsanya, Kosmas Tsakmakidis");
    mvwaddstr(headerwin,4,2,"build date: 9/3/2013");
    mvwaddstr(headerwin,5,COLS-40,"Simulation Status: Running");
    mvwaddstr(stdstats,1,midpointx, "Total Vehicles in engine:");
    mvwprintw(stdstats,1,midpointx+27, "%d",thread_args->simstats.getTotalVehicles());
    mvwaddstr(stdstats,2,2, "Average Time in Engine:");
    mvwprintw(stdstats,2,27, "%0.00f",thread_args->simstats.getAvTimeinEngine());
    mvwaddstr(stdstats,1,2, "Sim granularity: ");
    mvwprintw(stdstats,1,20,"%d",thread_args->sleep_time);
    mvwaddstr(stdstats,1,25, "Sim updates: ");
    mvwaddstr(stdstats,2,midpointx,"Cars: ");
    mvwprintw(stdstats,2,midpointx+6, "%d",thread_args->simstats.getVehicleTypeNum(0));
    mvwaddstr(stdstats,2,midpointx+10,"Buses: ");
    mvwprintw(stdstats,2,midpointx+17, "%d",thread_args->simstats.getVehicleTypeNum(1));
    mvwaddstr(stdstats,2,midpointx+20,"Lorries: ");
    mvwprintw(stdstats,2,midpointx+30, "%d",thread_args->simstats.getVehicleTypeNum(2));
    mvwaddstr(stdstats,3,midpointx,"Drivers(Normal:    Cautious:    Aggressive:   )");
    mvwprintw(stdstats,3,midpointx+16,"%d",thread_args->simstats.getDriverTypeNum(0));
    mvwprintw(stdstats,3,midpointx+30,"%d",thread_args->simstats.getDriverTypeNum(1));
    mvwprintw(stdstats,3,midpointx+45,"%d",thread_args->simstats.getDriverTypeNum(2));
    mvwprintw(stdstats,1,40, "%d",thread_args->tick_count);
    mvwprintw(cmdin,1,2, "Command:");
    refresh();

    top = panels[0];


    halfdelay(1);
    while(!thread_args->finished) {
        
        mvwprintw(stdstats,2,27, "%0.00f",thread_args->simstats.getAvTimeinEngine());
        mvwprintw(stdstats,2,midpointx+6, "%d",thread_args->simstats.getVehicleTypeNum(0));
        mvwprintw(stdstats,2,midpointx+17, "%d",thread_args->simstats.getVehicleTypeNum(1));
        mvwprintw(stdstats,2,midpointx+30, "%d",thread_args->simstats.getVehicleTypeNum(2));
        mvwprintw(stdstats,1,midpointx+27, "%d",thread_args->simstats.getTotalVehicles());
        mvwprintw(stdstats,3,midpointx+16,"%d",thread_args->simstats.getDriverTypeNum(0));
        mvwprintw(stdstats,3,midpointx+30,"%d",thread_args->simstats.getDriverTypeNum(1));
        mvwprintw(stdstats,3,midpointx+45,"%d",thread_args->simstats.getDriverTypeNum(2));
        mvwprintw(stdstats,1,40, "%d",thread_args->tick_count);
        wrefresh(stdstats);
        

        do {

            ch = mvwgetch(cmdin,1,10);
            if (ch == '\n') break;
            if (ch == 'a') mvwprintw(stdstats,2,40, "%d",thread_args->tick_count);
            if (ch == 't')  mvwaddstr(stdstats,3,2,"testing this shit"); 
            if (ch == 'q') thread_args->finished=true;
        
            wrefresh(cmdin);
        
        } while (ch != ERR);
    
        wmove(cmdin,1,10);
        wrefresh(cmdin);
        sleep(thread_args->sleep_time);
    }
    delwin(mainwin);
    delwin(headerwin);
    delwin(stdstats);
    endwin();
    
    pthread_exit(NULL);
}
