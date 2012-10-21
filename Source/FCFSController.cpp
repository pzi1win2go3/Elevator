#include "../Include/ElevatorController.h"

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

				// break if no mission
				if (MissionQ.empty())
					break;

				// assign if elevator is free
				if(elevator[i].getStatus() == 0)
				{
					ptrMission = MissionQ.front();
					MissionQ.pop();

					// when elevator is large enough
					if(ptrMission->getPassenger() <= capacity)
					{
						elevator[i].takeMission(ptrMission);
						elevator[i].setStatus(-1);
					}
					// when elevator can not hold all the people
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

					// update info
					updateRunTime(elevator[i].getMission());

					elevator[i].drop();				
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

				// update info
				updateWaitingTime(ptrMission);

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
		updateAveFlow();
	}
}

void FCFSController::storeMission(Mission * ptrMission)
{
	// make sure mission is reasonable
  if (ptrMission->getFrom() == ptrMission->getTo() || ptrMission->getPassenger() <= 0)
  {
      delete ptrMission;
      return;
  }
	waiting[ptrMission->getFrom()] += ptrMission->getPassenger();
	MissionQ.push(ptrMission);
}
