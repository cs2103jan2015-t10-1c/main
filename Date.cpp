#include "Date.h"

Date::Date(){
}

void Date::insertDay(int inputDay){
	_day = inputDay;
}

void Date::insertMonth(int inputMonth){
	_month = inputMonth;
}

void Date::insertYear(int inputYear){
	_year = inputYear;
}

int Date::getDay(){
	return _day;
}

string Date::getMonth(){
	switch(_month){
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

int Date::getYear(){
	return _year;
}	

