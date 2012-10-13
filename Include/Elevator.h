#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "Mission.h"
using namespace std;

class Elevator
{
public:
	Elevator (int initId);				
	
	void takeMission(Mission *);
	void complete();
	void move();
	void pick();
	void drop();

	int getMissionNum();
	int getPosition();
	int getDestination();
	int getStatus();
	int getPassenger();
	bool isEmpty();
	Mission* getMission();

	void setStatus();
	void setMissionNull();		// set cur_mission to NULL

private:
	Mission* cur_mission;
	int missionNum;			
	int position;
	int destination;
	int status;
	int passenger;
	bool empty;
	int id;

};

#endif