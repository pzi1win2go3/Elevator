Elevator(int initId)
{
	cur_mission = NULL;
	missionNum = 0;
	position = 0;
	destination = 0;
	status = 0;
	passenger = 0;
	isEmpty = true;
	id = initId;
}

void takeMission(Mission * mission)
{
	cur_mission = mission;
	missionNum++;
}

void move()
{
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

void pick()
{
	passenger += cur_mission.passenger
	missionNum++;
	// take 1 unit time
}

void drop()
{
	passenger -= cur_mission.passenger
	missionNum--;
	// take 1 unit time
}

int getMissionNum()
{
	return missionNum;
}
int getPosition()
{
	return position;
}
int getDestination()
{
	return destination;
}
int getStatus()
{
	return status;
}
int getPassengers()
{
	return passenger;
}
bool isEmpty()
{
	return empty;
}