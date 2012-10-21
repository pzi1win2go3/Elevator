#include <cstdlib>
#include <cstdio>
#include <string>

#include "../Include/Mission.h"
#include "../Include/Elevator.h"
#include "../Include/Time.h"
#include "../Include/Poisson.h"
#include "../Include/ElevatorController.h"

# define DEBUG

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
	printf("Please input capacity:\n");
	scanf("%d", &capacity);

	printf("Please input number of elevators:\n");
	scanf("%d", &elevatorNum);

	printf("Please input number of storeys:\n");
	scanf("%d", &storey);

	printf("Please input Lambda:\n");
	scanf("%lf", &lambda);
}

int main(int argc, char *argv[])
{
	while(true)
	{
		ElevatorController * controller;

		// choose which algorithm to use
		int decision;
		bool over = false;

		printf("----Please input the number of algorithm to use(1, 2, 3, 4):\n");
		printf("	0.exit\n");
		printf("	1.FCFS first come first serve\n");
		printf("	2.SSTF shortest seek time first\n");
		printf("	3.SCAN\n");
		printf("	4.LOOK\n");
		cin >> decision;

		if(decision == 0)
		{
			printf("Thank you for using, see you next time.\n");
			break;
		}
		else if(decision == 1)
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
			printf("Sorry, wrong input.\n");
			continue;
		}

		// randomize
		srand(time(0));

		// reset time
		globalClock.reset();

		// process
		while(true)
		{			
			// 1. generate missions
			int missionNum = 1;	// num of missions generated per DURATION

			while(missionNum--)
			{
				Mission *newMission = new Mission(rand() % storey + 1, rand() % storey + 1, P_Rand(lambda), globalClock.getTime());
				controller->storeMission(newMission);
			}

			// 2. control
			controller->control();

			// 3. display for 100s only, then choose again
			if(globalClock.getTime() >= 100)
			{
				delete controller;
				break;
			}
		}
	}

	return 0;
}
