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
	int missionNum;			// 改进算法时使用
	int position;
	int status;
	int passenger;
	bool isEmpty;

};

# endif