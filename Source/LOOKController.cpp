# include  "../Include/ElevatorController.h"
# include <memory.h>

LOOKController::LOOKController(int init_capacity, int init_storey, int init_elevatorNum)
:ElevatorController(init_capacity, init_storey, init_elevatorNum)
{
	int i,j,k;
	for (i = 1; i  <= init_elevatorNum; i++)
	{
		elevator[i].setPosition(i % storey +1);
		elevator[i].setStatus(1);
	}
}

void LOOKController::control()
{
	int i, j, k, t;
	Mission * ptrMission;
	vector<Mission *>::iterator infoIter;

	for(t = 0; t < DURATION; t++)
	{
		show();
		info();
		globalClock.tick();
		sleep(1);

		bool * stop = new bool[elevatorNum+1];
		memset(stop,0,(elevatorNum+1)*sizeof(bool));

	  for (i = 1 ; i <= elevatorNum; i++)
	  {
	  	vector<Mission*>::iterator iter;
	    if (elevator[i].getPosition() == 1)
	    {
	        elevator[i].setStatus(1);
	    }
	    else if (elevator[i].getPosition() == storey)
	    {
	        elevator[i].setStatus(-1);
	    }
	    if (elevator[i].getStatus() == 1 && elevator[i].getMissionNum() == 0)
	    {
	    	elevator[i].setStatus(-1);
	    	for (iter = MissionList.begin();iter!=MissionList.end();++iter)
	    	{
	    		if ((*iter)->getFrom() > elevator[i].getPosition())
	    			elevator[i].setStatus(1);
	    	}
	    }
	    else if (elevator[i].getStatus() == -1 && elevator[i].getMissionNum() == 0)
	    {
	    	elevator[i].setStatus(1);
	    	for (iter = MissionList.begin();iter!=MissionList.end();++iter)
	    	{
	    		if ((*iter)->getFrom() < elevator[i].getPosition())
	    			elevator[i].setStatus(-1);
	    	}
	    }
	  }


		for (i = 1; i <= elevatorNum; i++)
				{
					if (elevator[i].getMissionNum() >= 1 && elevator[i].getMission(1)->getTo() == elevator[i].getPosition())
					{
					  stop[i] = true;
						elevator[i].drop(1);
					}
					if (elevator[i].getMissionNum() >= 2 && elevator[i].getMission(2)->getTo() == elevator[i].getPosition())
					{
						stop[i] = true;
						elevator[i].drop(2);
					}
					if (elevator[i].getMissionNum() >= 3 && elevator[i].getMission(3)->getTo() == elevator[i].getPosition())
					{
					  stop[i] = true;
						elevator[i].drop(3);
					}
				}

				for(i = 1; i <= elevatorNum; i++)
				{
					vector<Mission*>::iterator iter;
					for (iter = MissionList.begin(); iter != MissionList.end();)
					{
					  ptrMission = *iter;
					  if (ptrMission -> getFrom() == elevator[i].getPosition() && elevator[i].getMissionNum() < 3 &&(ptrMission->getTo() - ptrMission->getFrom())*elevator[i].getStatus() >= 0)
					  {
				    	if (ptrMission->getPassenger()+elevator[i].getPassenger() <= capacity)     // same direction
				    	{
				        elevator[i].takeMission(ptrMission );
						  	elevator[i].pick(elevator[i].getMissionNum());
		         	  waiting[ptrMission ->getFrom()] -= ptrMission ->getPassenger();
								iter = MissionList.erase(iter);
				  	  }
				   	 	else
				  	  {
					        int max = capacity-elevator[i].getPassenger();
					        Mission* toTake = new Mission(ptrMission->getFrom(),ptrMission->getTo(),max,ptrMission->getBornTime());
					        Mission* left = new Mission(ptrMission->getFrom(),ptrMission->getTo(),ptrMission->getPassenger()-max,ptrMission->getBornTime());
					        elevator[i].takeMission(toTake);
		 							elevator[i].pick(elevator[i].getMissionNum());
		              waiting[ptrMission ->getFrom()] -= toTake ->getPassenger();
		             	iter = MissionList.erase(iter);
		              MissionList.push_back(left);
				  	  }
						}
						else
						{
						  ++iter;
						}
					}
				}

			    //show();
			    // sleep(1);
				for (i = 1 ; i <= elevatorNum; i++)
				{
				  if (stop[i] == true)
			      continue;

					if (elevator[i].getStatus() == 1)
						elevator[i].move(storey);
					else
						elevator[i].move(1);
				}

				delete []stop;

				// update infos for every mission in MissionList
				for(infoIter = MissionList.begin(); infoIter != MissionList.end(); infoIter++)
				{
					updateWaitingTime(*infoIter);
					updateRunTime(*infoIter);
				}
				updateAveFlow();
	}
}



void LOOKController::storeMission(Mission * ptrMission)
{
    if (ptrMission->getFrom() == ptrMission->getTo())
    {
        delete ptrMission;
        return;
    }
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionList.push_back(ptrMission);
}
