#ifndef MISSION_H
#define MISSION_H

#include <iostream>
using namespace std;

class Mission
{
public:
	Mission(int tStart, int tEnd, int tPassenger);

private:
	int start;
	int end;
	int passenger;
};

#endif