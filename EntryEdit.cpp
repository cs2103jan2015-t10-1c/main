#include <sstream>
#include "EntryEdit.h"

EntryEdit::EntryEdit(){
};

int EntryEdit::getEntryNumber(string& entryComponents){
	size_t pos = 0;
	string numberString = entryComponents.substr(1, 1);
	entryComponents.erase(0, 2);
	pos = 0;
	_entryNumber = convertToNumber(numberString);
	return _entryNumber;
}

string EntryEdit::getMarker(string& entryComponents){
	_marker = entryComponents.substr(1, 2);
	entryComponents.erase(0, 4);
	_newInformation = entryComponents;
	return _marker;
}

int EntryEdit::convertToNumber(string numberString){
	int number;
	istringstream convertString(numberString);
	if (!(convertString >> number)) {
		number = 0; 
	}
	return number;
}

string EntryEdit::getName(){
	return _newInformation;
}

void EntryEdit::getTime(int& newStartHour, int& newStartMinute, int& newEndHour, int& newEndMinute){
	StringConvertor parseTime;
	string newStartTime;
	string newEndTime;
	parseTime.extractStringTime(_newInformation, newStartTime);
	parseTime.extractStringTime(_newInformation, newEndTime);
	parseTime.convertTime(newStartTime, newStartHour, newStartMinute);
	parseTime.convertTime(newEndTime, newEndHour, newEndMinute);
}

void EntryEdit::getDate(int& newDay, int& newMonth, int& newYear){
	StringConvertor parseDate;
	parseDate.convertDate(_newInformation, newDay, newMonth, newYear);
}

string EntryEdit::getLocation(){
	return _newInformation;
}