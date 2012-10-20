#include "Elevator.h"
#include "Mission.h"
#include "Time.h"
#include <queue>
#include <iostream>
#include <cmath>

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

	void updateWaitingTime(Mission *);    // to call 3 functions below, called when a mission is waiting every 1 unit time
	void updateMaxWaitingTime(Mission *); 
	void updateMinWaitingTime(Mission *);
	void updateAveWaitingTime(Mission *);	
	void updateRunTime(Mission *);
	void updateMaxRunTime(Mission *); 
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
	vector<Mission *> MissionList;
};

class SCANController:public ElevatorController
{
public:
	SCANController  (int init_capacity, int init_storey, int init_elevatorNum);
	void control();
	void storeMission(Mission*);
private:
	vector<Mission *> MissionList;

};

class LOOKController:public ElevatorController
{
public:
	LOOKController  (int init_capacity, int init_storey, int init_elevatorNum);
	void control();
	void storeMission(Mission*);
private:
	vector<Mission *> MissionList;
};
