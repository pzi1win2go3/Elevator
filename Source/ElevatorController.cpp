#include "ElevatorController.h"
#include <memory.h>
#include <cstdio>

ElevatorController::ElevatorController (int inti_compacity,  int init_storey, int init_elevatorNum)
{
	compaciy = inti_compacity;
	storey = init_storey;
	elevatorNum = init_elevatorNum;
	elevator =  new Elevator[elevatorNum+2];
	waiting = new int[storey+2];
	memset(wating, 0, (storey+2)*sizeof(int));
}

void ElevatorController::control ( )
{
	int i,j,k,t;	 // FOR DEBUG
	Mission * ptrMission;

	for (t = 0; t < 5; t++)
	{
		show();

		//   assign mission
		if ( ! MissionQ.empty() )
		{
			for (i = 1; i <= elevatorNum; i++)
			{
				if  (elevator[i].getStatus() == 0)
				{
					ptrMission = MissionQ.front();
					MissionQ.pop();
					if (ptrMission->getPassenger() <= compaciy)
					{
						elevator[i].takeMission(ptrMission);
					}
					else
					{
						Mission * temp = new Mission (ptrMission->getFrom(), ptrMission->getTo, ptrMission->getPassenger-compacity);
						elevator[i].takeMission(ptrMission);
						MissionQ.push(temp);
					}
				}

			}
		}	


		// elevator run
		for  (i = 1; i <= elevatorNum; i++)
		{
			if (elevator[i].getStatus() == 0)
				continue;

			else if (elevator[i].getStatus() == 1)
			{
				ptrMission = elevator[i].getMission();
				if (elevator[i].getPosition() == ptrMission->getTo())
				{
					//reach
					elevator[i].open();
					elevator[i].close();
					elevator[i].setStatus(0);
					elevator[i].drop();
					delete elevator[i].getMission();
					elevator[i].setMissionNull();
				}
				else
				{
					elevator[i].move(ptrMission->getTo());
				}
			}
			else if (elevator[i].getStatus() == -1)
			{
				ptrMission = elevator[i].getMission();
				if (elevator[i].getPosition() == ptrMission->getFrom())
				{
					//reach
					elevator[i].open();
					elevator[i].close();
					elevator[i].setStatus(1);
					waiting[ptrMission->getFrom()] -= ptrMission->getPassenger();
					elevator[i].pick();
				}
				else
				{
					elevator[i].move(ptrMission->getFrom());
				}

			}

		}
	}
}

void ElevatorController::storeMission(Mission * ptrMission)
{
	waiting[ptrMission->getFrom] += ptrMission->getPassenger();
	MissionQ.push(ptrMission);
}

void ElevatorController::show()
{
	int i,j,k;
	printf("Storey                        Waiting");
	for (i = 1; i  <= elevatorNum; i++)
	{
		printf("  Elevator %d  ", i);
	}
	printf ("\n");


	
	for (i = storey; i >= 1; i--)
	{
		printf("%d                           %d", i, waiting[i]);
		for (j = 1; j <= elevatorNum; j++)
		{
			if (elevator[j].getPosition() == i)
				printf("      [%d]      ", elevator[j].getPassenger());
			else
				printf("                       ");
		}
		printf("\n");
	}
}

