#include "Elevator.h"
#include "Mission.h"
#include "Time.h"
#include <queue>
#include <iostream>
#include <cmath>

class ElevatorController
{
public:
	ElevatorController(int init_capacity, int init_storey, int init_elevatorNum);
	void show();
	void info();

	void updateMaxWaitingTime(Mission *); // called when a mission taken
	void updateAveWaitingTime(Mission *);

	void updateAveFlow(); // called when every 1 unit time

	virtual void control() = 0;
	virtual void storeMission(Mission *) = 0;

		Time globalClock;
		
protected:
	Elevator * elevator;
	int * waiting;
	Mission * missionInStorey;
	int capacity;
	int storey;
	int elevatorNum;

	int DURATION;	// duration of generating missions

	// for info collection
	int maxWaitingTime;
	int aveWaitingTimeCount;
	double aveWaitingTime;
	double aveFlow;
	int totalFlow;
};

class FCFSController:public ElevatorController // First Come First Served
{
public:
	 FCFSController (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(init_capacity, init_storey, init_elevatorNum){};
	void control();
	void storeMission(Mission *);
private:
	queue <Mission *> MissionQ;
};

class SSTFController:public ElevatorController // Shortest Seek Time First
{
public:
	SSTFController  (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(init_capacity, init_storey, init_elevatorNum){};
	void control();
	void storeMission(Mission *);

private:
	vector<Mission *>  MissionList;

};
