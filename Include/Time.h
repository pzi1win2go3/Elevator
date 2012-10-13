#ifndef TIME_H
#define TIME_H

class Time
{
public:
	Time();

	void tick();
	void reset();
private:
	int time;
};

#endif