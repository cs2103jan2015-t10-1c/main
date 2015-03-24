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

const string SeparateEntryComponents::MONTH_ARRAY[12] = {MONTH_JANUARY, MONTH_FEBRUARY, MONTH_MARCH, MONTH_APRIL, MONTH_MAY, MONTH_JUNE,
	MONTH_JULY, MONTH_AUGUST, MONTH_SEPTEMBER, MONTH_OCTOBER, MONTH_NOVEMBER, MONTH_DECEMBER};

const int SeparateEntryComponents::BLANK_SPACE_COUNT = 1;
const string SeparateEntryComponents::AT_MARKER = "at";
const string SeparateEntryComponents::BLANK_SPACE = " ";
const string SeparateEntryComponents::FROM_MARKER = "from";
const string SeparateEntryComponents::FULLSTOP_MARKER = ".";
const string SeparateEntryComponents::ON_MARKER = "on";
const string SeparateEntryComponents::TAG_MARKER = "#";
const string SeparateEntryComponents::TO_MARKER = "to";


void SeparateEntryComponents::dissectCommand (string entryComponents, string& entryName, string& entryStartTime, string& entryEndTime,
				                              string& entryStartDate, string& entryEndDate, string& entryLocation, string& tag){
	extractName(entryComponents, entryName);

	if (entryComponents[0] == FROM_MARKER[0] && entryComponents[1] == FROM_MARKER[1]){
		int startDatePosition = FROM_MARKER.size() + BLANK_SPACE_COUNT;
		entryComponents.erase(0, startDatePosition);
		extractDate(entryComponents, entryStartDate);
		extractTime(entryComponents, entryStartTime);
		int endDatePosition = TO_MARKER.size() + BLANK_SPACE_COUNT;
		int endOfLine = entryComponents.size() - 1;
		entryComponents = entryComponents.substr(endDatePosition, endOfLine);
		extractDate(entryComponents, entryEndDate);
		extractTime(entryComponents, entryEndTime);
	}

	else{
		extractTime(entryComponents, entryStartTime);
		extractTime(entryComponents, entryEndTime);
		if (entryComponents[0] == ON_MARKER[0] && entryComponents[1] == ON_MARKER[1]){
			int datePosition = ON_MARKER.size() + BLANK_SPACE_COUNT;
			entryComponents.erase(0, datePosition);
			extractDate(entryComponents, entryStartDate);
		}
	}

	if (entryComponents[0] == AT_MARKER[0] && entryComponents[1] == AT_MARKER[1]){
		extractLocation(entryComponents, entryLocation);
	}

	if (entryComponents[0] == TAG_MARKER[0]){
		extractTag(entryComponents, tag);
	}
}

void SeparateEntryComponents::extractTag(string& entryComponents, string& entryTag){
	int endOfTag = entryComponents.size();
	entryTag = entryComponents.substr(0, endOfTag);
	entryComponents.erase(0, endOfTag);
}
	
void SeparateEntryComponents::extractName(string& entryComponents, string& entryName){
	int endOfName = entryComponents.find(FULLSTOP_MARKER) - 1;
	entryName = entryComponents.substr(1, endOfName);
	int startOfRemainder = endOfName + FULLSTOP_MARKER.size() + BLANK_SPACE_COUNT + 1;
	int endOfRemainder = entryComponents.size() - 1;
	entryComponents = entryComponents.substr(startOfRemainder, endOfRemainder);
}

void SeparateEntryComponents::extractTime(string& entryComponents, string& entryTime){
	int endOfTime = entryComponents.find(BLANK_SPACE);
	entryTime = entryComponents.substr(0, endOfTime);
    entryComponents.erase(0, endOfTime + BLANK_SPACE_COUNT);
}

void SeparateEntryComponents::extractDate(string& entryComponents, string& entryDate){
    int endOfDay = entryComponents.find(BLANK_SPACE);
	int endOfMonth = entryComponents.find(BLANK_SPACE, endOfDay + BLANK_SPACE_COUNT);
	int endOfYear = entryComponents.find(BLANK_SPACE, endOfMonth + BLANK_SPACE_COUNT);
	entryDate = entryComponents.substr(0, endOfYear);
	entryComponents.erase(0, endOfYear + BLANK_SPACE_COUNT);
}

void SeparateEntryComponents::extractLocation(string& entryComponents, string& entryLocation){
	int startOfLocation = entryComponents.find(BLANK_SPACE) + BLANK_SPACE_COUNT;
	int endOfLocation = entryComponents.find(BLANK_SPACE, startOfLocation);
	entryLocation = entryComponents.substr(startOfLocation, endOfLocation - startOfLocation);
    entryComponents.erase(0, endOfLocation + BLANK_SPACE_COUNT);
}

void SeparateEntryComponents::convertTime(string entryTime, int& entryHour, int& entryMin){
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
		if (monthString == MONTH_ARRAY[monthCount - 1]){
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