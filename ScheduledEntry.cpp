#include "ScheduledEntry.h"
#include <iostream>
#include <fstream>

//Static variables that cannot be initialised in the header file
const string ScheduledEntry::FEEDBACK_ADDED = "added ";
const string ScheduledEntry::FEEDBACK_FROM = " from ";
const string ScheduledEntry::FEEDBACK_TO = " to ";
const string ScheduledEntry::FEEDBACK_AT = " at ";
const string ScheduledEntry::FEEDBACK_EDITED = "edited ";
const string ScheduledEntry::FEEDBACK_DELETED = "This entry has been deleted:";
const string ScheduledEntry::FEEDBACK_INVALID_TYPE = "Invalid Type!";

const string ScheduledEntry::NAME_MARKER = "name";
const string ScheduledEntry::DATE_MARKER = "date";
const string ScheduledEntry::TIME_MARKER = "time";
const string ScheduledEntry::LOCATION_MARKER = "place";
const string ScheduledEntry::STATUS_MARKER = "status";

const string ScheduledEntry::BORDER = "- - - - - - - - - - - - - - - - -";

ScheduledEntry::ScheduledEntry(){
}

void ScheduledEntry::emptyCounter(){
	_counter.emptyUndoStack();
}

void ScheduledEntry::addEntry(Entry newEntry){
	int latestEntryIndex;
	//scheduled entry
	if (newEntry.getDateStatus()){
		_scheduledList.push_back(newEntry);
		sort(latestEntryIndex);
		_counter.counterAdd(true, latestEntryIndex);
	}

	//floating entry
	else {
		_floatingList.push_back(newEntry);
		latestEntryIndex = _floatingList.size();
		_counter.counterAdd(false, latestEntryIndex);
	}
}

void ScheduledEntry::showAddFeedback(Entry newEntry){
	string entryName = newEntry.getName();
	Date entryStartDate = newEntry.getStartDate();
	Date entryEndDate = newEntry.getEndDate();
	Time entryStartTime = newEntry.getStartTime();
	Time entryEndTime = newEntry.getEndTime();
	string entryLocation = newEntry.getLocation();

	cout << FEEDBACK_ADDED << entryName;
	if (newEntry.getDateStatus()){
		cout << FEEDBACK_FROM << entryStartDate.getDay() << " " << entryStartDate.getMonth() << " " << entryStartDate.getYear()
			<< FEEDBACK_AT << entryStartTime.getHour() << ".";
		if (entryStartTime.getMinute() < 10){
			cout << '0';
		}
		cout << entryStartTime.getMinute()
			<< FEEDBACK_TO << entryEndDate.getDay() << " " << entryEndDate.getMonth() << " " << entryEndDate.getYear()
			<< FEEDBACK_AT << entryEndTime.getHour() << ".";
		if (entryEndTime.getMinute() < 10){
			cout << '0';
		}
		cout << entryEndTime.getMinute();
	}
		cout << ". " << entryLocation << endl; 
}


void ScheduledEntry::displayEntry(int index){
	cout << endl
		<< BORDER << endl
		<< index << ". "
		<< _scheduledList[index-1].getFullDisplay()
		<< BORDER;
}

void ScheduledEntry::removeEntry(bool isScheduled, int index){
	cout << FEEDBACK_DELETED << endl;
	displayEntry(index);
	//scheduled entry
	if (isScheduled){
		_counter.counterDelete(true, index, _scheduledList[index-1]);
		_scheduledList.erase(_scheduledList.begin() + index - 1);
	}

	//floating entry
	else {
		_counter.counterDelete(false, index, _floatingList[index-1]);
		_floatingList.erase(_floatingList.begin() + index - 1);
	}
}

