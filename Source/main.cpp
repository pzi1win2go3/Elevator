#include <iostream>
#include "../Include/Poisson.h"
#include "../Include/ElevatorController.h"

using namespace std;

Time globalClock;
ElevatorController controller;

int maxPassengerNum;
int elevatorNum;
int floorNum;
double lambda;

const DURATION = 5;										// duration of generating missions

int main(int argc, char *argv[])
{
	cout << "请输入最大乘客数:" << endl;
	cin >> maxPassengerNum;
	cout << "请输入电梯数:" << endl;
	cin >> elevatorNum;
	cout << "请输入楼层数:" << endl;
	cin >> floorNum;
	cout << "请输入泊松分布参数:" << endl;
	cin >> lambda;
	srand(time(0));
	while(true)
	{
		newMission = new Mission(rand()%floorNum+1, rand()%floorNum+1, P_rand(lambda));
		controller.storeMission (newMission);
		// 1.generate missions
		controller.control()
		// 2.control
	}

	return 0;
}