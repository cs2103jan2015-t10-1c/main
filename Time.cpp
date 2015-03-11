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
	return _hour;
}

int Time::getMinute(){
	return _minute;
}

