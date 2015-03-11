#include "Entry.h"

Entry::Entry(){
}

void Entry::insertName(string inputName){
	_name = inputName;
}

string Entry::getName(){
	return _name;
}

void Entry::insertStartDate(Date inputStartDate){
	_startDate = inputStartDate;
}

void Entry::insertEndDate(Date inputEndDate){
	_endDate = inputEndDate;
}

Date Entry::getStartDate(){
	return _startDate;
}

Date Entry::getEndDate (){
	return _endDate;
}

void Entry::insertStartTime(Time inputStartTime){
	_startTime = inputStartTime;
}

void Entry::insertEndTime(Time inputEndTime){
	_endTime = inputEndTime;
}

Time Entry::getStartTime(){
	return _startTime;
}

Time Entry::getEndTime(){
	return _endTime;
}

void Entry::insertLocation(string inputLocation){
	_location = inputLocation;
}

string Entry::getLocation (){	
	return _location;
}