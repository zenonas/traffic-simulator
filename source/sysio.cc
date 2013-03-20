/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 15/2/2013
Updated: 23/2/2013
File: sysio.cc
Description: This file specifies the input and output thread of the system

Copyright (c) King's College London

*/
#include "sysio.h"
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <stdio.h>
#include <form.h>
#include <panel.h>
#include <curses.h>
#include "roadNode.h"
#include <vector>
#include <limits>
#include "statistics.h"
#include "ResetTrafficLights.h"


using namespace std;

void updateVehicles(WINDOW *vehiclestats, void *arguments) {
    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
    int midpointx = COLS / 2;

    vector<vehicle *> vehiclesInEngine = thread_args->simstats.getVehiclesInEngine();
    for (int y=0; y<LINES-17; y++) {
        wmove(vehiclestats,2+y,2);
        wclrtoeol(vehiclestats);
    }
    box(vehiclestats,0,0);
    for (int i=0; i<vehiclesInEngine.size(); i++) {
        vector<int> vehiclePath = vehiclesInEngine[i]->getPath();
        mvwprintw(vehiclestats,2+i,3,"%d",vehiclesInEngine[i]->vehi_id);
        if (vehiclesInEngine[i]->getType() == 0)
            mvwaddstr(vehiclestats,2+i,16,"Car");
        else if (vehiclesInEngine[i]->getType() == 1)
            mvwaddstr(vehiclestats,2+i,16,"Bus");
        else if (vehiclesInEngine[i]->getType() == 2)
            mvwaddstr(vehiclestats,2+i,16,"Lorry");
        mvwprintw(vehiclestats,2+i,31,"%.f",vehiclesInEngine[i]->getCurrentSpeed());
        mvwprintw(vehiclestats,2+i,41,"%d",vehiclesInEngine[i]->getEntryPoint());
        mvwprintw(vehiclestats,2+i,51,"%d",vehiclesInEngine[i]->getExitPoint());
        for (int vp=0; vp<vehiclePath.size(); vp++) {
            mvwprintw(vehiclestats,2+i,60+(3*vp)," %d", vehiclePath[vp]);
        }        
        mvwprintw(vehiclestats,2+i,80,"roadNode: %d",vehiclesInEngine[i]->getCurrentPosition().roadNodeID);
        mvwprintw(vehiclestats,2+i,93,"Pos: %d", vehiclesInEngine[i]->getCurrentPosition().p);
        mvwprintw(vehiclestats,2+i,105,"Lane: %d", vehiclesInEngine[i]->getCurrentPosition().lane);
        mvwprintw(vehiclestats,2+i,117,"%d s",vehiclesInEngine[i]->getTimer()*thread_args->sleep_time);

        //mvwprintw(vehiclestats,2+i,51,"%d",vehiclesInEngine[i]->getCurrentSpeed()); //path
        //vwprintw(vehiclestats,2+i,16,"%d",vehiclesInEngine[i]->getCurrentSpeed());  //current position in path
    }
}
void updateTrafficLights(WINDOW *trafficlstats, void *arguments){
    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
    int midpointx = COLS / 2;

    for (int y=0; y<LINES-17; y++) {
    wmove(trafficlstats,2+y,2);
    wclrtoeol(trafficlstats);
    }
    box(trafficlstats,0,0);
    for (int i=0; i<thread_args->mymap.trafficlights.size(); i++) {
        mvwprintw(trafficlstats,2+i,3,"%d",thread_args->mymap.trafficlights[i]->getCartesianX());
        mvwprintw(trafficlstats,2+i,11,"%d",thread_args->mymap.trafficlights[i]->getCartesianY());
        mvwprintw(trafficlstats,2+i,21,"%d",thread_args->mymap.trafficlights[i]->getTimer());
         if (thread_args->mymap.trafficlights[i]->getState() == 0) {
            wattron(trafficlstats,COLOR_PAIR(4));
            mvwaddstr(trafficlstats,2+i,30,"RED");
            wattroff(trafficlstats,COLOR_PAIR(4));
        } else {
            wattron(trafficlstats,COLOR_PAIR(3));
            mvwaddstr(trafficlstats,2+i,30,"GREEN");
            wattroff(trafficlstats,COLOR_PAIR(3));
        }
        mvwprintw(trafficlstats,2+i,40,"%d",thread_args->mymap.trafficlights[i]->getPos().roadNodeID);
        mvwprintw(trafficlstats,2+i,45,"%d",thread_args->mymap.trafficlights[i]->getPos().p);
        mvwprintw(trafficlstats,2+i,55,"%d",thread_args->mymap.trafficlights[i]->getPos().lane);
    }


        //mvwprintw(roadnodestats,2+i,46,"%d",vehiclesInEngine[i]->getExitPoint()); //connected roadnodes
        //mvwprintw(roadnodestats,2+i,66,"%d",vehiclesInEngine[i]->getExitPoint()); // current vehicles in roadnode
}

