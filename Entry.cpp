#include "Entry.h"
#include <iostream>

const string Entry::FEEDBACK_AT = " at ";

Entry::Entry(){
}

void Entry::insertName(string inputName){
	_name = inputName;
}

string Entry::getName(){
	return _name;
}

void Entry::insertStartDate(Date inputStartDate){
	_hasStartDate = inputStartDate.getDateStatus();
	
	_startDate = inputStartDate;
	_startDate.initialiseDate();
}

void Entry::insertEndDate(Date inputEndDate){
	_hasEndDate = inputEndDate.getDateStatus();

	//if there is no inputEndDate, then the entry starts and ends on the same day
	if (!_hasEndDate){
		_endDate = _startDate;
	}
	else{
		_endDate = inputEndDate;
	}

	_endDate.initialiseDate();
}

Date Entry::getStartDate(){
	return _startDate;
}

bool Entry::getStartDateStatus(){
	return _hasStartDate;
}

Date Entry::getEndDate(){
	return _endDate;
}

bool Entry::getEndDateStatus(){
	return _hasEndDate;
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

void Entry::addTags(vector<string>& tags){
	_tags = tags;
}

void Entry::searchEntryTag(string tag, int count){
	vector<string>::iterator iterTag;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		if(*iterTag == tag){
			cout << endl;
			cout << "- - - - - - - - - - - - - - - -";
			cout << *iterTag << " " << endl
			<< count << ". " << getDisplay();
			cout << "- - - - - - - - - - - - - - - -";
			cout << endl;
		}
	}
}

string Entry::getTags(){
	ostringstream oss;
	vector<string>::iterator iterTag;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		oss << *iterTag << " ";
	}

	return oss.str();
}

date_duration Entry::calculateDaysFromToday(){
	date startDate = _startDate.getDate();
	date today(day_clock::local_day());
	return startDate - today;
}

date_duration Entry::calculateEventDurationInDays(){
	date startDate = _startDate.getDate();
	date endDate = _endDate.getDate();
	date_duration dayDifference = endDate - startDate;
	return dayDifference;
}

time_duration Entry::calculateEventDurationInHours(){
	ptime startTime = _startTime.getTime();
	ptime endTime = _endTime.getTime();
	time_duration timeDifference = endTime - startTime;
	return timeDifference;
}

string Entry::getDisplay(){
	ostringstream oss;
	
	oss << _name << endl
		<< "Start Date & Time: ";
	greg_weekday startDateToString = _startDate.getDate().day_of_week();
	oss << " " << startDateToString.as_long_string()
		<< " " << _startDate.getDay() << " "
		<< _startDate.getMonth() << " "
		<< _startDate.getYear() << FEEDBACK_AT
		<< _startTime.getHour() << "."
		<< _startTime.getMinute() << endl
		<< "End Date & Time: ";
	greg_weekday endDateToString = _endDate.getDate().day_of_week();
	oss << " " << endDateToString.as_long_string() 
		<< " " << _endDate.getDay() << " "
		<< _endDate.getMonth() << " "
		<< _endDate.getYear() << FEEDBACK_AT
		<< _endTime.getHour() << "."
		<< _endTime.getMinute() << endl
		<< "Location: "
		<< _location << endl
		<< "Event duration : "
		<< days(calculateEventDurationInHours().hours()/24) << " days and "
		<< calculateEventDurationInHours().hours()%24 << " hours and " 
		<< calculateEventDurationInHours().minutes() << " minutes" << endl
		<< "Time left: " << calculateDaysFromToday() << " days "<< endl;
	
	return oss.str();
}

string Entry::storeEntry(){
	ostringstream oss;
	
	oss << _name << endl

		<< _startDate.getDay() << " "
		<< _startDate.getMonth() << " "
		<< _startDate.getYear() << endl
		
		<< _startTime.getHour() << "."
		<< _startTime.getMinute() << endl 
		
		<< _endDate.getDay() << " "
		<< _endDate.getMonth() << " "
		<< _endDate.getYear() << endl
		
		<< _endTime.getHour() << "."
		<< _endTime.getMinute() << endl

		<< _location << endl

		<< getTags() << endl;
	
	return oss.str();
}