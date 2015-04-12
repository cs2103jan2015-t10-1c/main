#include "EntryTime.h"

//@author A0115902N
Time::Time(){
	_hour = 99;
	_minute = 99;
	_hasTime = false;
}

void Time::insertHour(int inputHour){
	_hour = inputHour;
}

void Time::insertMinute(int inputMinute){
	_minute = inputMinute;
	//check for a change to the default values
	if (_hour != 99 && _minute != 99){
		_hasTime = true;
	}
}

int Time::getHour(){
	return _entryTime.time_of_day().hours();
}

int Time::getMinute(){
	return _entryTime.time_of_day().minutes();
}

//check whether the entry has time
bool Time::getTimeStatus(){
	return _hasTime;
}

//initialise ptime object with the input values
void Time::initialiseTime(date _entryDate){
	_entryTime = ptime(_entryDate, hours(_hour) + minutes(_minute));
}

ptime Time::getTime(){
	return _entryTime;
}