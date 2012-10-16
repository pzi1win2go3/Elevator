#include "../Include/Time.h"

Time::Time()
{
	time = 1;
}

void Time::tick()
{
	time++;
}

void Time::reset()
{
	time = 0;
}

int Time::getTime()
{
	return time;
}