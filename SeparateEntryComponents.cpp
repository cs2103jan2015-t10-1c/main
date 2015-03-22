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

const string SeparateEntryComponents::DATE_MARKER = "-d";
const string SeparateEntryComponents::TIME_MARKER = "-t";
const string SeparateEntryComponents::LOCATION_MARKER = "-l";
const string SeparateEntryComponents::END_MARKER = ".";
const string SeparateEntryComponents::MONTH_ARRAY[12] = {MONTH_JANUARY, MONTH_FEBRUARY, MONTH_MARCH, MONTH_APRIL, MONTH_MAY, MONTH_JUNE,
	MONTH_JULY, MONTH_AUGUST, MONTH_SEPTEMBER, MONTH_OCTOBER, MONTH_NOVEMBER, MONTH_DECEMBER};

void SeparateEntryComponents::dissectCommand (string entryComponents, string& entryName, string& entryTime,
							 string& entryDate, string& entryLocation){
	size_t pos = 0;
	extractName(entryComponents, pos, entryName);
	extractTime(entryComponents, pos, entryTime);
	extractDate(entryComponents, pos, entryDate);
	extractLocation(entryComponents, pos, entryLocation);
}

void SeparateEntryComponents::extractName(string& entryComponents, size_t pos, string& entryName){
	if ((pos = entryComponents.find(TIME_MARKER)) != std::string::npos || (pos = entryComponents.find(DATE_MARKER)) != std::string::npos ||
		(pos = entryComponents.find(LOCATION_MARKER)) != std::string::npos||(pos = entryComponents.find(END_MARKER)) != std::string::npos) {
    	entryName = entryComponents.substr(1, pos-2);
    	entryComponents.erase(0, pos);
    	pos = 0;
	}
}

void SeparateEntryComponents::extractTime(string& entryComponents, size_t pos, string& entryTime){
	if (entryComponents[0] == TIME_MARKER[0] && entryComponents[1] == TIME_MARKER[1]){
		if ((pos = entryComponents.find(DATE_MARKER)) != std::string::npos ||
		   (pos = entryComponents.find(LOCATION_MARKER)) != std::string::npos ||(pos = entryComponents.find(END_MARKER)) != std::string::npos) {
    	entryTime = entryComponents.substr(3, pos-3);
    	entryComponents.erase(0, pos);
    	pos = 0;
		}
	}
}

void SeparateEntryComponents::extractDate(string& entryComponents, size_t pos, string& entryDate){
	if (entryComponents[0] == DATE_MARKER[0] && entryComponents[1] == DATE_MARKER[1]){
		if ((pos = entryComponents.find(TIME_MARKER)) != std::string::npos ||
		   (pos = entryComponents.find(LOCATION_MARKER)) != std::string::npos||(pos = entryComponents.find(END_MARKER)) != std::string::npos) {
    	entryDate = entryComponents.substr(3, pos-3);
    	entryComponents.erase(0, pos);
    	pos = 0;
		}
	}
}

void SeparateEntryComponents::extractLocation(string& entryComponents, size_t pos, string& entryLocation){
	if (entryComponents[0] == LOCATION_MARKER[0] && entryComponents[1] == LOCATION_MARKER[1]){
		if ((pos = entryComponents.find(TIME_MARKER)) != std::string::npos ||
		   (pos = entryComponents.find(DATE_MARKER)) != std::string::npos||(pos = entryComponents.find(END_MARKER)) != std::string::npos) {
    	entryLocation = entryComponents.substr(3, pos-3);
    	entryComponents.erase(0, pos);
    	pos = 0;
		}
	}
}

void SeparateEntryComponents::convertTime(string entryTime, int& startHour, int& startMin, int& endHour, int& endMin){
	istringstream iss(entryTime);
	string start;
	string end;
	iss >> start >> end;

	size_t startDot = start.find_first_of(".");
	string startHourString = start.substr(0, startDot);
	istringstream convertStartHour(startHourString);
	if (!(convertStartHour >> startHour)) {
		startHour = 0;  
	}
	
	string startMinString = start.substr(startDot+1, string::npos);
	istringstream convertStartMin(startMinString);
	if (!(convertStartMin >> startMin)) {
		startMin = 0;  
	}
	
	size_t endDot = end.find_first_of("."); 
	string endHourString = end.substr(0, endDot);
	istringstream convertEndHour(endHourString);
	if (!(convertEndHour >> endHour)) {
		endHour = 0;  
	}

	string endMinString = end.substr(endDot+1, string::npos);
	istringstream convertEndMin(endMinString);
	if (!(convertEndMin >> endMin)) {
		endMin = 0;  
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