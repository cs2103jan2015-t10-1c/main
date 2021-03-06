#include "Entry.h"
#include <iostream>
#include <Windows.h>

const string Entry::FEEDBACK_AT = " at ";

Entry::Entry() {
	initialiseStatus();
}

//@author A0115656A
//insert string inputName into the private attribute _name
void Entry::insertName(string inputName) {
	_name = inputName;
}

//returns a string containing the value of private attribute _name
string Entry::getName() {
	return _name;
}

//insert int entryNumber into the private attribute _entryNumber
void Entry::insertEntryNumber(int entryNumber) {
	_entryNumber = entryNumber;
}

//returns an int containing the value of private attribute _entryNumber
int Entry::getEntryNumber() {
	return _entryNumber;
}

//@author A0115902N

//insert Date object as start date. initialise the date value
void Entry::insertStartDate(Date inputStartDate){
	_hasDate = inputStartDate.getDateStatus();
	_startDate = inputStartDate;
	if (_hasDate){
		_startDate.initialiseDate();
	}
}
//insert Date object as end date. initialise the date value
void Entry::insertEndDate(Date inputEndDate){
	_endDate = inputEndDate;
	if (_hasDate){
		_endDate.initialiseDate();
	}
}

//return Date object for start date
Date Entry::getStartDate(){
	return _startDate;
}

//return Date object for end date
Date Entry::getEndDate(){
	return _endDate;
}

bool Entry::getDateStatus(){
	return _hasDate;
}

//insert Time object as start time. initialise the ptime value
void Entry::insertStartTime(Time inputStartTime){
	_hasTime = inputStartTime.getTimeStatus();
	_startTime = inputStartTime;
	if (_hasDate && _hasTime) {
		_startTime.initialiseTime(_startDate.getDate());
	}
}

//insert Time object as end time. initialise the ptime value
void Entry::insertEndTime(Time inputEndTime){
	_endTime = inputEndTime;
	if (_hasDate && _hasTime) {
		_endTime.initialiseTime(_endDate.getDate());
	}
}

//return Time object for start time
Time Entry::getStartTime(){
	return _startTime;
}

//return Time object for end time
Time Entry::getEndTime(){
	return _endTime;
}

//@author A0116660L
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

//@author A0115656A
//insert string inputLocation into the private attribute _location
void Entry::insertLocation(string inputLocation){
	_location = inputLocation;
}

//returns a string containing the value of  private attribute _location
string Entry::getLocation (){	
	return _location;
}

//@author A0116660L
void Entry::insertTags(vector<string>& tags){
	_tags = tags;
}

void Entry::searchEntryTag(string tag, bool& tagFound){
	vector<string>::iterator iterTag;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		size_t found = iterTag->find(tag);
		if(found != string::npos){
			tagFound = true;
		}
	}
}

//@author A0115656A
//returns a string containing the tags inside the vector<string> _tags
string Entry::getTags() {
	ostringstream oss;
	vector<string>::iterator iterTag;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		oss << *iterTag << " ";
	}

	return oss.str();
}

//add a string tag into vector<string> _tags
void Entry::addTag(string tag) {
	_tags.push_back(tag);
}

//remove a string tag from vector<string> _tags
void Entry::removeTag(string tag) {
	vector<string>::iterator iterTag;
	bool isFound = false;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		size_t found = iterTag->find(tag);
		if(found != string::npos){
			_tags.erase(iterTag);
			isFound = true;
			break;
		}
	}

	if (!isFound){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << tag << " does not exist" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
}

//@author A0115902N

//return date_duration object. calculates day from today to start date
date_duration Entry::calculateDaysFromToday(){
	date startDate = _startDate.getDate();
	date today(day_clock::local_day());
	return startDate - today;
}

//return date_duration object. calculates length from start to end date
date_duration Entry::calculateEventDurationInDays(){
	date startDate = _startDate.getDate();
	date endDate = _endDate.getDate();
	date_duration dayDifference = endDate - startDate;
	return dayDifference;
}

//return time_duration object. calculates length from start to end time
time_duration Entry::calculateEventDurationInHours(){
	ptime startTime = _startTime.getTime();
	ptime endTime = _endTime.getTime();
	time_duration timeDifference = endTime - startTime;
	return timeDifference;
}