void updateRoadNodes(WINDOW *roadnodestats, void *arguments){
    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
    int midpointx = COLS / 2;

    vector<roadNode > unfRoads = thread_args->mymap.getunfRoads();
    vector<vehicle *> vehiclesInEngine = thread_args->simstats.getVehiclesInEngine();
    for (int y=0; y<LINES-17; y++) {
    wmove(roadnodestats,2+y,2);
    wclrtoeol(roadnodestats);
    }
    box(roadnodestats,0,0);
    for (int i=0; i<unfRoads.size(); i++) {
        mvwprintw(roadnodestats,2+i,3,"%d",unfRoads[i].getId());
        mvwprintw(roadnodestats,2+i,16,"%d",unfRoads[i].getLength());
        mvwprintw(roadnodestats,2+i,31,"%d",unfRoads[i].getMaxSpeed());
        int carcount = 0;
        for (int p=0; p<vehiclesInEngine.size(); p++) {
            int id = vehiclesInEngine[p]->getCurrentPosition().roadNodeID;
        if (id == unfRoads[i].getId())
            mvwprintw(roadnodestats,2+i,65+(2*carcount)," %d",vehiclesInEngine[p]->vehi_id);
            carcount++;
    }


        //mvwprintw(roadnodestats,2+i,46,"%d",vehiclesInEngine[i]->getExitPoint()); //connected roadnodes
        //mvwprintw(roadnodestats,2+i,66,"%d",vehiclesInEngine[i]->getExitPoint()); // current vehicles in roadnode
    }
}

int maxVehicleChange(WINDOW *cmdbox,void *arguments) {
    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
    int midpointx = COLS / 2;
    nodelay(cmdbox,FALSE);
    wattron(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox, 1, midpointx-12,"Traffic Simulation System");
    mvwaddstr(cmdbox,2,midpointx-15,"Change the max number of Vehicles");
    wattroff(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox,3,2, "This controls the maximum number of vehicles the Vehicle generator is allowed to");
    mvwaddstr(cmdbox,4,2, "create during each of the simulation updates");
    mvwaddstr(cmdbox,5,2, "Please enter a new maximum number");
    wattron(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox,5,40, "          ");
    wattroff(cmdbox, A_UNDERLINE);
    int maxInLen = 4;
    char input[maxInLen];
    for (int i=0; i<maxInLen; i++){
        int charIn = mvwgetch(cmdbox,5,41+i);
        if (charIn != '\n')
            input[i] = charIn;
        else
            break;
    }
    int newNum = atoi(input);
    thread_args->max_no_vehicles = newNum;
    return 1;
}

int changeSimTime(WINDOW *cmdbox,void *arguments) {
    struct thread_arguments *thread_args;
    thread_args = (struct thread_arguments *)arguments;
    int midpointx = COLS / 2;
    nodelay(cmdbox,FALSE);
    wattron(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox, 1, midpointx-12,"Traffic Simulation System");
    mvwaddstr(cmdbox,2,midpointx-15,"Change the simulation granularity");
    wattroff(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox,3,2, "This controls the time between each simulation tick. This setting defaults");
    mvwaddstr(cmdbox,4,2, "to 5 second lapses");
    mvwaddstr(cmdbox,5,2, "Please enter a new tick time:");
    wattron(cmdbox, A_UNDERLINE);
    mvwaddstr(cmdbox,5,40, "          ");
    wattroff(cmdbox, A_UNDERLINE);
    int maxInLen = 3;
    char input[maxInLen];
    for (int i=0; i<maxInLen; i++){
        int charIn = mvwgetch(cmdbox,5,41+i);
        if (charIn != '\n')
            input[i] = charIn;
        else
            break;
    }
    int newNum = atoi(input);
    thread_args->sleep_time = newNum;
    return 1;
}

