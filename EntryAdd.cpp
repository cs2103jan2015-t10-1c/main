#include <sstream>
#include "EntryAdd.h"


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

const string EntryAdd::MONTH_ARRAY[12] = {MONTH_JANUARY, MONTH_FEBRUARY, MONTH_MARCH, MONTH_APRIL, MONTH_MAY, MONTH_JUNE,
	MONTH_JULY, MONTH_AUGUST, MONTH_SEPTEMBER, MONTH_OCTOBER, MONTH_NOVEMBER, MONTH_DECEMBER};

const int EntryAdd::BLANK_SPACE_COUNT = 1;
const string EntryAdd::AT_MARKER = "at";
const string EntryAdd::BLANK_SPACE = " ";
const string EntryAdd::FROM_MARKER = "from";
const string EntryAdd::FULLSTOP_MARKER = ".";
const string EntryAdd::ON_MARKER = "on";
const string EntryAdd::TAG_MARKER = "#";
const string EntryAdd::TO_MARKER = "to";


void EntryAdd::dissectCommand (string entryComponents, string& entryName, string& entryStartTime, string& entryEndTime,
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
		extractDate(entryComponents, entryStartDate);
		//for entry with only one date, the end date is the same as starting date
		entryEndDate = entryStartDate;
		extractTime(entryComponents, entryStartTime);
		int endTimePosition = TO_MARKER.size() + BLANK_SPACE_COUNT;
		int endOfLine = entryComponents.size() - 1;
		entryComponents = entryComponents.substr(endTimePosition, endOfLine);
		extractTime(entryComponents, entryEndTime);
	}

	if (entryComponents[0] == AT_MARKER[0] && entryComponents[1] == AT_MARKER[1]){
		extractLocation(entryComponents, entryLocation);
	}

	if (entryComponents[0] == TAG_MARKER[0]){
		extractTag(entryComponents, tag);
	}
}

void EntryAdd::extractTag(string& entryComponents, string& entryTag){
	int endOfTag = entryComponents.size();
	Entry tag;
	int tracker;
	for (tracker = 0; tracker <= endOfTag; tracker++){
		if (entryComponents[tracker] == ' '){
			entryTag = entryComponents.substr(0, tracker - 1);
			entryComponents = entryComponents.erase(0, tracker + 1);
			tracker = 0;
			endOfTag = entryComponents.size();
			cout << "Tag: " << entryTag << endl;
			tag.addTag(entryTag);
		}

		else if (tracker == endOfTag){
			entryTag = entryComponents.substr(0, tracker);
			entryComponents = entryComponents.erase(0, tracker + 1);
			tracker = 0;
			endOfTag = entryComponents.size();
			cout << "Tag: " << entryTag << endl;
			tag.addTag(entryTag);
		}
	}
}
	
void EntryAdd::extractName(string& entryComponents, string& entryName){
	int endOfName = entryComponents.find(FULLSTOP_MARKER) - 1;
	entryName = entryComponents.substr(1, endOfName);
	int startOfRemainder = endOfName + FULLSTOP_MARKER.size() + BLANK_SPACE_COUNT + 1;
	int endOfRemainder = entryComponents.size() - 1;
	entryComponents = entryComponents.substr(startOfRemainder, endOfRemainder);
}

void EntryAdd::extractTime(string& entryComponents, string& entryTime){
	StringConvertor timeExtractor;
	timeExtractor.extractStringTime(entryComponents, entryTime);
}

void EntryAdd::extractDate(string& entryComponents, string& entryDate){
	StringConvertor dateExtractor;
	dateExtractor.extractStringDate(entryComponents, entryDate);
}

void EntryAdd::extractLocation(string& entryComponents, string& entryLocation){
	int startOfLocation = entryComponents.find(BLANK_SPACE) + BLANK_SPACE_COUNT;
	int endOfLocation = entryComponents.find(BLANK_SPACE, startOfLocation);
	entryLocation = entryComponents.substr(startOfLocation, endOfLocation - startOfLocation);
    entryComponents.erase(0, endOfLocation + BLANK_SPACE_COUNT);
}

void EntryAdd::convertTime(string entryTime, int& entryHour, int& entryMin){
	StringConvertor parseTime;
	parseTime.convertTime(entryTime, entryHour, entryMin);
}

void EntryAdd::convertDate(string entryDate, int& day, int& month, int& year){
	StringConvertor parseDate;
	parseDate.convertDate(entryDate, day, month, year);
}