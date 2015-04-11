#include "Entry.h"
#include <iostream>
#include <Windows.h>

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

void Entry::insertEntryNumber(int entryNumber){
	_entryNumber = entryNumber;
}

int Entry::getEntryNumber(){
	return _entryNumber;
}

void Entry::insertStartDate(Date inputStartDate){
	_hasDate = inputStartDate.getDateStatus();
	
	_startDate = inputStartDate;
	
	if (_hasDate){
		_startDate.initialiseDate();
	}
}

void Entry::insertEndDate(Date inputEndDate){
	_endDate = inputEndDate;
	
	if (_hasDate){
		_endDate.initialiseDate();
	}
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
	_hasTime = inputStartTime.getTimeStatus();

	_startTime = inputStartTime;
	
	if (_hasDate && _hasTime) {
		_startTime.initialiseTime(_startDate.getDate());
	}
}

void Entry::insertEndTime(Time inputEndTime){
	_endTime = inputEndTime;
	
	if (_hasDate && _hasTime) {
		_endTime.initialiseTime(_endDate.getDate());
	}
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

string Entry::getTags(){
	ostringstream oss;
	vector<string>::iterator iterTag;
	for(iterTag = _tags.begin(); iterTag != _tags.end(); iterTag++){
		oss << *iterTag << " ";
	}

	return oss.str();
}

void Entry::addTag(string tag){
	_tags.push_back(tag);
}

void Entry::removeTag(string tag){
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

string Entry::getFullDisplay(){
	ostringstream oss;
	
	oss << _name << endl;
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

string Entry::getShortDisplay(){
	ostringstream oss;
	oss << _name << endl;
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
		<< getStatus() << endl
		<< getTags() << endl;
	
	return oss.str();
}

