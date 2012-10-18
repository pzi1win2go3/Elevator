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
	void pick();
	void drop();

	void setId(int);
	void setStatus(int);
	void setMissionNull();		// set cur_mission to NULL

	//////////////////////////////////////////////////////////////////
	/////////////////////////// API here /////////////////////////////
	int getMissionNum();
	int getPosition();
	int getDestination();
	int getStatus();
	int getPassenger();
	bool isEmpty();
	Mission* getMission();
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

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