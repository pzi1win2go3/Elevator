#include "Elevator.h"
#include "Mission.h"
#include <queue>
#include <iostream>

class ElevatorController
{
public:
	ElevatorController(int inti_compacity, int init_storey, int init_elevatorNum);
	void control();
	void show();
private:
	queue<Mission *> MissionQ;
	Elevator * elevator;
	int * wating;
	int compacity;
	int storey;
	int elevatorNum;


};