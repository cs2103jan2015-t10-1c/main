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
int Date::getDay(){
	return _entryDate.day();
}

string Date::getMonth(){
	int monthNumber = _entryDate.month();
	switch(monthNumber){
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

int Date::getMonthNumber(){
	return _entryDate.month();
}

int Date::getYear(){
	return _entryDate.year();
}	

//check whether the entry has date
bool Date::getDateStatus(){
	return _hasDate;
}

date Date::getDate(){
	date toPassToTime = _entryDate;
	return toPassToTime;
}

void Date::printDayOfDate(){
	cout << _entryDate.day_of_week();
}
