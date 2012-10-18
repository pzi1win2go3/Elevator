#include "../Include/Mission.h"

Mission::Mission(int initFrom, int initTo, int initPassenger, int initBornTime)
{
	from = initFrom;
	to = initTo;
	passenger = initPassenger;
	bornTime = initBornTime;
}

void Mission::picked(int initPickedTime)
{
	pickedTime = initPickedTime;
}
//////////////////////////////////////////////////////////////////
/////////////////////////// API here /////////////////////////////
int Mission::getFrom()
{
	return from;
}
int Mission::getTo()
{
	return to;
}
int Mission::getPassenger()
{
	return passenger;
}
int Mission::getWaitingTime(int pickedTime)
{
	return pickedTime - bornTime;
}
int Mission::getRunTime(int completedTime)
{
	return completedTime - pickedTime;
} 
int Mission::getBornTime()
{
	return bornTime;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
