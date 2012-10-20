#include "../Include/ElevatorController.h"

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Shortest Seek Time First /////////////////////////////////

void SSTFController::control()
{
	int i, j, k, t;	 // FOR DEBUG
	Mission * ptrMission;
	vector<Mission*>::iterator iter;
	vector<Mission*>::iterator infoIter;
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

					// mission completed - function moved to class elevator-drop()
					/*
					if (elevator[i].getMission() != NULL)
					{
					    delete elevator[i].getMission();
					    elevator[i].setMissionNull();
					}
					*/
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

		// update infos for every mission in MissionList
		for(infoIter = MissionList.begin(); infoIter != MissionList.end(); infoIter++)
		{
			updateWaitingTime(*infoIter);
			updateRunTime(*infoIter);
		}
		updateAveFlow();
	}
}

void SSTFController::storeMission(Mission* ptrMission)
{
    if (ptrMission->getFrom() == ptrMission->getTo())
    {
        delete ptrMission;
        return;
    }
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionList.push_back(ptrMission);
}