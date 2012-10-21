#include "Elevator.h"
#include "Mission.h"
#include "Time.h"
#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>

extern Time globalClock;

class ElevatorController
{
public:
	ElevatorController(int init_capacity, int init_storey, int init_elevatorNum);	// construction

	/////////////////////
	// print functions //
	void show();
	void info();
	/////////////////////
	/////////////////////

	void updateWaitingTime(Mission *);    // to call 3 functions below, called when a mission is waiting
	void updateMaxWaitingTime(Mission *);
	void updateMinWaitingTime(Mission *);
	void updateAveWaitingTime(Mission *);

	void updateRunTime(Mission *);			  // to call 3 functions below, called when a mission is completed
	void updateMaxRunTime(Mission *);			// actually it can be called whenever a mission is in elevator
	void updateMinRunTime(Mission *);			
	void updateAveRunTime(Mission *);

	void updateAveFlow();	 								// called when every 1 unit time

	virtual void control() = 0;
	virtual void storeMission(Mission *) = 0;

protected:
	int capacity;
	int storey;
	int elevatorNum;

	int DURATION;	  				// duration of generating missions

	Elevator * elevator;		// (pointer) elevators

	int * waiting;					// (pointer) numbers of waiting people of different storeys

	/////////////////////////
	// for info collection //
	int maxWaitingTime;
	int minWaitingTime;
	int aveWaitingTimeCount;
	double aveWaitingTime;
	int maxRunTime;
	int minRunTime;
	int aveRunTimeCount;
	double aveRunTime;
	double aveFlow;
	double totalFlow;
	/////////////////////////
	/////////////////////////
};

class FCFSController:public ElevatorController // Algorithm 1 : First Come First Served
{
public:
	 FCFSController (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(init_capacity, init_storey, init_elevatorNum){};
	void control();
	void storeMission(Mission *);
private:
	queue <Mission *> MissionQ;
};

class SSTFController:public ElevatorController // Algorithm 2 : Shortest Seek Time First
{
public:
	SSTFController  (int init_capacity, int init_storey, int init_elevatorNum)
	 :ElevatorController(init_capacity, init_storey, init_elevatorNum){};
	void control();
	void storeMission(Mission *);

private:
	vector<Mission *> MissionList;
	vector<Mission *> pickedMissionList;
};

class SCANController:public ElevatorController	// Algorithm 3 : Scan
{
public:
	SCANController  (int init_capacity, int init_storey, int init_elevatorNum);
	void control();
	void storeMission(Mission*);
private:
	vector<Mission *> MissionList;
	vector<Mission *> pickedMissionList;
};

class LOOKController:public ElevatorController	// Algorithm 4 : Look
{
public:
	LOOKController  (int init_capacity, int init_storey, int init_elevatorNum);
	void control();
	void storeMission(Mission*);
private:
	vector<Mission *> MissionList;
	vector<Mission *> pickedMissionList;
};
