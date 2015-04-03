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

const string ScheduledEntry::TYPE_SCHEDULED = " scheduled";
const string ScheduledEntry::TYPE_FLOATING = " floating";

ScheduledEntry::ScheduledEntry(){
}


void ScheduledEntry::addEntry(Entry newEntry){
	if (newEntry.getDateStatus()){
		_scheduledList.push_back(newEntry);
		sort();
	}
	else {
		_floatingList.push_back(newEntry);
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
		<< "- - - - - - - - - - - - - - - - -" << endl
		<< index << ". "
		<< _scheduledList[index-1].getFullDisplay()
	 << "- - - - - - - - - - - - - - - - -";
}

void ScheduledEntry::removeEntry(int index){
	cout << FEEDBACK_DELETED << endl;
	displayEntry(index);
	index--;
	_scheduledList.erase(_scheduledList.begin()+index);
}

void ScheduledEntry::editEntry(string userInput){
	EntryEdit editComponent;
	int entryNumber = editComponent.getEntryNumber(userInput);
	string marker = editComponent.getMarker(userInput);
			
	if (marker == NAME_MARKER){
		string newName = editComponent.getName();
		vector<Entry>::iterator iter = _scheduledList.begin();
		//loop find the ith entry
		for(int i = 1; i < entryNumber; i++){
			iter++;
		}
		iter->insertName(newName);
	}
	
	if (marker == TIME_MARKER){
		int inputStartHour;
		int inputStartMinute;
		int inputEndHour;
		int inputEndMinute;
		editComponent.getTime(inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
		vector<Entry>::iterator iter = _scheduledList.begin();
		for(int i = 1; i < entryNumber; i++){
			iter++;
		}
		
		Time newStartTime;
		Time newEndTime;
		newStartTime.insertHour(inputStartHour);
		newStartTime.insertMinute(inputStartMinute);
		newEndTime.insertHour(inputEndHour);
		newEndTime.insertMinute(inputEndMinute);

		iter->insertStartTime(newStartTime);
		iter->insertEndTime(newEndTime);
	}
	
	if (marker == DATE_MARKER){
		int inputStartDay;
		int inputStartMonth;
		int inputStartYear;
				
		editComponent.getDate(inputStartDay, inputStartMonth, inputStartYear);
		vector<Entry>::iterator iter = _scheduledList.begin();
		for(int i = 1; i < entryNumber; i++){
			iter++;
		}
		Date newStartDate;
		newStartDate.insertDay(inputStartDay);
		newStartDate.insertMonth(inputStartMonth);
		newStartDate.insertYear(inputStartYear);

		iter->insertStartDate(newStartDate);
	}
			
	if (marker == LOCATION_MARKER){
		string newLocation = editComponent.getLocation();
		vector<Entry>::iterator iter = _scheduledList.begin();
		for(int i = 1; i < entryNumber; i++){
			iter++;
		}
		iter->insertLocation(newLocation);
	}

	if (marker == STATUS_MARKER){
		string status = editComponent.getStatus();
		vector<Entry>::iterator iter = _scheduledList.begin();
		for(int i = 1; i < entryNumber; i++){
			iter++;
		}

		if (status == "done"){
			iter->changeStatus();
			iter->getStatus();
		}
		else if (status == "undone"){
			iter->initialiseStatus();
			iter->getStatus();
		}
	}


	//feedback to users
	cout << FEEDBACK_EDITED << entryNumber << endl;
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

void ScheduledEntry::sort(){
	vector<Entry>::iterator firstIter;
	vector<Entry>::iterator secondIter;
	int count = 0;
	for (firstIter = _scheduledList.begin(); firstIter != _scheduledList.end(); firstIter++){
		for(secondIter = _scheduledList.begin()+1; secondIter != _scheduledList.end() - count; secondIter++){
			if((secondIter - 1)->getStartTime().getTime() > (secondIter)->getStartTime().getTime()){
				Entry tempEntry = *(secondIter-1);
				*(secondIter-1) = *(secondIter);
				*(secondIter) = tempEntry;
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

