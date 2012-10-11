# include <iostream>
# include "Mission.h"
using namespace std;

# ifndef ELEVATOR_H
# define ELEVATOR_H

class Elevator
{
public:
	Elevator ( );				// undesigned
	void takeMission(Mission *);
	void move();
private:
	Mission* mission;
	int missionNum;			// �Ľ��㷨ʱʹ��
	int position;
	int status;
	int passenger;
	bool isEmpty;

};

# endif