#ifndef TIME_H
#define TIME_H

class Time
{
public:
	Time();

	void tick();
	void reset();
	int getTime();
private:
	int time;
};

#endif