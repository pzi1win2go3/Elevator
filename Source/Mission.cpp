#include "../Include/Mission.h"

Mission::Mission(int initFrom, int initTo, int initPassenger)
{
	from = initFrom;
	to = initTo;
	passenger = initPassenger;
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
