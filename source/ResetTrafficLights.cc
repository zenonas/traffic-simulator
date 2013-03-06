#include "th_structs.h"
#include "map.h"
#include <vector>
#include <iostream>

using namespace std;



void ResetTrafficLights(void *arguments)
{
	struct thread_arguments *thread_args;
	thread_args = (struct thread_arguments *)arguments;
	thread_args->CurrentTimer=0;
}

void ToggleLights(void *arguments, int CurrentTimer)
{
	
	struct thread_arguments *thread_args;
	thread_args = (struct thread_arguments *)arguments;

	for(int i=0; i<thread_args->mymap.trafficlights.size(); i++)
	{
			if (thread_args->mymap.trafficlights[i].getState() == 1)
			{
				thread_args->mymap.trafficlights[i].setState(0);
				thread_args->CurrentTimer=0;
				thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()/2);
			}
			else
			{

				thread_args->mymap.trafficlights[i].setState(1);
				thread_args->CurrentTimer=0;
				thread_args->mymap.trafficlights[i].setTimer(thread_args->mymap.trafficlights[i].getTimer()*2);
			}
	}
}