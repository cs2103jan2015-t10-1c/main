#include <sstream>
#include "SeparateEntryComponents.h"

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

const string SeparateEntryComponents::STARTDATE_MARKER = "from";
const string SeparateEntryComponents::LOCATION_MARKER = "at";
const string SeparateEntryComponents::NAME_MARKER = ".";
const string SeparateEntryComponents::ENDDATE_MARKER = "on";
const string SeparateEntryComponents::TAG_MARKER = "#";
const string SeparateEntryComponents::MONTH_ARRAY[12] = {MONTH_JANUARY, MONTH_FEBRUARY, MONTH_MARCH, MONTH_APRIL, MONTH_MAY, MONTH_JUNE,
	MONTH_JULY, MONTH_AUGUST, MONTH_SEPTEMBER, MONTH_OCTOBER, MONTH_NOVEMBER, MONTH_DECEMBER};

void SeparateEntryComponents::dissectCommand (string entryComponents, string& entryName, string& entryStartTime, string& entryEndTime,
							 string& entryStartDate, string& entryEndDate, string& entryLocation, string& tag){
	size_t pos = 0;
	extractName(entryComponents, pos, entryName);

	if (entryComponents[0] == STARTDATE_MARKER[0] && entryComponents[1] == STARTDATE_MARKER[1]){
		entryComponents.erase(0, STARTDATE_MARKER.size() + 1);
		extractDate(entryComponents, pos, entryStartDate);
		extractTime(entryComponents, pos, entryStartTime);
		entryComponents = entryComponents.substr(3, entryComponents.size()-1);
		extractDate(entryComponents, pos, entryEndDate);
		extractTime(entryComponents, pos, entryEndTime);
	}
	else{
		extractTime(entryComponents, pos, entryStartTime);
		extractTime(entryComponents, pos, entryEndTime);
		if (entryComponents[0] == ENDDATE_MARKER[0] && entryComponents[1] == ENDDATE_MARKER[1]){
			entryComponents.erase(0,3);
			extractDate(entryComponents, pos, entryStartDate);
		}
	}
	if (entryComponents[0] == LOCATION_MARKER[0] && entryComponents[1] == LOCATION_MARKER[1]){
		extractLocation(entryComponents, pos, entryLocation);
	}

	if (entryComponents[0] == TAG_MARKER[0]){
		extractTag(entryComponents, pos, tag);
	}
}

void SeparateEntryComponents::extractTag(string& entryComponents, size_t pos, string& entryTag){
	pos = entryComponents.size();
	entryTag = entryComponents.substr(0, pos);
    entryComponents.erase(0, pos);
}
	
void SeparateEntryComponents::extractName(string& entryComponents, size_t pos, string& entryName){
	pos = entryComponents.find(NAME_MARKER);
    entryName = entryComponents.substr(1, pos-1);
    entryComponents = entryComponents.substr(pos+2, entryComponents.size() - 1);
}

void SeparateEntryComponents::extractTime(string& entryComponents, size_t pos, string& entryTime){
	int index = entryComponents.find(' ');
    entryTime = entryComponents.substr(0, index);
    entryComponents.erase(0, index+1);
}

void SeparateEntryComponents::extractDate(string& entryComponents, size_t pos, string& entryDate){
    int index = entryComponents.find(' ');
	index = entryComponents.find(' ', index + 1);
	index = entryComponents.find(' ', index + 1);
	entryDate = entryComponents.substr(0, index);
    entryComponents.erase(0, index+1);
}


void SeparateEntryComponents::extractLocation(string& entryComponents, size_t pos, string& entryLocation){
    int leftBound = entryComponents.find(' ');
	int rightBound = entryComponents.find(' ', leftBound + 1);
	entryLocation = entryComponents.substr(leftBound+1, rightBound-leftBound);
    entryComponents.erase(0, rightBound+1);
}

void SeparateEntryComponents::convertTime(string entryTime, int& entryHour, int& entryMin){
	istringstream iss(entryTime);
	string start;
	string end;
	iss >> start >> end;

	size_t startDot = start.find_first_of(".");
	string startHourString = start.substr(0, startDot);
	istringstream convertStartHour(startHourString);
	if (!(convertStartHour >> entryHour)) {
		entryHour = 0;  
	}
	
	string startMinString = start.substr(startDot+1, string::npos);
	istringstream convertStartMin(startMinString);
	if (!(convertStartMin >> entryMin)) {
		entryMin = 0;  
	}

	return;
}

void SeparateEntryComponents::convertDate(string entryDate, int& day, int& month, int& year){
	istringstream iss(entryDate);
	string dayString;
	string monthString;
	string yearString;

	iss >> dayString
		>> monthString
		>> yearString;

	//day
	istringstream convertDay(dayString);
	if (!(convertDay >> day)) {
		day = 0;  
	}

	//month
	bool found = false;
	int monthCount = 1;
	while (!found){
		if (monthString == MONTH_ARRAY[monthCount-1]){
			found = true;
			month = monthCount;
		}
		else{
			monthCount++;
		}
	}

	//year
	istringstream convertYear(yearString);
	if (!(convertYear >> year)) {
		year = 0;  
	}
}