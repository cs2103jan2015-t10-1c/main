#include "Date.h"

Date::Date(){
	_day = 0;
	_month = 0;
	_year = 0;
	_hasDate = false;
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
	bool inThePast = true;
	date today(day_clock::local_day());
	if(greg_year(_year) >= today.year()){
		if(greg_month(_month) >= today.month()){
			if(greg_day(_day) >= today.day()){
				inThePast = false;
			}
		}
	}
	if (inThePast){
		cout << endl << "Warning! Date is in the past" << endl;
	}
		_entryDate = date(_year, _month, _day);
}
	

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
