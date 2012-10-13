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

void open()
{
	// take 1 unit time
}

void cloes()
{
	// take 1 unit time
}