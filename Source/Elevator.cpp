#include "../Include/Elevator.h"

extern Time globalClock;

Elevator::Elevator()
{
	cur_mission = sec_mission= thd_mission= NULL;
	missionNum = 0;
	position = 1;
	destination = 0;
	status = 0;
	passenger = 0;
	empty = true;;
}

void Elevator::setId(int init_id)
{
	id = init_id;
	return;
}

void Elevator::takeMission(Mission * mission)
{
	missionNum++;

	if (missionNum == 1)
        cur_mission = mission;
    else if (missionNum == 2)
        sec_mission = mission;
    else
        thd_mission = mission;

}

void Elevator::move(int order)
{
	destination = order;

	// go down
	if(position > destination)
	{
		position--;
	}

	// go up
	if(position < destination)
	{
		position++;
	}
}

void Elevator::pick(int num)
{
	// pick the first mission
	if (num == 1)
	{
		passenger += cur_mission->getPassenger();
		cur_mission->picked(globalClock.getTime());
	}

	// pick the second mission, if exists
	else if (num == 2)
	{
		passenger += sec_mission->getPassenger();
		sec_mission->picked(globalClock.getTime());
	}

	// pick the third mission, if exists
	else
	{
		passenger += thd_mission->getPassenger();
		thd_mission->picked(globalClock.getTime());
	}
}

void Elevator::drop(int num)
{
	// drop the first mission
	if (num == 1)
	{
		passenger -= cur_mission->getPassenger();
		delete cur_mission;
		cur_mission = sec_mission;
		sec_mission = thd_mission;
		thd_mission = NULL;
	}

	// drop the second mission, if exists
	else if (num == 2)
	{
		passenger -= sec_mission->getPassenger();
		delete sec_mission;
		sec_mission = thd_mission;
		thd_mission = NULL;
	}

	// drop the third mission, if exists
	else
	{
		passenger -= thd_mission->getPassenger();
		delete thd_mission;
		thd_mission = NULL;
	}
	missionNum--;
}

void Elevator::setStatus(int newStatus)
{
	status = newStatus;
	return;
}

void Elevator::setPosition(int newPosition)
{
	position = newPosition;
}

//////////////////////////////////////////////////////////////////
/////////////////////////// API here /////////////////////////////
int Elevator::getMissionNum()
{
	return missionNum;
}
int Elevator::getPosition()
{
	return position;
}
int Elevator::getDestination()
{
	return destination;
}
int Elevator::getStatus()
{
	return status;
}
int Elevator::getPassenger()
{
	return passenger;
}
bool Elevator::isEmpty()
{
	return empty;
}
Mission* Elevator::getMission(int num)
{
	if  (num == 1)
		return cur_mission;
	else if (num == 2)
		return sec_mission;
	else
		return thd_mission;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