void ScheduledEntry::editEntry(bool isScheduled, string userInput){
	EntryEdit editComponent(isScheduled);
	int entryNumber = editComponent.getEntryNumber(userInput);
	editComponent.extractMarkerInfo(userInput);
	
	//find the entry to be edited
	vector<Entry>::iterator iter;
	if (isScheduled){
		iter = _scheduledList.begin();
	}
	else {
		iter = _floatingList.begin();
	}
	//loop to find the ith entry
	for (int i = 1; i < entryNumber; i++){
			iter++;
	}
	
	//update name
	string newName = editComponent.getName();
	if (newName != ""){
		iter->insertName(newName);
	}

	//update date
	if (editComponent.getDateEditStatus()){
		int inputStartDay;
		int inputStartMonth;
		int inputStartYear;
		int inputEndDay;
		int inputEndMonth;
		int inputEndYear;		
		editComponent.getDate(inputStartDay, inputStartMonth, inputStartYear, inputEndDay, inputEndMonth, inputEndYear);

		Date newStartDate;
		newStartDate.insertDay(inputStartDay);
		newStartDate.insertMonth(inputStartMonth);
		newStartDate.insertYear(inputStartYear);
		Date newEndDate;
		newEndDate.insertDay(inputEndDay);
		newEndDate.insertMonth(inputEndMonth);
		newEndDate.insertYear(inputEndYear);
		
		iter->insertStartDate(newStartDate);
		iter->insertEndDate(newEndDate);
	}

	//update time
	if (editComponent.getTimeEditStatus()){
		int inputStartHour;
		int inputStartMinute;
		int inputEndHour;
		int inputEndMinute;
		editComponent.getTime(inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
		
		Time newStartTime;
		Time newEndTime;
		newStartTime.insertHour(inputStartHour);
		newStartTime.insertMinute(inputStartMinute);
		newEndTime.insertHour(inputEndHour);
		newEndTime.insertMinute(inputEndMinute);

		iter->insertStartTime(newStartTime);
		iter->insertEndTime(newEndTime);
	}

	//update location
	string newLocation = editComponent.getLocation();
	if (newLocation != ""){
		iter->insertLocation(newLocation);
	}

	//update status
	string newStatus = editComponent.getStatus();
	if (newStatus != ""){
		if (newStatus == "done"){
			iter->changeStatus();
		}
		else if (newStatus == "undone"){
			iter->initialiseStatus();
		}
	}

	//feedback to users
	cout << FEEDBACK_EDITED << entryNumber << endl;
}

void ScheduledEntry::undo(){
	_counter.execute(_scheduledList, _floatingList);
}

void ScheduledEntry::exit(bool& running){
	//write scheduled
	ofstream writeSched;
	writeSched.open("FastAddSched.txt");
	vector<Entry>::iterator iterSched;

	for (iterSched = _scheduledList.begin(); iterSched != _scheduledList.end(); iterSched++){
		writeSched << iterSched->storeEntry() << endl;
	}
	writeSched.close();

	//write floating
	ofstream writeFloat;
	writeFloat.open("FastAddFloat.txt");
	vector<Entry>::iterator iterFloat;

	for (iterFloat = _floatingList.begin(); iterFloat != _floatingList.end(); iterFloat++){
		writeFloat << iterFloat->storeEntry() << endl;
	}
	writeFloat.close();

	running = false;
}

void ScheduledEntry::sort(int& latestEntryIndex){
	latestEntryIndex = _scheduledList.size();
	vector<Entry>::iterator firstIter;
	vector<Entry>::iterator secondIter;
	int count = 0;
	Entry tempEntry;

	//bubble sort
	for (firstIter = _scheduledList.begin(); firstIter != _scheduledList.end(); firstIter++){
		for(secondIter = _scheduledList.begin()+1; secondIter != _scheduledList.end() - count; secondIter++){
			bool isSwapped = false;
			//if the previous entry is larger than the next entry, swap
			if((secondIter - 1)->getStartTime().getTime() > (secondIter)->getStartTime().getTime()){
				tempEntry = *(secondIter-1);
				*(secondIter-1) = *(secondIter);
				*(secondIter) = tempEntry;
				isSwapped = true;
			}

			//if: 1. it is the last iteration of the inner loop, that is the iteration which
			//compares the last element of inner loop with the element before it, and
			//2. a swap occurs in this iteration
			//decrement latesEntryIndex so it will match the index number of latest Entry
			if (secondIter == _scheduledList.end() - count - 1 && isSwapped) {
				latestEntryIndex--;
			}
		}
		count++;
	}
}

vector<Entry> ScheduledEntry::getScheduledList(){
	vector<Entry> ScheduledEntries = _scheduledList;
	return ScheduledEntries;
}

vector<Entry> ScheduledEntry::getFloatingList(){
	vector<Entry> FloatingEntries = _floatingList;
	return FloatingEntries;
}