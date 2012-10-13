#ifndef MISSION_H
#define MISSION_H

#include <iostream>
using namespace std;

class Mission
{
public:
	Mission(int initFrom, int initTo, int initPassenger);
	
	int getFrom();
	int getTo();
	int getPassenger();
	void setPassenger(int);

private:
	int from;
	int to;
	int passenger;
};

#endif