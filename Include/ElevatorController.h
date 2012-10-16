#include "Elevator.h"
#include "Mission.h"
#include <queue>
#include <iostream>
#include <cmath>

class ElevatorController
{
public:
	ElevatorController(int init_capacity, int init_storey, int init_elevatorNum);
	void show();
	virtual void control() = 0;
	virtual void storeMission(Mission *) = 0;
private:
	Elevator * elevator;
	int * waiting;
	int capacity;
	int storey;
	int elevatorNum;


};

class FCFSController : public ElevatorController // First Come First Served
{
public:
	 FCFSController (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(int init_capacity, int init_storey, int init_elevatorNum){};
	void control();
	void storeMission(Mission *);
private:
	queue <Mission *> MissionQ;
};

class SSTFController: public ElevatorController // Shortest Seek Time First
{
public:
	SSTFController  (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(int init_capacity, int init_storey, int init_elevatorNum){};
	 void control();
	void storeMission(Mission *);
private:
	vector<Mission *>  MissionList;

}