#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "Mission.h"
#include "Time.h"
using namespace std;

class Elevator
{
public:
	Elevator();                   // construction

	void takeMission(Mission *);  // called when a mission is assigned to this elevator

	void move(int order);					// move to order

	void pick(int num = 1);				// reach storey where missions are and pick missions (totally num missions, and num default as 1)

	void drop (int num = 1);			// called when a mission is completed, to change mission ptrs of elevator and free memory

	void setId(int);
	void setStatus(int);
	void setPosition(int);
	void setMissionNull(int num = 1);

	//////////////////////////////////////////////////////////////////
	/////////////////////////// API here /////////////////////////////
	int getMissionNum();
	int getPosition();
	int getDestination();
	int getStatus();
	int getPassenger();
	bool isEmpty();
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

	int status; 									// for FCFS: 0:free 1:running -1:to take mission
                                // for SSTF: 0:free 1:running -1:to take mission
                                // for SCAN: 1:go up -1:go down
                                // for LOOK: 1:go up -1:go down

	int passenger;
	bool empty;
	int id;

};

#endif
