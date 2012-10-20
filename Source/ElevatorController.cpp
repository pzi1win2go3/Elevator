#include "../Include/ElevatorController.h"
#include <memory.h>
#include <cstdio>
#include <cstdlib>

//#define DEBUG

ElevatorController::ElevatorController(int init_capacity, int init_storey, int init_elevatorNum)
{
	capacity = init_capacity;
	storey = init_storey;
	elevatorNum = init_elevatorNum;

	maxWaitingTime = 0;
	minWaitingTime = 0;
	aveWaitingTimeCount = 0;
	aveWaitingTime = 0;
	maxRunTime = 0;
	minRunTime = 0;
	aveRunTimeCount = 0;
	aveRunTime = 0;
	aveFlow = 0;
	totalFlow = 0;

	DURATION = 10;

	elevator =  new Elevator[elevatorNum + 2];
	for(int i = 1; i <= elevatorNum; i++)
	{
		elevator[i].setId(i);
	}
	waiting = new int[storey + 2];
	memset(waiting, 0, (storey + 2) * sizeof(int));
}

void ElevatorController::show()
{
	int i,j,k;
	system("clear");
	printf("Storey          Waiting  ");
	for(i = 1; i <= elevatorNum; i++)
	{
		printf("  Elevator %d  ", i);
	}
	printf("\n");

	for(i = storey; i >= 1; i--)
	{
		printf("  %2d              %2d ", i, waiting[i]);

# ifdef DEBUG
        if (waiting[i] < 0)
            cin.get();
# endif

		for(j = 1; j <= elevatorNum; j++)
		{
			if(elevator[j].getPosition() == i)
				printf("         [%d]  ", elevator[j].getPassenger());
			else
				printf("              ");
		}
		printf("\n");
	}
}

void ElevatorController::info()
{
	printf("--Information----------------------------------\n");
	printf("	Time now:					%6ds\n", globalClock.getTime());
	printf("	Number of elevator:			%6d\n", elevatorNum);
	printf("	Max waiting time:				%6ds\n", maxWaitingTime);
	printf("	Min waiting time:				%6ds\n", minWaitingTime);
	printf("	Ave waiting time:				%6.2fs\n", aveWaitingTime);
	printf("	Max run time:				%6ds\n", maxRunTime);
	printf("	Min run time:				%6ds\n", minRunTime);
	printf("	Ave run time:  				%6.2fs\n", aveRunTime);
	printf("	Total flow number:			%6.0f pass\n", totalFlow);
	printf("	Ave flow number:				%6.2f pass/s\n", aveFlow);
	printf("-----------------------------------------------\n");
}

//////////////////////////////////////////////////////////////////
////////////////////// Time Info Update //////////////////////////
void ElevatorController::updateWaitingTime(Mission * ptrMission)
{
	ElevatorController::updateMaxWaitingTime(ptrMission);
	ElevatorController::updateAveWaitingTime(ptrMission);
	ElevatorController::updateMinWaitingTime(ptrMission);
}

void ElevatorController::updateRunTime(Mission * ptrMission)
{
	ElevatorController::updateMaxRunTime(ptrMission);
	ElevatorController::updateAveRunTime(ptrMission);
	ElevatorController::updateMinRunTime(ptrMission);
}

void ElevatorController::updateMaxWaitingTime(Mission * ptrMission)
{
	if(ptrMission->getWaitingTime(globalClock.getTime()) > maxWaitingTime)
		maxWaitingTime = ptrMission->getWaitingTime(globalClock.getTime());
}

void ElevatorController::updateMinWaitingTime(Mission * ptrMission)
{
	if(ptrMission->getWaitingTime(globalClock.getTime()) < minWaitingTime)
		minWaitingTime = ptrMission->getWaitingTime(globalClock.getTime());
}

void ElevatorController::updateAveWaitingTime(Mission * ptrMission)
{
	aveWaitingTime = (ptrMission->getWaitingTime(globalClock.getTime()) + aveWaitingTime * (double)aveWaitingTimeCount++) / (double)aveWaitingTimeCount;
}

void ElevatorController::updateMaxRunTime(Mission * ptrMission)
{
	if(ptrMission->getRunTime(globalClock.getTime()) > maxRunTime)
		maxRunTime = ptrMission->getRunTime(globalClock.getTime());
}

void ElevatorController::updateMinRunTime(Mission * ptrMission)
{
	if(ptrMission->getRunTime(globalClock.getTime()) < minRunTime)
		minRunTime = ptrMission->getRunTime(globalClock.getTime());
}

void ElevatorController::updateAveRunTime(Mission * ptrMission)
{
	aveRunTime = (ptrMission->getRunTime(globalClock.getTime()) + aveRunTime * (double)aveRunTimeCount++) / (double)aveRunTimeCount;
}

//////////////////////////////////////////////////////////////////
////////////////////// Flow Info Update //////////////////////////
void ElevatorController::updateAveFlow()
{
	for(int i = 1; i <= elevatorNum; i++)
	{
		totalFlow += elevator[i].getPassenger();
	}
	aveFlow = totalFlow / (double)globalClock.getTime();
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////