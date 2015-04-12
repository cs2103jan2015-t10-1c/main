#ifndef ENTRYTIME_H
#define ENTRYTIME_H
#include <string>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class Time{
private:
	int _hour;
	int _minute;
	bool _hasTime;
	ptime _entryTime;

public:
	//@author A0115902N
	Time();
	
	//input the hour and minutes into a Time object
	void insertHour(int);
	void insertMinute(int);
	
	//return the values of the private attributes
	int getHour();
	int getMinute();
	bool getTimeStatus();
	void initialiseTime(date);
	ptime getTime();
};

#endif