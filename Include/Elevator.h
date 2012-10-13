#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "Mission.h"
using namespace std;

class Elevator
{
public:
	Elevator ( );				// undesigned
	void takeMission(Mission *);
	void move();
	void action();
	void complete();
	void open();
	void close();
private:
	Mission* mission;
	int missionNum;			// �Ľ��㷨ʱʹ��
	int position;
	int status;
	int passenger;
	bool isEmpty;
	int id;

};

#endif