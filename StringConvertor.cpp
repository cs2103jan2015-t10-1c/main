#include "StringConvertor.h"

const int StringConvertor::BLANK_SPACE_COUNT = 1;
const string StringConvertor::BLANK_SPACE = " ";
const string StringConvertor::FULLSTOP_MARKER = ".";
const string UPPERCASE_MONTHSHORT_JANUARY = "Jan";
const string UPPERCASE_MONTHSHORT_FEBRUARY = "Feb";
const string UPPERCASE_MONTHSHORT_MARCH = "Mar";
const string UPPERCASE_MONTHSHORT_APRIL = "Apr";
const string UPPERCASE_MONTHSHORT_MAY = "May";
const string UPPERCASE_MONTHSHORT_JUNE = "Jun";
const string UPPERCASE_MONTHSHORT_JULY = "Jul";
const string UPPERCASE_MONTHSHORT_AUGUST = "Aug";
const string UPPERCASE_MONTHSHORT_SEPTEMBER = "Sep";
const string UPPERCASE_MONTHSHORT_OCTOBER = "Oct";
const string UPPERCASE_MONTHSHORT_NOVEMBER = "Nov";
const string UPPERCASE_MONTHSHORT_DECEMBER = "Dec";

const string UPPERCASE_MONTHLONG_JANUARY = "January";
const string UPPERCASE_MONTHLONG_FEBRUARY = "February";
const string UPPERCASE_MONTHLONG_MARCH = "March";
const string UPPERCASE_MONTHLONG_APRIL = "April";
const string UPPERCASE_MONTHLONG_MAY = "May";
const string UPPERCASE_MONTHLONG_JUNE = "June";
const string UPPERCASE_MONTHLONG_JULY = "July";
const string UPPERCASE_MONTHLONG_AUGUST = "August";
const string UPPERCASE_MONTHLONG_SEPTEMBER = "September";
const string UPPERCASE_MONTHLONG_OCTOBER = "October";
const string UPPERCASE_MONTHLONG_NOVEMBER = "November";
const string UPPERCASE_MONTHLONG_DECEMBER = "December";

const string LOWERCASE_MONTHSHORT_JANUARY = "jan";
const string LOWERCASE_MONTHSHORT_FEBRUARY = "feb";
const string LOWERCASE_MONTHSHORT_MARCH = "mar";
const string LOWERCASE_MONTHSHORT_APRIL = "apr";
const string LOWERCASE_MONTHSHORT_MAY = "may";
const string LOWERCASE_MONTHSHORT_JUNE = "jun";
const string LOWERCASE_MONTHSHORT_JULY = "jul";
const string LOWERCASE_MONTHSHORT_AUGUST = "aug";
const string LOWERCASE_MONTHSHORT_SEPTEMBER = "sep";
const string LOWERCASE_MONTHSHORT_OCTOBER = "oct";
const string LOWERCASE_MONTHSHORT_NOVEMBER = "nov";
const string LOWERCASE_MONTHSHORT_DECEMBER = "dec";

const string LOWERCASE_MONTHLONG_JANUARY = "january";
const string LOWERCASE_MONTHLONG_FEBRUARY = "february";
const string LOWERCASE_MONTHLONG_MARCH = "march";
const string LOWERCASE_MONTHLONG_APRIL = "april";
const string LOWERCASE_MONTHLONG_MAY = "may";
const string LOWERCASE_MONTHLONG_JUNE = "june";
const string LOWERCASE_MONTHLONG_JULY = "july";
const string LOWERCASE_MONTHLONG_AUGUST = "august";
const string LOWERCASE_MONTHLONG_SEPTEMBER = "september";
const string LOWERCASE_MONTHLONG_OCTOBER = "october";
const string LOWERCASE_MONTHLONG_NOVEMBER = "november";
const string LOWERCASE_MONTHLONG_DECEMBER = "december";

const string StringConvertor::UPPERCASE_MONTHSHORT_ARRAY[12] = {UPPERCASE_MONTHSHORT_JANUARY, UPPERCASE_MONTHSHORT_FEBRUARY, UPPERCASE_MONTHSHORT_MARCH, UPPERCASE_MONTHSHORT_APRIL, UPPERCASE_MONTHSHORT_MAY, UPPERCASE_MONTHSHORT_JUNE,
	UPPERCASE_MONTHSHORT_JULY, UPPERCASE_MONTHSHORT_AUGUST, UPPERCASE_MONTHSHORT_SEPTEMBER, UPPERCASE_MONTHSHORT_OCTOBER, UPPERCASE_MONTHSHORT_NOVEMBER, UPPERCASE_MONTHSHORT_DECEMBER};

const string StringConvertor::UPPERCASE_MONTHLONG_ARRAY[12] = {UPPERCASE_MONTHLONG_JANUARY, UPPERCASE_MONTHLONG_FEBRUARY, UPPERCASE_MONTHLONG_MARCH, UPPERCASE_MONTHLONG_APRIL, UPPERCASE_MONTHLONG_MAY, UPPERCASE_MONTHLONG_JUNE,
	UPPERCASE_MONTHLONG_JULY, UPPERCASE_MONTHLONG_AUGUST, UPPERCASE_MONTHLONG_SEPTEMBER, UPPERCASE_MONTHLONG_OCTOBER, UPPERCASE_MONTHLONG_NOVEMBER, UPPERCASE_MONTHLONG_DECEMBER};

const string StringConvertor::LOWERCASE_MONTHSHORT_ARRAY[12] = {LOWERCASE_MONTHSHORT_JANUARY, LOWERCASE_MONTHSHORT_FEBRUARY, LOWERCASE_MONTHSHORT_MARCH, LOWERCASE_MONTHSHORT_APRIL, LOWERCASE_MONTHSHORT_MAY, LOWERCASE_MONTHSHORT_JUNE,
	LOWERCASE_MONTHSHORT_JULY, LOWERCASE_MONTHSHORT_AUGUST, LOWERCASE_MONTHSHORT_SEPTEMBER, LOWERCASE_MONTHSHORT_OCTOBER, LOWERCASE_MONTHSHORT_NOVEMBER, LOWERCASE_MONTHSHORT_DECEMBER};

const string StringConvertor::LOWERCASE_MONTHLONG_ARRAY[12] = {LOWERCASE_MONTHLONG_JANUARY, LOWERCASE_MONTHLONG_FEBRUARY, LOWERCASE_MONTHLONG_MARCH, LOWERCASE_MONTHLONG_APRIL, LOWERCASE_MONTHLONG_MAY, LOWERCASE_MONTHLONG_JUNE,
	LOWERCASE_MONTHLONG_JULY, LOWERCASE_MONTHLONG_AUGUST, LOWERCASE_MONTHLONG_SEPTEMBER, LOWERCASE_MONTHLONG_OCTOBER, LOWERCASE_MONTHLONG_NOVEMBER, LOWERCASE_MONTHLONG_DECEMBER};



//@author A0115902N
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
		if (monthString == UPPERCASE_MONTHSHORT_ARRAY[monthCount - 1]||monthString == UPPERCASE_MONTHLONG_ARRAY[monthCount-1]
		|| monthString == LOWERCASE_MONTHSHORT_ARRAY[monthCount - 1]||monthString == LOWERCASE_MONTHLONG_ARRAY[monthCount-1]){
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
	if(entryYear < 1000){
		entryYear = entryYear + 2000;
	}
}

//@author A0115902N-reused
void StringConvertor::convertStringToNumber(string input, int& number){
	istringstream convertToNumber(input);
	if (!(convertToNumber >> number)) {
		number = 0;  
	}
}

