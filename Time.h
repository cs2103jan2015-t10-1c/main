#ifndef TIME_H
#define TIME_H
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
	ptime _entryTime;

public:
	Time();
	
	//input the hour and minutes into a Time object
	void insertHour(int);
	void insertMinute(int);
	
	//return the values of the private attributes
	int getHour();
	int getMinute();
	void initialiseTime(date);
	ptime getTime();
};

#endif