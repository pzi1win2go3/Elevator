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

	maxWaitingTime = 0;
	aveWaitingTimeCount = 0;
	aveWaitingTime = 0;
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

void ElevatorController::info()
{
	printf("--Information----------------------------------\n");
	printf("	Max waiting time:				%6d\n", maxWaitingTime);
	printf("	Ave waiting time:  			%6.2f\n", aveWaitingTime);
	printf("	Ave flow number:				%6.2f\n", aveFlow);
	printf("-----------------------------------------------\n");
}

void ElevatorController::updateMaxWaitingTime(Mission * ptrMission)
{
	if(ptrMission->getLifeTime(globalClock.getTime()) > maxWaitingTime)
		maxWaitingTime = ptrMission->getLifeTime(globalClock.getTime());
}

void ElevatorController::updateAveWaitingTime(Mission * ptrMission)
{
	aveWaitingTime = (ptrMission->getLifeTime(globalClock.getTime()) + aveWaitingTime * (double)aveWaitingTimeCount++) / (double)aveWaitingTimeCount;
}

void ElevatorController::updateAveFlow()
{ 
	for(int i = 1; i <= elevatorNum; i++)
	{
		totalFlow += elevator[i].getPassenger();
	}
	aveFlow = totalFlow / (double)globalClock.getTime();
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// First Come First Serve ///////////////////////////////

void FCFSController::control()
{
	int i,j,k,t;	 // FOR DEBUG
	Mission * ptrMission;

	for(t = 0; t < DURATION; t++)
	{
		show();
		info();
		globalClock.tick();
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
						Mission * temp = new Mission (ptrMission->getFrom(), ptrMission->getTo(), ptrMission->getPassenger() - capacity, ptrMission->getBornTime());
						Mission * toTake = new Mission (ptrMission->getFrom(), ptrMission->getTo(), capacity, ptrMission->getBornTime());

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
			// when elevator has no mission taken and to be taken
			if(elevator[i].getStatus() == 0)												
				continue;

			// when elevator has mission taken
			else if(elevator[i].getStatus() == 1)										
			{
				ptrMission = elevator[i].getMission();

				//reach
				if(elevator[i].getPosition() == ptrMission->getTo())
				{
					elevator[i].setStatus(0);
					elevator[i].drop();

					// mission completed
					if(elevator[i].getMission() != NULL)	
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

			// when elevator has mission to be taken
			else if(elevator[i].getStatus() == -1)									
			{
				ptrMission = elevator[i].getMission();

				//reach
				if(elevator[i].getPosition() == ptrMission->getFrom())
				{

					// update info
					updateMaxWaitingTime(ptrMission);
					updateAveWaitingTime(ptrMission);

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
		updateAveFlow();
	}
}

void FCFSController::storeMission(Mission * ptrMission)
{
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionQ.push(ptrMission);
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Shortest Seek Time First /////////////////////////////////

void SSTFController::control()
{
	int i,j,k,t;	 // FOR DEBUG
	Mission * ptrMission;
	vector<Mission*>::iterator iter;
	vector<Mission*>::iterator SSTiter;
	int SSTime, subscript = 0;

	for(t = 0; t < DURATION; t++)
	{
		show();
		info();
		globalClock.tick();
		sleep(1);


		// assign mission
		for(i = 1; i <= elevatorNum; i++)
		{
			if(elevator[i].getStatus() != 0)
				continue;
			if(MissionList.empty())
				break;

			// find the shortest seek	time
			else 	
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
				Mission * temp = new Mission (ptrMission->getFrom(), ptrMission->getTo(), ptrMission->getPassenger() - capacity, ptrMission->getBornTime());
				Mission * toTake = new Mission (ptrMission->getFrom(), ptrMission->getTo(), capacity, ptrMission->getBornTime());
				
				elevator[i].takeMission(toTake);
				elevator[i].setStatus(-1);
				MissionList.push_back(temp);
			}


		}



		// elevator run
		for(i = 1; i <= elevatorNum; i++)
		{
			// when elevator has no mission taken and to be taken
			if(elevator[i].getStatus() == 0)												
				continue;

			// when elevator has mission taken
			else if(elevator[i].getStatus() == 1)										
			{
				ptrMission = elevator[i].getMission();

				//reach
				if(elevator[i].getPosition() == ptrMission->getTo())
				{
					elevator[i].setStatus(0);
					elevator[i].drop();

					// mission completed
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

			// when elevator has mission to be taken
			else if(elevator[i].getStatus() == -1)									
			{
				ptrMission = elevator[i].getMission();

				//reach
				if(elevator[i].getPosition() == ptrMission->getFrom())
				{

					// update info
					updateMaxWaitingTime(ptrMission);
					updateAveWaitingTime(ptrMission);

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
		updateAveFlow();
	}
}

void SSTFController::storeMission(Mission* ptrMission)
{
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionList.push_back(ptrMission);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

