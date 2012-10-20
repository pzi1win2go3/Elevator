#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "Mission.h"
#include "Time.h"
using namespace std;

class Elevator
{
public:
	Elevator();								// construction

	void takeMission(Mission *);
	void complete();
	void move(int order);
	//void pick();
	void pick(int num = 1);
	//void drop();
	void drop (int num = 1);

	void setId(int);
	void setStatus(int);
	void setPosition(int);
	//void setMissionNull();		// set cur_mission to NULL
	void setMissionNull(int num = 1);

	//////////////////////////////////////////////////////////////////
	/////////////////////////// API here /////////////////////////////
	int getMissionNum();
	int getPosition();
	int getDestination();
	int getStatus();
	int getPassenger();
	bool isEmpty();
	//Mission* getMission();
	Mission* getMission(int num = 1);
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

private:
	Mission* cur_mission;
	Mission* sec_mission;
	Mission* thd_mission;
	int missionNum;
	int position;
	int destination;
	int status;
	int passenger;
	bool empty;
	int id;

};

#endif
