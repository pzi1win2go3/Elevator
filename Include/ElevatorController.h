#include "Elevator.h"
#include "Mission.h"
#include <queue>
#include <iostream>

class ElevatorController
{
public:
	void control();
private:
	queue<Mission *> MissionQ;
	Elevator * elevator;
	int * wating;
	int compacity;
	int storey;
	int elevatorNum;


};