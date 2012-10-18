#include <cstdlib>
#include <cstdio>

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

int main(int argc, char *argv[])
{
	printf("请输入最大乘客数:\n");
	scanf("%d", &capacity);

	printf("请输入电梯数:\n");
	scanf("%d", &elevatorNum);

	printf("请输入楼层数:\n");
	scanf("%d", &storey);

	printf("请输入泊松分布参数:\n");
	scanf("%lf", &lambda);

	srand(time(0));


	// generate controller
	// HERE decide which algorithm to use
	// 1.FCFS 2.SSTF
	FCFSController controller(capacity, storey, elevatorNum);
	
	while(true)
	{

		// 1. generate missions here
		int missionNum = 3;	// missions generated per unit time
		while(missionNum--)
		{
			Mission *newMission = new Mission(rand() % storey + 1, rand() % storey + 1, P_Rand(lambda), globalClock.getTime());
			controller.storeMission(newMission);
		}

		// 2. control
		controller.control();

	}

	return 0;
}
