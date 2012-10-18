#ifndef MISSION_H
#define MISSION_H

#include <iostream>
using namespace std;

class Mission
{
public:
	Mission(int initFrom, int initTo, int initPassenger, int initBornTime);	// construction	
	
	void picked(int initPickedTime); // called when a mission is picked

	//////////////////////////////////////////////////////////////////
	/////////////////////////// API here /////////////////////////////	
	int getFrom();
	int getTo();
	int getPassenger();
	int getWaitingTime(int pickedTime);
	int getRunTime(int completedTime);
	int getBornTime();
	int getTakenTime();
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

private:
	int from;
	int to;
	int passenger;
	int bornTime;
	int pickedTime;
};

#endif