#include <sstream>
#include "EntryEditor.h"

EntryEditor::EntryEditor(){
};

int EntryEditor::getEntryNumber(string& entryComponents){
	size_t pos = 0;
	string numberString = entryComponents.substr(1, 1);
	entryComponents.erase(0, 2);
	pos = 0;
	_entryNumber = convertToNumber(numberString);
	return _entryNumber;
}

string EntryEditor::getMarker(string& entryComponents){
	_marker = entryComponents.substr(1, 2);
	entryComponents.erase(0, 4);
	_newInformation = entryComponents;
	return _marker;
}

int EntryEditor::convertToNumber(string numberString){
	int number;
	istringstream convertString(numberString);
	if (!(convertString >> number)) {
		number = 0; 
	}
	return number;
}

string EntryEditor::getName(){
	return _newInformation;
}

void EntryEditor::getTime(int& newStartHour, int& newStartMinute, int& newEndHour, int& newEndMinute){
	SeparateEntryComponents parseTime;
	parseTime.convertTime(_newInformation, newStartHour, newStartMinute, newEndHour, newEndMinute);
}

void EntryEditor::getDate(int& newDay, int& newMonth, int& newYear){
	SeparateEntryComponents parseDate;
	parseDate.convertDate(_newInformation, newDay, newMonth, newYear);
}

string EntryEditor::getLocation(){
	return _newInformation;
}