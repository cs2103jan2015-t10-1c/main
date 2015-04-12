#include <sstream>
#include "EntryEdit.h"

const int EntryEdit::BLANK_SPACE_COUNT = 1;
const int EntryEdit::INITIAL_POSITION = 0;
const string EntryEdit::NAME_MARKER = "name";
const string EntryEdit::DATE_MARKER = "date";
const string EntryEdit::TIME_MARKER = "time";
const string EntryEdit::LOCATION_MARKER = "place";
const string EntryEdit::STATUS_MARKER = "status";
const string EntryEdit::TAG_ADD_MARKER = "add";
const string EntryEdit::TAG_REMOVE_MARKER = "remove";
const string EntryEdit::FULLSTOP_MARKER = ". ";

//@author A0115656A
EntryEdit::EntryEdit(bool isScheduled){
	_isScheduled = isScheduled;
	_isEdited = true;
	_dateEdited = false;
	_timeEdited = false;
	_tagAdded = false;
	_tagRemoved = false;
};

int EntryEdit::getEntryNumber(string& entryComponents){
	//remove blank space
	entryComponents = entryComponents.substr(1);
	int pos = entryComponents.find_first_of(' ');
	string numberString = entryComponents.substr(0, pos);
	entryComponents.erase(0, pos+1);
	_entryNumber = convertToNumber(numberString);
	return _entryNumber;
}

