#ifndef MISSION_H
#define MISSION_H

#include <iostream>
using namespace std;

class Mission
{
public:
	Mission(int initFrom, int initTo, int initPassenger, int initLifeTime);	// construction	
	
	//////////////////////////////////////////////////////////////////
	/////////////////////////// API here /////////////////////////////	
	int getFrom();
	int getTo();
	int getPassenger();
	int getLifeTime(int completedTime);
	int getBornTime();
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

private:
	int from;
	int to;
	int passenger;
	int bornTime;
};

#endif