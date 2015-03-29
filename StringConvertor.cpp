#include "StringConvertor.h"

const int StringConvertor::BLANK_SPACE_COUNT = 1;
const string StringConvertor::BLANK_SPACE = " ";
const string StringConvertor::FULLSTOP_MARKER = ".";

const string MONTH_JANUARY = "January";
const string MONTH_FEBRUARY = "February";
const string MONTH_MARCH = "March";
const string MONTH_APRIL = "April";
const string MONTH_MAY = "May";
const string MONTH_JUNE = "June";
const string MONTH_JULY = "July";
const string MONTH_AUGUST = "August";
const string MONTH_SEPTEMBER = "September";
const string MONTH_OCTOBER = "October";
const string MONTH_NOVEMBER = "November";
const string MONTH_DECEMBER = "December";

const string StringConvertor::MONTH_ARRAY[12] = {MONTH_JANUARY, MONTH_FEBRUARY, MONTH_MARCH, MONTH_APRIL, MONTH_MAY, MONTH_JUNE,
	MONTH_JULY, MONTH_AUGUST, MONTH_SEPTEMBER, MONTH_OCTOBER, MONTH_NOVEMBER, MONTH_DECEMBER};

void StringConvertor::extractStringTime(string& inputString, string& timeString){
	int endOfTime = inputString.find(BLANK_SPACE);
	timeString = inputString.substr(0, endOfTime);
	inputString.erase(0, endOfTime + BLANK_SPACE_COUNT);
}

void StringConvertor::extractStringDate(string& inputString, string& dateString){
	int endOfDay = inputString.find(BLANK_SPACE);
	int endOfMonth = inputString.find(BLANK_SPACE, endOfDay + BLANK_SPACE_COUNT);
	int endOfYear = inputString.find(BLANK_SPACE, endOfMonth + BLANK_SPACE_COUNT);
	dateString = inputString.substr(0, endOfYear);
	inputString.erase(0, endOfYear + BLANK_SPACE_COUNT);
}

void StringConvertor::convertTime(string entryTime, int& entryHour, int& entryMin){
	istringstream iss(entryTime);
	string start;
	string end;
	iss >> start >> end;

	size_t startDot = start.find_first_of(FULLSTOP_MARKER);
	string startHourString = start.substr(0, startDot);
	istringstream convertStartHour(startHourString);
	if (!(convertStartHour >> entryHour)) {
		entryHour = 0;
	}
	
	string startMinString = start.substr(startDot + 1, string::npos);
	istringstream convertStartMin(startMinString);
	if (!(convertStartMin >> entryMin)) {
		entryMin = 0; 
	}
}

void StringConvertor::convertDate(string entryDate, int& entryDay, int& entryMonth, int& entryYear){
	istringstream iss(entryDate);
	string dayString;
	string monthString;
	string yearString;

	iss >> dayString
		>> monthString
		>> yearString;

	//day
	istringstream convertDay(dayString);
	if (!(convertDay >> entryDay)) {
		entryDay = 0;  
	}

	//month
	bool found = false;
	int monthCount = 1;
	while (!found){
		if (monthString == MONTH_ARRAY[monthCount - 1]){
			found = true;
			entryMonth = monthCount;
		}
		else{
			monthCount++;
		}
	}

	//year
	istringstream convertYear(yearString);
	if (!(convertYear >> entryYear)) {
		entryYear = 0;  
	}
}


