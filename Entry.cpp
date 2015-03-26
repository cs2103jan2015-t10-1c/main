#include "Entry.h"
#include <iostream>

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
	_startDate.initialiseDate();
}

void Entry::insertEndDate(Date inputEndDate){
	_endDate = inputEndDate;
	_endDate.initialiseDate();
}

Date Entry::getStartDate(){
	return _startDate;
}

Date Entry::getEndDate (){
	return _endDate;
}

void Entry::insertStartTime(Time inputStartTime){
	_startTime = inputStartTime;
	_startTime.initialiseTime(_startDate.getDate());
}

void Entry::insertEndTime(Time inputEndTime){
	_endTime = inputEndTime;
	_endTime.initialiseTime(_endDate.getDate());
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

void Entry::addTag(string tag){
	_tag.push_back(tag);
}

void Entry::searchEntryTag(string tag){
	vector<string>::iterator iterTag;
	for(iterTag = _tag.begin(); iterTag != _tag.end(); iterTag++){
		if(*iterTag == tag){
			cout << *iterTag << " " << _name << endl;
		}
	}
}

void Entry::displayTags(){
	vector<string>::iterator iterTag;
	for(iterTag = _tag.begin(); iterTag != _tag.end(); iterTag++){
		cout << *iterTag << endl;
	}
}

date_duration Entry::calculateDifference(){
	date startDate = _startDate.getDate();
	date today(day_clock::local_day());
	return startDate - today;
}