//return a complete list of an entry -
//name, start date end date, start time end time
//location, status, tags
string Entry::getFullDisplay(){
	ostringstream oss;
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	oss << _name << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
	if (_hasDate){
		string eventType;
		if(_startTime.getTime() == _endTime.getTime()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			eventType = "Deadline:\t";
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			eventType = "Start Date & Time: ";
		}
		oss	<< eventType;
		greg_weekday startDateToString = _startDate.getDate().day_of_week();
		oss << "\t|" << startDateToString.as_long_string()
			<< " " << _startDate.getDay() << " "
			<< _startDate.getMonth() << " "
			<< _startDate.getYear() << FEEDBACK_AT
			<< _startTime.getHour() << ".";
		if (_startTime.getMinute() < 10){
			oss << '0';
		}
		oss	<< _startTime.getMinute() << endl;
		if(_startTime.getTime() != _endTime.getTime()){
			oss << "End Date & Time: ";
			greg_weekday endDateToString = _endDate.getDate().day_of_week();
			oss << "\t|" << endDateToString.as_long_string() 
			<< " " << _endDate.getDay() << " "
			<< _endDate.getMonth() << " "
			<< _endDate.getYear() << FEEDBACK_AT
			<< _endTime.getHour() << ".";
			if (_endTime.getMinute() < 10){
				oss << '0';
			}
		oss << _endTime.getMinute() << endl;
		}
	}
	
	oss << "Location: " << "\t\t|" << _location << endl;
	
	if (_hasDate){
		if(_startTime.getTime() != _endTime.getTime()){
			oss	<< "Event duration: " << "\t|";
			if(days(calculateEventDurationInHours().hours()/24) > days(0)){
				oss << days(calculateEventDurationInHours().hours()/24) << " days and ";
			} 
			oss << calculateEventDurationInHours().hours()%24 << " hours and " 
			<< calculateEventDurationInHours().minutes() << " minutes" << endl;
		}
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		oss << "Time to event: " << "\t\t|" << calculateDaysFromToday() << " days "<< endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
	
	oss	<< "Status: " << "\t\t|" << getStatus() << endl
		<< "Tags: " << "\t\t\t|";
	vector<string>::iterator tagIter;
	for(tagIter = _tags.begin(); tagIter != _tags.end(); tagIter++){
		oss << *tagIter << " ";
	}
	oss << endl;
	
	return oss.str();
}

//return a short display of an entry
//name, start date end date, start time end time
string Entry::getShortDisplay(){
	ostringstream oss;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	oss << _name << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	if (_hasDate){
		string eventType;
		if(_startTime.getTime() == _endTime.getTime()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			eventType = "Deadline:\t";
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			eventType = "Start Date & Time: ";
		}
		oss	<< eventType;
		greg_weekday startDateToString = _startDate.getDate().day_of_week();
		oss << "\t|" << startDateToString.as_long_string()
			<< " " << _startDate.getDay() << " "
			<< _startDate.getMonth() << " "
			<< _startDate.getYear() << FEEDBACK_AT
			<< _startTime.getHour() << ".";
		if (_startTime.getMinute() < 10){
			oss << '0';
		}
		oss	<< _startTime.getMinute() << endl;
		if(_startTime.getTime() == _endTime.getTime()){
			return oss.str();
		}
		else{
			oss << "End Date & Time: ";
			greg_weekday endDateToString = _endDate.getDate().day_of_week();
			oss << "\t|" << endDateToString.as_long_string() 
			<< " " << _endDate.getDay() << " "
			<< _endDate.getMonth() << " "
			<< _endDate.getYear() << FEEDBACK_AT
			<< _endTime.getHour() << ".";
			if (_endTime.getMinute() < 10){
			oss << '0';
		}
		oss << _endTime.getMinute() << endl;
		}
	}
	return oss.str();
}

//@author A0115656A
//return a string containing the information of an entry, for storage purposes
string Entry::storeEntry() {
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
		<< getStatus() << endl
		<< getTags() << endl;
	
	return oss.str();
}

