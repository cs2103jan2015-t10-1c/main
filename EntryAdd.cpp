#include <sstream>
#include "EntryAdd.h"
#include <Windows.h>

const int EntryAdd::BLANK_SPACE_COUNT = 1;
const string EntryAdd::AT_MARKER = "at";
const string EntryAdd::BY_MARKER = "by";
const string EntryAdd::BLANK_SPACE = " ";
const string EntryAdd::FROM_MARKER = "from";
const string EntryAdd::FULLSTOP_MARKER = ".";
const string EntryAdd::ON_MARKER = "on";
const string EntryAdd::TAG_MARKER = "#";
const string EntryAdd::TO_MARKER = "to";


//@author A0116660L
void EntryAdd::dissectCommand (string entryComponents, string& entryName, string& entryStartDate, string& entryStartTime,
							   string& entryEndDate, string& entryEndTime, string& entryLocation, vector<string>& tag){
	//extract name of event
	extractName(entryComponents, entryName);

	//extract dates and time (2 dates)
	if (entryComponents[0] == FROM_MARKER[0] && entryComponents[1] == FROM_MARKER[1]
		&& entryComponents[2] == FROM_MARKER[2] && entryComponents[3] == FROM_MARKER[3]){
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

	//extract deadline (1 date 1 time)
	else if(entryComponents[0] == BY_MARKER[0] && entryComponents[1] == BY_MARKER[1]){
		int datePosition = BY_MARKER.size() + BLANK_SPACE_COUNT;
		entryComponents.erase(0, datePosition);
		extractDate(entryComponents, entryStartDate);
		entryEndDate = entryStartDate;
		extractTime(entryComponents, entryStartTime);
		entryEndTime = entryStartTime;
	}

	//only name and location, and maybe tags
	else if (entryComponents[0] == AT_MARKER[0] && entryComponents[1] == AT_MARKER[1]){
		extractLocation(entryComponents, entryLocation);
		if (entryComponents[0] == TAG_MARKER[0]){
			extractTag(entryComponents, tag);
		}
		return;
	}

	//only name and tags
	else if (entryComponents[0] == TAG_MARKER[0]){
		extractTag(entryComponents, tag);
		return;
	}

	//extract date and time (1 date)
	else if (entryComponents[0] == ON_MARKER[0] && entryComponents[1] == ON_MARKER[1]){
		entryComponents = entryComponents.substr(ON_MARKER.size() + BLANK_SPACE_COUNT);
		extractDate(entryComponents, entryStartDate);
		//for entry with only one date, the end date is the same as starting date
		entryEndDate = entryStartDate;
		extractTime(entryComponents, entryStartTime);
		int endTimePosition = TO_MARKER.size() + BLANK_SPACE_COUNT;
		int endOfLine = entryComponents.size() - 1;
		entryComponents = entryComponents.substr(endTimePosition, endOfLine);
		extractTime(entryComponents, entryEndTime);
	}
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Wrong parameters are given!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}

	if (entryComponents[0] == AT_MARKER[0] && entryComponents[1] == AT_MARKER[1]){
		extractLocation(entryComponents, entryLocation);
	}

	if (entryComponents[0] == TAG_MARKER[0]){
		extractTag(entryComponents, tag);
	}
}

void EntryAdd::extractTag(string& entryComponents, vector<string>& entryTag){
	int endOfTag = entryComponents.size();
	string tag;
	int tracker;
	for (tracker = 0; tracker <= endOfTag; tracker++){
		if (entryComponents[tracker] == ' ' || tracker == endOfTag){
			tag = entryComponents.substr(0, tracker);
			entryComponents = entryComponents.erase(0, tracker + 1);
			tracker = 0;
			endOfTag = entryComponents.size();
			entryTag.push_back(tag);
		}
	}
}
	
void EntryAdd::extractName(string& entryComponents, string& entryName){
	int endOfName = entryComponents.find_first_of(FULLSTOP_MARKER) - 1;
	//remove blank space
	entryName = entryComponents.substr(1, endOfName);
	int startOfRemainder = endOfName + FULLSTOP_MARKER.size() + BLANK_SPACE_COUNT + 1;
	int endOfRemainder = entryComponents.size() - 1;
	if(startOfRemainder > endOfRemainder){
		return;
	}
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
	int endOfLocation = entryComponents.find(TAG_MARKER, startOfLocation);
	entryLocation = entryComponents.substr(startOfLocation, endOfLocation - startOfLocation);
    entryComponents.erase(0, endOfLocation);
}

//@author A0115902N
void EntryAdd::convertTime(string entryTime, int& entryHour, int& entryMin){
	StringConvertor parseTime;
	parseTime.convertTime(entryTime, entryHour, entryMin);
}

void EntryAdd::convertDate(string entryDate, int& day, int& month, int& year){
	StringConvertor parseDate;
	parseDate.convertDate(entryDate, day, month, year);
}