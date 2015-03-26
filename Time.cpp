#include "Time.h"

Time::Time(){
}

void Time::insertHour(int inputHour){
	_hour = inputHour;
}

void Time::insertMinute(int inputMinute){
	_minute = inputMinute;
}

int Time::getHour(){
	return _entryTime.time_of_day().hours();
}

int Time::getMinute(){
	return _entryTime.time_of_day().minutes();
}

void Time::initialiseTime(date _entryDate){
	_entryTime = ptime(_entryDate, hours(_hour) + minutes(_minute));
}

ptime Time::getTime(){
	return _entryTime;
}