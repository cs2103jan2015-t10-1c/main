#include "EntryDate.h"
#include <Windows.h>

//@author A0115902N
Date::Date(){
	_day = 0;
	_month = 0;
	_year = 0;
	_hasDate = false;
	_loading = false;
}

Date::Date(bool loading){
	_day = 0;
	_month = 0;
	_year = 0;
	_hasDate = false;
	_loading = loading;
}

void Date::insertDay(int inputDay){
	_day = inputDay;
}

void Date::insertMonth(int inputMonth){
	_month = inputMonth;

	//an entry with day and month can be considered as having date, year is inconsequential
	if (_day != 0 && _month != 0){
		_hasDate = true;
	}
}

void Date::insertYear(int inputYear){
	_year = inputYear;
}

void Date::initialiseDate(){
	bool inThePast;
	date today(day_clock::local_day());
	date thisDate(_year, _month, _day);
	inThePast = thisDate < today;
	if (inThePast){
		if(!_loading){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << endl << "Warning! Date is in the past" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		}
	}
		_entryDate = date(_year, _month, _day);
}
	

//@author A0115656A
//returns an int containing the value of private attribute _entryDate.day()
int Date::getDay() {
	return _entryDate.day();
}

//returns a string containing the value of private attribute _entryDate.month() after being converted to string
string Date::getMonth() {
	int monthNumber = _entryDate.month();
	switch(monthNumber) {
		case 1:
			return "Jan";
		case 2: 
			return "Feb";
		case 3: 
			return "Mar";
		case 4: 
			return "Apr";
		case 5: 
			return "May";
		case 6: 	
			return "Jun";
		case 7: 
			return "Jul";
		case 8: 
			return "Aug";
		case 9: 
			return "Sep";
		case 10: 
			return "Oct";
		case 11: 
			return "Nov";
		case 12: 
			return "Dec";
		default:
			return "Invalid month";
	}
}

//returns an int containing the value of private attribute _entryDate.month()
int Date::getMonthNumber() {
	return _entryDate.month();
}

//returns an int containing the value of private attribute _entryDate.year()
int Date::getYear() {
	return _entryDate.year();
}	

//return true when the Entry has a valid date, false otherwise
bool Date::getDateStatus() {
	return _hasDate;
}

//return a date (from boost library) containing the date of this object
date Date::getDate() {
	date toPassToTime = _entryDate;
	return toPassToTime;
}

//print out the day of the Date
void Date::printDayOfDate() {
	cout << _entryDate.day_of_week();
}
