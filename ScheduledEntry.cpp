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
const string ScheduledEntry::FEEDBACK_NO_ENTRIES_LEFT = "No entries left.";
const string ScheduledEntry::FEEDBACK_WRONG_COMMAND = "Wrong command!";
const string ScheduledEntry::FEEDBACK_SUCCESSFULLY_STORED = " successfully stored at ";

const string ScheduledEntry::STATUS_DONE = "done";
const string ScheduledEntry::STATUS_UNDONE = "undone";

const string ScheduledEntry::SPECIFY_STORAGE_PROMPT = "Please specify where you want to store your: ";
const string ScheduledEntry::SCHEDULED_ENTRIES_PROMPT = "Scheduled entries";
const string ScheduledEntry::FLOATING_ENTRIES_PROMPT = "Floating entries";

const string ScheduledEntry::SCHEDULED_FILE_NAME = "\\FastAddSched.txt";
const string ScheduledEntry::FLOATING_FILE_NAME = "\\FastAddFloat.txt";

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


void ScheduledEntry::displayEntry(bool isScheduled, int index){
	cout << endl
		<< BORDER << endl
		<< index << ". ";
	//scheduled entry
	if (isScheduled){	
		cout << _scheduledList[index-1].getFullDisplay();
	}
	//floating entry
	else {
		cout << _floatingList[index-1].getFullDisplay();
	}
	cout << BORDER;
}

void ScheduledEntry::removeEntry(bool isScheduled, int index){
	//scheduled entry
	if (isScheduled && !_scheduledList.empty()){
		cout << FEEDBACK_DELETED << endl;
		displayEntry(isScheduled, index);
		_counter.counterDelete(true, index, _scheduledList[index-1]);
		_scheduledList.erase(_scheduledList.begin() + index - 1);
	}

	//floating entry
	else if (!isScheduled && !_floatingList.empty()){
		cout << FEEDBACK_DELETED << endl;
		displayEntry(isScheduled, index);
		_counter.counterDelete(false, index, _floatingList[index-1]);
		_floatingList.erase(_floatingList.begin() + index - 1);
	}

	//no more entry
	else {
		cout << FEEDBACK_NO_ENTRIES_LEFT << endl;
	}
}

void ScheduledEntry::editEntry(bool isScheduled, string userInput){
	EntryEdit editComponent(isScheduled);
	int entryNumber = editComponent.getEntryNumber(userInput);
	editComponent.extractMarkerInfo(userInput);
	
	if (!editComponent.getEditStatus()){
		cout << FEEDBACK_WRONG_COMMAND << endl;
		return;
	}

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
	int inputStartDay;
	if (editComponent.getDateEditStatus()){
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
		if (newStatus == STATUS_DONE){
			iter->changeStatus();
		}
		else if (newStatus == STATUS_UNDONE){
			iter->initialiseStatus();
		}
	}

	//update added tags
	if (editComponent.getTagAddedStatus()){
		editComponent.addTag(*iter);
	}

	//update removed tags
	if (editComponent.getTagRemovedStatus()){
		editComponent.removeTag(*iter);
	}

	//feedback to users
	cout << FEEDBACK_EDITED << entryNumber << endl;

	//move entry from floating to scheduled list and vice versa
	if (editComponent.getDateEditStatus() && (editComponent.getTimeEditStatus() || inputStartDay == 0)){
		moveScheduledFloating(isScheduled, entryNumber, *iter);
	}
}

void ScheduledEntry::moveScheduledFloating(bool isScheduled, int entryNumber, Entry movedEntry){
	removeEntry(isScheduled, entryNumber);
	addEntry(movedEntry);
}

void ScheduledEntry::undo(){
	_counter.execute(_scheduledList, _floatingList);
}

void ScheduledEntry::exit(bool& running){
	cout << SPECIFY_STORAGE_PROMPT << endl;
	
	//write scheduled
	ofstream writeSched;
	string scheduledPath;
	cout << SCHEDULED_ENTRIES_PROMPT << ": ";
	cin >> scheduledPath;
	scheduledPath = scheduledPath + SCHEDULED_FILE_NAME;
	writeSched.open(scheduledPath);
	vector<Entry>::iterator iterSched;

	for (iterSched = _scheduledList.begin(); iterSched != _scheduledList.end(); iterSched++){
		writeSched << iterSched->storeEntry() << endl;
	}
	writeSched.close();
	cout << SCHEDULED_ENTRIES_PROMPT << FEEDBACK_SUCCESSFULLY_STORED << scheduledPath << endl;

	//write floating
	ofstream writeFloat;
	string floatingPath;
	cout << FLOATING_ENTRIES_PROMPT << ": ";
	cin >> floatingPath;
	floatingPath = floatingPath + FLOATING_FILE_NAME;
	writeFloat.open(floatingPath);
	vector<Entry>::iterator iterFloat;

	for (iterFloat = _floatingList.begin(); iterFloat != _floatingList.end(); iterFloat++){
		writeFloat << iterFloat->storeEntry() << endl;
	}
	writeFloat.close();
	cout << FLOATING_ENTRIES_PROMPT << FEEDBACK_SUCCESSFULLY_STORED << floatingPath << endl;

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