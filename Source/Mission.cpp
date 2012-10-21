#include "../Include/Mission.h"
#include "../Include/Time.h"

extern Time globalClock;

Mission::Mission(int initFrom, int initTo, int initPassenger, int initBornTime)
{
	from = initFrom;
	to = initTo;
	passenger = initPassenger;
	bornTime = initBornTime;
	pickedTime = 0;
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
#ifdef DEBUG
	if (pickedTime > globalClock.getTime())
	{
		cout << "error!";
		cin.get();
	}
#endif
	return pickedTime - bornTime;
}
int Mission::getRunTime(int completedTime)
{
#ifdef DEBUG
	if (completedTime-pickedTime < 0)
	{cout << "error!";
		cin.get();}
#endif
	return completedTime - pickedTime;
}
int Mission::getBornTime()
{
	return bornTime;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
