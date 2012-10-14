#include "Elevator.h"
#include "Mission.h"
#include <queue>
#include <iostream>

class ElevatorController
{
public:
	ElevatorController(int init_capacity, int init_storey, int init_elevatorNum);
	void control();
	void show();
	void storeMission(Mission *);
private:
	queue<Mission *> MissionQ;
	Elevator * elevator;
	int * waiting;
	int capacity;
	int storey;
	int elevatorNum;


};