#include <cstdlib>
#include <cstdio>

#include "../Include/Mission.h"
#include "../Include/Elevator.h"
#include "../Include/Time.h"
#include "../Include/Poisson.h"
#include "../Include/ElevatorController.h"

using namespace std;

int capacity;
int elevatorNum;
int storey;
double lambda;
int DURATION = 5;	// duration of generating missions

Time globalClock;
ElevatorController controller(capacity, elevatorNum, storey);

int main(int argc, char *argv[])
{
	printf("请输入最大乘客数:\n");
	scanf("%d\n", &capacity);

	printf("请输入电梯数:\n");
	scanf("%d\n", &elevatorNum);
	
	printf("请输入楼层数:\n");
	scanf("%d\n", &storey);
	
	printf("请输入泊松分布参数:\n");
	scanf("%lf\n", &lambda);
	
	srand(time(0));
	
	while(true)
	{
		Mission *newMission = new Mission(rand() % storey + 1, rand() % storey + 1, P_Rand(lambda));
		controller.storeMission(newMission);
		// 1.generate missions
		controller.control();
		// 2.control
	}

	return 0;
}