//@author A0116660L
//extract the markers and strings of new information, and push them into _changesList vector
void EntryEdit::extractMarkerInfo(string entryComponents) {
	bool isEndOfEdit = false;
	while (!isEndOfEdit) {
		_NEW_CHANGES currentChange;
		
		//extract new name
		if (entryComponents[INITIAL_POSITION] == NAME_MARKER[INITIAL_POSITION] && entryComponents[1] == NAME_MARKER[1]
			&& entryComponents[2] == NAME_MARKER[2] && entryComponents[3] == NAME_MARKER[3]) {
			extractName(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == DATE_MARKER[0] && entryComponents[1] == DATE_MARKER[1]
				   && entryComponents[2] == DATE_MARKER[2] && entryComponents[3] == DATE_MARKER[3]) {
		  //extract new date
			extractDate(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == TIME_MARKER[0] && entryComponents[1] == TIME_MARKER[1]
				   && entryComponents[2] == TIME_MARKER[2] && entryComponents[3] == TIME_MARKER[3]) {
		  //extract new time
			extractTime(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == LOCATION_MARKER[0] && entryComponents[1] == LOCATION_MARKER[1] 
				   && entryComponents[2] == LOCATION_MARKER[2] && entryComponents[3] == LOCATION_MARKER[3] 
				   && entryComponents[4] == LOCATION_MARKER[4]) {
		  //extract new location
			extractLocation(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == STATUS_MARKER[0] && entryComponents[1] == STATUS_MARKER[1] 
				   && entryComponents[2] == STATUS_MARKER[2] && entryComponents[3] == STATUS_MARKER[3] 
				   && entryComponents[4] == STATUS_MARKER[4] && entryComponents[5] == STATUS_MARKER[5]) {
		  //extract new status
			extractStatus(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == TAG_ADD_MARKER[0] && entryComponents[1] == TAG_ADD_MARKER[1] 
				   && entryComponents[2] == TAG_ADD_MARKER[2]) {
		  //extract new added tags
			extractAddedTag(entryComponents, currentChange, isEndOfEdit);
		} else if (entryComponents[0] == TAG_REMOVE_MARKER[0] && entryComponents[1] == TAG_REMOVE_MARKER[1] 
				   && entryComponents[2] == TAG_REMOVE_MARKER[2] && entryComponents[3] == TAG_REMOVE_MARKER[3] 
				   && entryComponents[4] == TAG_REMOVE_MARKER[4] && entryComponents[5] == TAG_REMOVE_MARKER[5]) {
		  //extract new removed tags
			extractRemovedTag(entryComponents, currentChange, isEndOfEdit);
		} else {
		  //unrecognised command
			_isEdited = false;
			isEndOfEdit = true;
		}
	}
}

void EntryEdit::extractName(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit) {
	//push current change into vector
	currentChange._editedField = Name;
	//remove the word 'name' and blank space
	entryComponents = entryComponents.substr(NAME_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfName = entryComponents.find(FULLSTOP_MARKER);

	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfName == string::npos) {
		endOfName = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfName);
	_changesList.push_back(currentChange);
	
	//extract remainder
	extractRemainder(endOfName, entryComponents, isEndOfEdit);
}

//@author A0115902N
void EntryEdit::extractDate(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit){
	//push current change into vector
	currentChange._editedField = Date;
	//remove the word 'date' and blank space
	entryComponents = entryComponents.substr(DATE_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfDate = entryComponents.find(FULLSTOP_MARKER);
	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfDate == string::npos){
		endOfDate = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfDate);
	_changesList.push_back(currentChange);
	_dateEdited = true;

	//extract remainder
	extractRemainder(endOfDate, entryComponents, isEndOfEdit);
}

void EntryEdit::extractTime(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit){
	//push current change into vector
	currentChange._editedField = Time;
	//remove the word 'time' and blank space
	entryComponents = entryComponents.substr(TIME_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfTime = entryComponents.find(FULLSTOP_MARKER);
	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfTime == string::npos){
		endOfTime = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfTime);
	_changesList.push_back(currentChange);
	_timeEdited = true;

	//extract remainder
	extractRemainder(endOfTime, entryComponents, isEndOfEdit);
}

//@author A0116660L
void EntryEdit::extractLocation(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit) {
	//push current change into vector
	currentChange._editedField = Location;
	//remove the word 'place' and blank space
	entryComponents = entryComponents.substr(LOCATION_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfLocation = entryComponents.find(FULLSTOP_MARKER);

	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfLocation == string::npos) {
		endOfLocation = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfLocation);
	_changesList.push_back(currentChange);
	
	//extract remainder
	extractRemainder(endOfLocation, entryComponents, isEndOfEdit);
}

void EntryEdit::extractStatus(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit) {
	//push current change into vector
	currentChange._editedField = Status;
	//remove the word 'status' and blank space
	entryComponents = entryComponents.substr(STATUS_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfStatus = entryComponents.find(FULLSTOP_MARKER);

	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfStatus == string::npos) {
		endOfStatus = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfStatus);
	_changesList.push_back(currentChange);
	
	//extract remainder
	extractRemainder(endOfStatus, entryComponents, isEndOfEdit);
}

//@author A0115656A
void EntryEdit::extractAddedTag(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit){
	//push current change into vector
	currentChange._editedField = TagAdd;
	//remove the word 'add' and blank space
	entryComponents = entryComponents.substr(TAG_ADD_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfAddedTag = entryComponents.find(FULLSTOP_MARKER);
	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfAddedTag == string::npos){
		endOfAddedTag = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfAddedTag);
	_changesList.push_back(currentChange);
	_tagAdded = true;
	
	//extract remainder
	extractRemainder(endOfAddedTag, entryComponents, isEndOfEdit);
}

void EntryEdit::extractRemovedTag(string& entryComponents, _NEW_CHANGES currentChange, bool& isEndOfEdit){
	//push current change into vector
	currentChange._editedField = TagRemove;
	//remove the word 'remove' and blank space
	entryComponents = entryComponents.substr(TAG_REMOVE_MARKER.size() + BLANK_SPACE_COUNT);
	int endOfRemovedTag = entryComponents.find(FULLSTOP_MARKER);
	//if FULLSTOP_MARKER is not found, then it is already the end of string
	if (endOfRemovedTag == string::npos){
		endOfRemovedTag = entryComponents.size();
	}
	currentChange._newInformation = entryComponents.substr(0, endOfRemovedTag);
	_changesList.push_back(currentChange);
	_tagRemoved = true;

	//extract remainder
	extractRemainder(endOfRemovedTag, entryComponents, isEndOfEdit);
}

void EntryEdit::extractRemainder(int endOfField, string& entryComponents, bool& isEndOfEdit){
	int startOfRemainder = endOfField + BLANK_SPACE_COUNT + 1;
	if (startOfRemainder < entryComponents.size()){
		entryComponents = entryComponents.substr(startOfRemainder);
	}
	else {
		isEndOfEdit = true;
	}
}

//@author A0115902N
int EntryEdit::convertToNumber(string numberString){
	int number;
	istringstream convertString(numberString);
	if (!(convertString >> number)) {
		number = 0; 
	}
	return number;
}

string EntryEdit::getName(){
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++){
		if (iter->_editedField == Name){
			return iter->_newInformation;
		}
	}
	return "";
}

void EntryEdit::getDate(int& newStartDay, int& newStartMonth, int& newStartYear, int& newEndDay, int& newEndMonth, int& newEndYear){
	string newDate;
	//store the new date(s) into the string newDate
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++){
		if (iter->_editedField == Date){
			 newDate = iter->_newInformation;
			 break;
		}
	}
	
	StringConvertor parseDate;
	string startDate;
	string endDate;
	parseDate.extractStringDate(newDate, startDate);
	if(newDate.empty()){
		endDate = startDate;
	}
	else{
		parseDate.extractStringDate(newDate, endDate);
	}
	parseDate.convertDate(startDate, newStartDay, newStartMonth, newStartYear);
	parseDate.convertDate(endDate, newEndDay, newEndMonth, newEndYear);
}

void EntryEdit::getTime(int& newStartHour, int& newStartMinute, int& newEndHour, int& newEndMinute){
	string newTime;
	//store the new date(s) into the string newDate
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++){
		if (iter->_editedField == Time){
			 newTime = iter->_newInformation;
			 break;
		}
	}
	
	StringConvertor parseTime;
	string newStartTime;
	string newEndTime;
	parseTime.extractStringTime(newTime, newStartTime);
	if(newTime.empty()){
		newEndTime = newStartTime;
	}
	parseTime.extractStringTime(newTime, newEndTime);
	parseTime.convertTime(newStartTime, newStartHour, newStartMinute);
	parseTime.convertTime(newEndTime, newEndHour, newEndMinute);
}

//@author A0116660L
string EntryEdit::getLocation() {
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++) {
		if (iter->_editedField == Location) {
			return iter->_newInformation;
		}
	}
	return "";
}

string EntryEdit::getStatus() {
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++) {
		if (iter->_editedField == Status) {
			return iter->_newInformation;
		}
	}
	return "";
}

