#include <sstream>
#include "EntryEdit.h"

EntryEdit::EntryEdit(){
};

int EntryEdit::getEntryNumber(string& entryComponents){
	entryComponents = entryComponents.substr(1);
	int pos = entryComponents.find_first_of(' ');
	string numberString = entryComponents.substr(0, pos);
	entryComponents.erase(0, pos+1);
	_entryNumber = convertToNumber(numberString);
	return _entryNumber;
}

string EntryEdit::getMarker(string& entryComponents){
	_marker = entryComponents.substr(0, entryComponents.find_first_of(' '));
	entryComponents = entryComponents.substr(entryComponents.find_first_of(' ') + 1);
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

string EntryEdit::getStatus(){
	return _newInformation;
}

void EntryEdit::getTime(int& newStartHour, int& newStartMinute, int& newEndHour, int& newEndMinute){
	StringConvertor parseTime;
	string newStartTime;
	string newEndTime;
	parseTime.extractStringTime(_newInformation, newStartTime);
	if(_newInformation.empty()){
		newEndTime = newStartTime;
	}
	parseTime.extractStringTime(_newInformation, newEndTime);
	parseTime.convertTime(newStartTime, newStartHour, newStartMinute);
	parseTime.convertTime(newEndTime, newEndHour, newEndMinute);
}

void EntryEdit::getDate(int& newStartDay, int& newStartMonth, int& newStartYear, int& newEndDay, int& newEndMonth, int& newEndYear){
	StringConvertor parseDate;
	string startDate;
	string endDate;
	parseDate.extractStringDate(_newInformation, startDate);
	if(_newInformation.empty()){
		endDate = startDate;
	}
	else{
		parseDate.extractStringDate(_newInformation, endDate);
	}
	parseDate.convertDate(startDate, newStartDay, newStartMonth, newStartYear);
	parseDate.convertDate(endDate, newEndDay, newEndMonth, newEndYear);
}

string EntryEdit::getLocation(){
	return _newInformation;
}
