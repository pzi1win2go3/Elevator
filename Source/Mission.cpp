#include "../Include/Mission.h"

Mission::Mission(int initFrom, int initTo, int initPassenger, int initBornTime)
{
	from = initFrom;
	to = initTo;
	passenger = initPassenger;
	bornTime = initBornTime;
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
int Mission::getLifeTime(int assignedTime)
{
	return assignedTime - bornTime;
} 
int Mission::getBornTime()
{
	return bornTime;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
