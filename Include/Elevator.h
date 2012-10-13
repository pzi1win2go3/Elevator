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
	void open();
	void close();
	void action();

private:
	Mission* cur_mission;
	int missionNum;			
	int position;
	int destination;
	int status;
	int passenger;
	bool isEmpty;
	int id;

};

#endif