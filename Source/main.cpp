#include <cstdlib>
#include <cstdio>
#include <string>

#include "../Include/Mission.h"
#include "../Include/Elevator.h"
#include "../Include/Time.h"
#include "../Include/Poisson.h"
#include "../Include/ElevatorController.h"

using namespace std;

//////////////////////
// global variables //
int capacity;
int elevatorNum;
int storey;
double lambda;
Time globalClock;
//////////////////////
//////////////////////

void input()
{
	printf("请输入最大乘客数:\n");
	scanf("%d", &capacity);

	printf("请输入电梯数:\n");
	scanf("%d", &elevatorNum);

	printf("请输入楼层数:\n");
	scanf("%d", &storey);

	printf("请输入泊松分布参数:\n");
	scanf("%lf", &lambda);
}

int main(int argc, char *argv[])
{
	while(true)
	{
		ElevatorController * controller;
		int decision;
		bool over = false;

		printf("----请输入您要使用的算法的编号(1, 2, 3, 4):\n");
		printf("	1.FCFS 先到先服务\n");
		printf("	2.SSTF 最短搜索时间\n");
		printf("	3.SCAN\n");
		printf("	4.LOOK\n");
		cin >> decision;

		if(decision == 1)
		{
			input();
			controller = new FCFSController(capacity, storey, elevatorNum);
		}
		else if(decision == 2)
		{
			input();
			controller = new SSTFController(capacity, storey, elevatorNum);
		}
		else if(decision == 3)
		{
			input();
			controller = new SCANController(capacity, storey, elevatorNum);
		}
		else if(decision == 4)
		{
			input();
			controller = new LOOKController(capacity, storey, elevatorNum);
		}
		else
		{
			printf("您没有输入正确的选项。\n");
			continue;
		}

		srand(time(0));

		while(true)
		{
			// 1. generate missions here
			int missionNum = 3;	// missions generated per unit time
			while(missionNum--)
			{
				Mission *newMission = new Mission(rand() % storey + 1, rand() % storey + 1, P_Rand(lambda), globalClock.getTime());
				controller->storeMission(newMission);
			}
			// 2. control
			controller->control();

			if(globalClock.getTime() == 100)
			{
				break;
			}
		}
	}

	return 0;
}
