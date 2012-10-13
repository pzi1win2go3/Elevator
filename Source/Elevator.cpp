

Elevator::Elevator()
{
	cur_mission = NULL;
	missionNum = 0;
	position = 0;
	destination = 0;
	status = 0;
	passenger = 0;
	isEmpty = true;
}

void Elevator::setId(int init_id)
{
	id = init_id;
	return;
}

void Elevator::takeMission(Mission * mission)
{
	cur_mission = mission;
	missionNum++;
}

void Elevator::move(int order)
{
	destination = order;
	if(position > destination)
	{
		position--;
	}
	if(position < destination)
	{
		position++;
	}
	// take 1 unit time
}

void Elevator::pick()
{
	passenger += cur_mission.passenger
	missionNum++;
	// take 1 unit time
}

void Elevator::drop()
{
	passenger -= cur_mission.passenger
	missionNum--;
	// take 1 unit time
}

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
int Elevator::getPassengers()
{
	return passenger;
}
bool Elevator::isEmpty()
{
	return empty;
}

Mission* Elevator::getMission()
{
	return cur_mission;
}

void Elevator::setStatus(int newStatus)
{
	status = newStatus;
	return;
}

void Elevator::setMissionNull()
{
	cur_mission = NULL;
	return;
}

