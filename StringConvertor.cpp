#include "StringConvertor.h"

const int StringConvertor::BLANK_SPACE_COUNT = 1;
const string StringConvertor::BLANK_SPACE = " ";
const string StringConvertor::FULLSTOP_MARKER = ".";
const string MONTHSHORT_JANUARY = "Jan";
const string MONTHSHORT_FEBRUARY = "Feb";
const string MONTHSHORT_MARCH = "Mar";
const string MONTHSHORT_APRIL = "Apr";
const string MONTHSHORT_MAY = "May";
const string MONTHSHORT_JUNE = "Jun";
const string MONTHSHORT_JULY = "Jul";
const string MONTHSHORT_AUGUST = "Aug";
const string MONTHSHORT_SEPTEMBER = "Sep";
const string MONTHSHORT_OCTOBER = "Oct";
const string MONTHSHORT_NOVEMBER = "Nov";
const string MONTHSHORT_DECEMBER = "Dec";

const string MONTHLONG_JANUARY = "January";
const string MONTHLONG_FEBRUARY = "February";
const string MONTHLONG_MARCH = "March";
const string MONTHLONG_APRIL = "April";
const string MONTHLONG_MAY = "May";
const string MONTHLONG_JUNE = "June";
const string MONTHLONG_JULY = "July";
const string MONTHLONG_AUGUST = "August";
const string MONTHLONG_SEPTEMBER = "September";
const string MONTHLONG_OCTOBER = "October";
const string MONTHLONG_NOVEMBER = "November";
const string MONTHLONG_DECEMBER = "December";

const string StringConvertor::MONTHSHORT_ARRAY[12] = {MONTHSHORT_JANUARY, MONTHSHORT_FEBRUARY, MONTHSHORT_MARCH, MONTHSHORT_APRIL, MONTHSHORT_MAY, MONTHSHORT_JUNE,
	MONTHSHORT_JULY, MONTHSHORT_AUGUST, MONTHSHORT_SEPTEMBER, MONTHSHORT_OCTOBER, MONTHSHORT_NOVEMBER, MONTHSHORT_DECEMBER};

const string StringConvertor::MONTHLONG_ARRAY[12] = {MONTHLONG_JANUARY, MONTHLONG_FEBRUARY, MONTHLONG_MARCH, MONTHLONG_APRIL, MONTHLONG_MAY, MONTHLONG_JUNE,
	MONTHLONG_JULY, MONTHLONG_AUGUST, MONTHLONG_SEPTEMBER, MONTHLONG_OCTOBER, MONTHLONG_NOVEMBER, MONTHLONG_DECEMBER};


StringConvertor::StringConvertor(){
}

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
		if (monthString == MONTHSHORT_ARRAY[monthCount - 1]||monthString == MONTHLONG_ARRAY[monthCount-1]){
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

void StringConvertor::convertStringToNumber(string input, int& number){
	istringstream convertToNumber(input);
	if (!(convertToNumber >> number)) {
		number = 0;  
	}
}