void *inout(void *arguments)
{

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
    WINDOW * mainwin, * headerwin, *stdstats, *cmdin, *helpwin, *helpbox;
    int      ch;
    int      midpointx = COLS/ 2;
    int      midpointy = LINES / 2;


    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
    }
    
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE );
    init_pair(2, COLOR_WHITE, COLOR_BLUE );
    init_pair(3, COLOR_GREEN,  COLOR_BLUE );
    init_pair(4, COLOR_RED,  COLOR_BLUE );
    bkgd(COLOR_PAIR(2)); // Green Text on a White Screen

    /*  Switch off echoing and enable keypad (for arrow keys)  */
    cbreak();
    raw();
    nodelay(mainwin,TRUE);
    //noecho();
    keypad(mainwin, TRUE);



    //Following is code pertaining to the Panels showing Live updates of Vehicles
    WINDOW *vehiclestats, *roadnodestats, *trafficlstats, *cmdbox;
    PANEL *panels[6];
    vehiclestats = newwin(LINES-18,COLS-4,14,2);
    roadnodestats = newwin(LINES-18,COLS-4,14,2);
    trafficlstats = newwin(LINES-18,COLS-4,14,2);
    helpbox = newwin(7,COLS-4,1,2);
    cmdbox = newwin(7,COLS-4,1,2);
    headerwin = newwin(7, COLS-4, 1, 2);
    box(vehiclestats,0,0);
    box(roadnodestats,0,0);
    box(helpbox,0,0);
    box(cmdbox,0,0);
    box(headerwin, 0, 0);
    box(trafficlstats,0,0);
    wbkgd(vehiclestats,COLOR_PAIR(2));
    wbkgd(roadnodestats,COLOR_PAIR(2));
    wbkgd(helpbox,COLOR_PAIR(1));
    wbkgd(cmdbox,COLOR_PAIR(1));
    wbkgd(headerwin,COLOR_PAIR(2));
    wbkgd(trafficlstats,COLOR_PAIR(2));
    panels[0]=new_panel(vehiclestats);
    panels[1]=new_panel(roadnodestats);
    panels[2]=new_panel(helpbox);
    panels[3]=new_panel(headerwin);
    panels[4]=new_panel(cmdbox);
    panels[5]=new_panel(trafficlstats);
    set_panel_userptr(panels[0], panels[1]);
    set_panel_userptr(panels[1], panels[2]);
    set_panel_userptr(panels[2], panels[0]);
    bkgd(COLOR_PAIR(2));
    update_panels();

    int cpanel = 0;
    int helppanel = 0;
    int cmdbox_status = 0 ;
    show_panel(panels[0]);
    show_panel(panels[3]);
    //Panel code ends here
    
    /*  Make our child window, and add
    a border and some text to it.   */

   
    stdstats = subwin(mainwin,6, COLS-4,8,2);
    cmdin = subwin(mainwin,3,25,LINES-4,2);
    helpwin = subwin(mainwin,3,COLS-29,LINES-4,27);
    wborder(mainwin, 0, 0, 0, 0, 0, 0, 0, 0);
    box(stdstats,0,0);
    box(cmdin,0,0);
    box(helpwin,0,0);

    mvwaddstr(headerwin, 1, midpointx-12,"Traffic Simulation System");
    mvwaddstr(headerwin, 2, 2,"TEAM B: Zinon Kyprianou, Panikos Lazarou, Maria Leventopoulou,");
    mvwaddstr(headerwin, 3, 10,"Adesinmisola Ogunsanya, Kosmas Tsakmakidis");
    mvwaddstr(headerwin,4,2,"build date: 19/3/2013");
    mvwaddstr(headerwin,5,COLS-40,"Simulation Status: Running");
    mvwaddstr(stdstats,1,midpointx, "Total Vehicles in engine:");
    mvwprintw(stdstats,1,midpointx+27, "%d",thread_args->simstats.getTotalVehicles());
    mvwaddstr(stdstats,2,2, "Average time in Engine:");
    mvwprintw(stdstats,2,27, "%0.00f s",thread_args->simstats.getAvTimeinEngine()*thread_args->sleep_time );
    mvwaddstr(stdstats,1,2, "Sim granularity: ");
    mvwprintw(stdstats,1,20,"%d s",thread_args->sleep_time);
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
    mvwprintw(stdstats,3,27, "%.00f",thread_args->simstats.getAvSpeed());
    mvwaddstr(stdstats,3,2,"Average speed in engine: ");
    mvwaddstr(stdstats,4,2,"Vehicles Completed:    Most Common Entry/Exit point:    /");
    mvwprintw(stdstats,4,20,"%d", thread_args->simstats.getRemVehi());
    mvwprintw(stdstats,4,58,"%d", thread_args->simstats.getMostCommonEntryP());
    mvwprintw(stdstats,4,63,"%d", thread_args->simstats.getMostCommonExitP());
    mvwaddstr(helpwin,1,2,"For help press 'H'.           Copyright(c) 2013 Kings College London.");
    // PREPARING PANEL TEXT
    wattron(vehiclestats, A_UNDERLINE);
    wattron(roadnodestats, A_UNDERLINE);
    wattron(trafficlstats, A_UNDERLINE);
    wattron(helpbox, A_UNDERLINE);
    mvwaddstr(helpbox, 1, midpointx-12,"Traffic Simulation System");
    mvwaddstr(helpbox,2,midpointx-8,"HELP COMMAND LIST");
    wattroff(helpbox, A_UNDERLINE);
    mvwaddstr(helpbox,3,2,"1. Set No of Vehicles ");
    mvwaddstr(helpbox,4,2,"2. Set Vehicle Type Ratio ");
    mvwaddstr(helpbox,5,2,"3. Set Driver Type Ratio ");
    mvwaddstr(helpbox,3,35,"4. Pause Simulation ");
    mvwaddstr(helpbox,4,35,"5. Change Granularity");
    mvwaddstr(helpbox,5,35,"6. Toggle Traffic Lights");
    mvwaddstr(helpbox,3,65,"H. Close this menu");
    mvwaddstr(helpbox,4,65,"Q. Quit the Simulation");
    mvwaddstr(helpbox,5,65,"P. Switch Between Vehicle/road views");

    mvwaddstr(vehiclestats,1,2,"Vehicle ID");
    mvwaddstr(vehiclestats,1,15,"Type");
    mvwaddstr(vehiclestats,1,25,"Current Speed");
    mvwaddstr(vehiclestats,1,40,"EntryP");
    mvwaddstr(vehiclestats,1,50,"ExitP");
    mvwaddstr(vehiclestats,1,60,"Path");
    mvwaddstr(vehiclestats,1,80,"Current Position in Path");
    mvwaddstr(vehiclestats,1,116,"Timer");

    mvwaddstr(roadnodestats,1,2,"RoadNode ID");
    mvwaddstr(roadnodestats,1,15,"Length");
    mvwaddstr(roadnodestats,1,30,"Maximum Speed");
    mvwaddstr(roadnodestats,1,45,"Connected RoadNodes");
    mvwaddstr(roadnodestats,1,65,"Current Vehicles in RoadNode");

    mvwaddstr(trafficlstats,1,2,"Cart-X");
    mvwaddstr(trafficlstats,1,10,"Cart-Y");
    mvwaddstr(trafficlstats,1,20,"Timer");
    mvwaddstr(trafficlstats,1,30,"State");

    wattroff(vehiclestats, A_UNDERLINE);
    wattroff(trafficlstats, A_UNDERLINE);
    wattroff(roadnodestats, A_UNDERLINE);
    updateRoadNodes(roadnodestats, thread_args);
    updateTrafficLights(trafficlstats, thread_args);
    mvwprintw(cmdin,1,2, "Command:");
    refresh();
    update_panels();
    doupdate();
    nodelay(cmdin,TRUE);
    while(!thread_args->finished) {
        
        mvwprintw(stdstats,2,27, "%0.00f",thread_args->simstats.getAvTimeinEngine()*thread_args->sleep_time);
        mvwprintw(stdstats,1,20,"%d",thread_args->sleep_time);
        mvwprintw(stdstats,3,27, "%.00f",thread_args->simstats.getAvSpeed());
        updateTrafficLights(trafficlstats, thread_args);
        mvwprintw(stdstats,2,midpointx+6, "%d",thread_args->simstats.getVehicleTypeNum(0));
        mvwprintw(stdstats,2,midpointx+17, "%d",thread_args->simstats.getVehicleTypeNum(1));
        mvwprintw(stdstats,2,midpointx+30, "%d",thread_args->simstats.getVehicleTypeNum(2));
        mvwprintw(stdstats,1,midpointx+27, "%d",thread_args->simstats.getTotalVehicles());
        mvwprintw(stdstats,3,midpointx+16,"%d",thread_args->simstats.getDriverTypeNum(0));
        mvwprintw(stdstats,3,midpointx+30,"%d",thread_args->simstats.getDriverTypeNum(1));
        mvwprintw(stdstats,3,midpointx+45,"%d",thread_args->simstats.getDriverTypeNum(2));
        mvwprintw(stdstats,4,20,"%d", thread_args->simstats.getRemVehi());
        mvwprintw(stdstats,4,58,"%d", thread_args->simstats.getMostCommonEntryP());
        mvwprintw(stdstats,4,63,"%d", thread_args->simstats.getMostCommonExitP()); 
        mvwprintw(stdstats,1,40, "%d",thread_args->tick_count);
        updateVehicles(vehiclestats, thread_args);
        updateRoadNodes(roadnodestats, thread_args);
        wrefresh(stdstats);
        

        do {

            ch = mvwgetch(cmdin,1,10);
            if (ch == '\n') break;
            if (ch == '1') {
                if (cmdbox_status == 0) {
                    hide_panel(panels[3]);
                    show_panel(panels[4]);
                    cmdbox_status = 1;
                    if (int result = maxVehicleChange(cmdbox, thread_args) == 1) {
                        hide_panel(panels[4]);
                        show_panel(panels[3]);    
                        cmdbox_status = 0;
                    }
                } else {
                    hide_panel(panels[4]);
                    show_panel(panels[3]);
                    cmdbox_status = 0;
                }
            }
            if (ch == '2') break; 
            if (ch == '3') break;
            if (ch == '4') {
                if (!thread_args->sim_paused) {
                    thread_args->sim_paused = true;
                } else {
                    thread_args->sim_paused = false;
                }
            }

            if (ch == '5') {
                if (cmdbox_status == 0) {
                    hide_panel(panels[3]);
                    show_panel(panels[4]);
                    cmdbox_status = 1;
                    if (int result = changeSimTime(cmdbox, thread_args) == 1) {
                        hide_panel(panels[4]);
                        show_panel(panels[3]);    
                        cmdbox_status = 0;
                    }
                } else {
                    hide_panel(panels[4]);
                    show_panel(panels[3]);
                    cmdbox_status = 0;
                }
            }
            if (ch == '6') ToggleLights(thread_args);
            if (ch == 'p' || ch == 'P') { // panel switch
                if (cpanel == 0) {
                    hide_panel(panels[0]);
                    show_panel(panels[1]);
                    cpanel = 1;
                } else if (cpanel == 1) {
                    hide_panel(panels[1]);
                    show_panel(panels[5]);
                    cpanel = 2;
                } else if (cpanel == 2) {
                    hide_panel(panels[5]);
                    show_panel(panels[0]);
                    cpanel = 0;
                }

            }
            if (ch == 'h' || ch == 'H') {
                if (helppanel == 0) {
                    hide_panel(panels[3]);
                    show_panel(panels[2]);
                    helppanel = 1;
                } else {
                    hide_panel(panels[2]);
                    show_panel(panels[3]);
                    helppanel = 0;
                }
            }
            if (ch == 'q' || ch == 'Q') {
                mvwaddstr(headerwin,5,COLS-40,"Simulation Status: Shutting Down");
                wrefresh(headerwin);
                thread_args->finished = true;
                sleep(2);
            }
            wrefresh(cmdin);
        
        } while (ch != ERR);
    
        wmove(cmdin,1,10);
        update_panels();
        doupdate();
        wrefresh(cmdin);
        usleep(5000);
    }   
    delwin(mainwin);
    delwin(headerwin);
    delwin(stdstats);
    delwin(vehiclestats);
    delwin(roadnodestats);
    delwin(cmdin);
    delwin(cmdbox);
    delwin(helpbox);
    delwin(helpwin);
    endwin();
    pthread_exit(NULL);   
}
