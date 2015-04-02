#include "Entry.h"
#include <iostream>

const string Entry::FEEDBACK_AT = " at ";

Entry::Entry(){
	initialiseStatus();
}

void Entry::insertName(string inputName){
	_name = inputName;
}

string Entry::getName(){
	return _name;
}

void Entry::insertStartDate(Date inputStartDate){
	_hasDate = inputStartDate.getDateStatus();
	
	_startDate = inputStartDate;
	
	if (_hasDate){
		_startDate.initialiseDate();
	}

	/*try{
		date d(_startDate.getYear(), _startDate.getMonthNumber(), _startDate.getDay());
		throw "date does not exist";
	}
	catch(string error){
		cout << "error! Start " << error << endl;
	}*/
}

void Entry::insertEndDate(Date inputEndDate){
	_endDate = inputEndDate;
	
	if (_hasDate){
		_endDate.initialiseDate();
	}

	/*try{
		date d(_endDate.getYear(), _endDate.getMonthNumber(), _endDate.getDay());
		throw "date does not exist";
	}
	catch(string error){
		cout << "error! Start " << error << endl;
	}*/
}

Date Entry::getStartDate(){
	return _startDate;
}

Date Entry::getEndDate(){
	return _endDate;
}

bool Entry::getDateStatus(){
	return _hasDate;
}

void Entry::insertStartTime(Time inputStartTime){
	_startTime = inputStartTime;
	
	if (_hasDate) {
		_startTime.initialiseTime(_startDate.getDate());
	}

	/*try{
		ptime p(_startDate.getDate(), hours( _startTime.getHour()) + minutes(_startTime.getMinute()));
		throw "time does not exist";
	}
	catch(string error){
		cout << "error! Start " << error << endl;
	}*/
}

void Entry::insertEndTime(Time inputEndTime){
	_endTime = inputEndTime;
	
	if (_hasDate) {
		_endTime.initialiseTime(_endDate.getDate());
	}

	/*try{
		ptime p(_endDate.getDate(), hours( _endTime.getHour()) + minutes(_endTime.getMinute()));
		throw "time does not exist";
	}
	catch(string error){
		cout << "error! End " << error << endl;
	}*/
}

Time Entry::getStartTime(){
	return _startTime;
}

Time Entry::getEndTime(){
	return _endTime;
}

void Entry::initialiseStatus(){
	_status = false;
}

void Entry::changeStatus(){
	_status = true;
}

string Entry::getStatus(){
	string printStatus;
	if (_status == true){
		printStatus = "done";
	}
	if (_status == false){
		printStatus = "undone";
	}
	return printStatus;
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
	
	oss << _name << endl;
	if (_hasDate){
		oss	<< "Start Date & Time: ";
		greg_weekday startDateToString = _startDate.getDate().day_of_week();
		oss << " " << startDateToString.as_long_string()
			<< " " << _startDate.getDay() << " "
			<< _startDate.getMonth() << " "
			<< _startDate.getYear() << FEEDBACK_AT
			<< _startTime.getHour() << ".";
		if (_startTime.getMinute() < 10){
			oss << '0';
		}
		oss	<< _startTime.getMinute() << endl
		<< "End Date & Time: ";
		greg_weekday endDateToString = _endDate.getDate().day_of_week();
		oss << " " << endDateToString.as_long_string() 
		<< " " << _endDate.getDay() << " "
		<< _endDate.getMonth() << " "
		<< _endDate.getYear() << FEEDBACK_AT
		<< _endTime.getHour() << ".";
		if (_endTime.getMinute() < 10){
			oss << '0';
		}
		oss << _endTime.getMinute() << endl;
	}
	
	oss << "Location: " << _location << endl;
	
	if (_hasDate){
	oss	<< "Event duration : "
		<< days(calculateEventDurationInHours().hours()/24) << " days and "
		<< calculateEventDurationInHours().hours()%24 << " hours and " 
		<< calculateEventDurationInHours().minutes() << " minutes" << endl
		<< "Time left: " << calculateDaysFromToday() << " days "<< endl
		<< "Status: " << getStatus() << endl;
	}
	
	return oss.str();
}

string Entry::storeEntry(){
	ostringstream oss;
	
	oss << _name << endl;

	if (_hasDate){
		oss	<< _startDate.getDay() << " "
			<< _startDate.getMonth() << " "
			<< _startDate.getYear() << endl
			
			<< _startTime.getHour() << ".";
		if (_startTime.getMinute() < 10){
			oss << '0';
		}	
		oss	<< _startTime.getMinute() << endl 
		
			<< _endDate.getDay() << " "
			<< _endDate.getMonth() << " "
			<< _endDate.getYear() << endl
		
			<< _endTime.getHour() << ".";
		if (_endTime.getMinute() < 10){
			oss << '0';
		}
		oss << _endTime.getMinute() << endl;
	}

	oss	<< _location << endl

		<< getTags() << endl;
	
	return oss.str();
}