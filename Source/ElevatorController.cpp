#include "../Include/ElevatorController.h"
#include <memory.h>
#include <cstdio>
#include <cstdlib>

#define DEBUG

ElevatorController::ElevatorController(int init_capacity, int init_storey, int init_elevatorNum)
{
	capacity = init_capacity;
	storey = init_storey;
	elevatorNum = init_elevatorNum;
	elevator =  new Elevator[elevatorNum + 2];
	for(int i = 1; i <= elevatorNum; i++)
	{
		elevator[i].setId(i);
	}
	waiting = new int[storey + 2];
	memset(waiting, 0, (storey + 2) * sizeof(int));
}

void FCFSController ::control()
{
	int i,j,k,t;	 // FOR DEBUG
	Mission * ptrMission;

	for(t = 0; t < 5; t++)
	{
		show();
		sleep(1);

		//   assign mission
		if( ! MissionQ.empty() )
		{
			for(i = 1; i <= elevatorNum; i++)
			{
				if (MissionQ.empty())
					break;
				if(elevator[i].getStatus() == 0)
				{
					ptrMission = MissionQ.front();
					MissionQ.pop();
					if(ptrMission->getPassenger() <= capacity)
					{
						elevator[i].takeMission(ptrMission);
						elevator[i].setStatus(-1);

					}
					else
					{
						Mission * temp = new Mission (ptrMission->getFrom(), ptrMission->getTo(), ptrMission->getPassenger() - capacity);
						Mission * toTake = new Mission (ptrMission->getFrom(), ptrMission->getTo(), capacity);
						elevator[i].takeMission(toTake);
						elevator[i].setStatus(-1);
						MissionQ.push(temp);
					}
				}

			}
		}


		// elevator run
		for(i = 1; i <= elevatorNum; i++)
		{
			if(elevator[i].getStatus() == 0)												// when elevator has no mission taken and to be taken
				continue;

			else if(elevator[i].getStatus() == 1)										// when elevator has mission taken
			{
				ptrMission = elevator[i].getMission();
				if(elevator[i].getPosition() == ptrMission->getTo())
				{
					//reach
					elevator[i].setStatus(0);
					elevator[i].drop();
					if (elevator[i].getMission() != NULL)
					{
					    delete elevator[i].getMission();
					    elevator[i].setMissionNull();
					}
				}
				else
				{
					elevator[i].move(ptrMission->getTo());
				}
			}

			else if(elevator[i].getStatus() == -1)									// when elevator has mission to be taken
			{
				ptrMission = elevator[i].getMission();
				if(elevator[i].getPosition() == ptrMission->getFrom())
				{
					//reach
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

void FCFSController ::storeMission(Mission * ptrMission)
{
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionQ.push(ptrMission);
}

void ElevatorController::show()
{
	int i,j,k;
	system("clear");
	printf("Storey                    Waiting");
	for(i = 1; i <= elevatorNum; i++)
	{
		printf("  Elevator %d  ", i);
	}
	printf("\n");



	for(i = storey; i >= 1; i--)
	{
		if (i < 10)
			printf("%d                           %d", i, waiting[i]);
		else
			printf("%d                          %d", i, waiting[i]);
# ifdef DEBUG
        if (waiting[i] < 0)
            cin.get();
# endif

		for(j = 1; j <= elevatorNum; j++)
		{
			if(elevator[j].getPosition() == i)
				printf("      [%d]      ", elevator[j].getPassenger());
			else
				printf("               ");


		}
		printf("\n");
	}
}

void SSTFController::storeMission (Mission* ptrMission)
{
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionList.push_back(ptrMission);
}

void SSTFController::control()
{
	int i,j,k,t;	 // FOR DEBUG
	Mission * ptrMission;
	vector<Mission*> ::iterator iter ;
	vector<Mission*>::iterator SSTiter;
	int SSTime, subscript = 0;

	for(t = 0; t < 5; t++)
	{
		show();
		sleep(1);


		//   assign mission
		for(i = 1; i <= elevatorNum; i++)
		{
			if  (elevator[i].getStatus() != 0)
				continue;
			if (MissionList.empty())
				break;
			else 	// find the shortest seek	 time
			{
				SSTime = abs(MissionList[0]->getFrom() - elevator[i].getPosition());
				iter = MissionList.begin();
				SSTiter = iter;
				for (iter = MissionList.begin() , k = 0; iter != MissionList.end(); ++iter,++k)
				{
					int timeDiff = abs(MissionList[k]->getFrom() - elevator[i].getPosition());
					if (timeDiff < SSTime)
					{
						SSTime = timeDiff;
						SSTiter = iter;
						subscript = k;
					}
				}
			}

			ptrMission = *SSTiter;
			MissionList.erase(SSTiter);
			if(ptrMission->getPassenger() <= capacity)
			{
				elevator[i].takeMission(ptrMission );
				elevator[i].setStatus(-1);

			}
			else
			{
				Mission * temp = new Mission (ptrMission->getFrom(), ptrMission->getTo(), ptrMission->getPassenger() - capacity);
				Mission * toTake = new Mission (ptrMission->getFrom(), ptrMission->getTo(), capacity);
				elevator[i].takeMission(toTake);
				elevator[i].setStatus(-1);
				MissionList.push_back(temp);
			}


		}



		// elevator run
		for(i = 1; i <= elevatorNum; i++)
		{
			if(elevator[i].getStatus() == 0)												// when elevator has no mission taken and to be taken
				continue;

			else if(elevator[i].getStatus() == 1)										// when elevator has mission taken
			{
				ptrMission = elevator[i].getMission();
				if(elevator[i].getPosition() == ptrMission->getTo())
				{
					//reach
					elevator[i].setStatus(0);
					elevator[i].drop();
					if (elevator[i].getMission() != NULL)
					{
					    delete elevator[i].getMission();
					    elevator[i].setMissionNull();
					}

				}
				else
				{
					elevator[i].move(ptrMission->getTo());
				}
			}

			else if(elevator[i].getStatus() == -1)									// when elevator has mission to be taken
			{
				ptrMission = elevator[i].getMission();
				if(elevator[i].getPosition() == ptrMission->getFrom())
				{
					//reach
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


