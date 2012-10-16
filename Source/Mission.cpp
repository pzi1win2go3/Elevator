#include "../Include/Mission.h"

Mission::Mission(int initFrom, int initTo, int initPassenger, int initBornTime)
{
	from = initFrom;
	to = initTo;
	passenger = initPassenger;
	bornTime = initBornTime;
}

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
int Mission::getLifeTime(int completedTime)
{
	return completedTime - bornTime;
} 
int Mission::getBornTime()
{
	return bornTime;
}
