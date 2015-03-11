#ifndef TIME_H
#define TIME_H
#include <string>

using namespace std;

class Time{
private:
	int _hour;
	int _minute;

public:
	Time();
	
	//input the hour and minutes into a Time object
	void insertHour(int);
	void insertMinute(int);
	
	//return the values of the private attributes
	int getHour();
	int getMinute();
};

#endif