//@author A0115656A
void EntryEdit::addTag(Entry& editedEntry, ostringstream& oss){
	string addedTags;
	//store the added tags into the string addedTags
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++){
		if (iter->_editedField == TagAdd){
			addedTags = iter->_newInformation;
			break;
		}
	}
	oss << addedTags << endl;

	int endOfTag = addedTags.size();
	string tag;
	int tracker;
	for (tracker = 0; tracker <= endOfTag; tracker++){
		if (addedTags[tracker] == ' ' || tracker == endOfTag){
			tag = addedTags.substr(0, tracker);
			addedTags = addedTags.erase(0, tracker + BLANK_SPACE_COUNT);
			tracker = 0;
			endOfTag = addedTags.size();
			editedEntry.addTag(tag);
		}
	}
}

void EntryEdit::removeTag(Entry& editedEntry, ostringstream& oss){
	string removedTags;
	//store the removed tags into the string removedTags
	vector<_NEW_CHANGES>::iterator iter;
	for (iter = _changesList.begin(); iter < _changesList.end(); iter++){
		if (iter->_editedField == TagRemove){
			removedTags = iter->_newInformation;
			break;
		}
	}
	oss << removedTags << endl;

	int endOfTag = removedTags.size();
	string tag;
	int tracker;
	for (tracker = 0; tracker <= endOfTag; tracker++){
		if (removedTags[tracker] == ' ' || tracker == endOfTag){
			tag = removedTags.substr(0, tracker);
			removedTags = removedTags.erase(0, tracker + BLANK_SPACE_COUNT);
			tracker = 0;
			endOfTag = removedTags.size();
			editedEntry.removeTag(tag);
		}
	}
}

bool EntryEdit::getEditStatus(){
	return _isEdited;
}

bool EntryEdit::getDateEditStatus(){
	return _dateEdited;
}

bool EntryEdit::getTimeEditStatus(){
	return _timeEdited;
}

bool EntryEdit::getTagAddedStatus(){
	return _tagAdded;
}

bool EntryEdit::getTagRemovedStatus(){
	return _tagRemoved;
}