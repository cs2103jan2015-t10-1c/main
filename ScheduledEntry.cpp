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

const string ScheduledEntry::NAME_MARKER = "-n";
const string ScheduledEntry::DATE_MARKER = "-d";
const string ScheduledEntry::TIME_MARKER = "-t";
const string ScheduledEntry::LOCATION_MARKER = "-l";

ScheduledEntry::ScheduledEntry(){
}

void ScheduledEntry::addEntry(Entry newEntry){
	if (newEntry.getStartDateStatus()){
		_scheduledList.push_back(newEntry);
	}
	else{
		_floatingList.push_back(newEntry);
	}
	showAddFeedback(newEntry);
}

void ScheduledEntry::showAddFeedback(Entry newEntry){
	string entryName = newEntry.getName();
	Date entryStartDate = newEntry.getStartDate();
	Date entryEndDate = newEntry.getEndDate();
	Time entryStartTime = newEntry.getStartTime();
	Time entryEndTime = newEntry.getEndTime();
	string entryLocation = newEntry.getLocation();

	cout << FEEDBACK_ADDED << entryName;
	if (newEntry.getStartDateStatus()){
		cout << FEEDBACK_FROM << entryStartDate.getDay() << " " << entryStartDate.getMonth() << " " << entryStartDate.getYear()
			<< FEEDBACK_AT << entryStartTime.getHour() << "." << entryStartTime.getMinute();
		if (newEntry.getEndDateStatus()){
			cout << FEEDBACK_TO << entryEndDate.getDay() << " " << entryEndDate.getMonth() << " " << entryEndDate.getYear()
				<< FEEDBACK_AT << entryEndTime.getHour() << "." << entryEndTime.getMinute();
		}
	}
		cout << ". " << entryLocation << endl; 
}

void ScheduledEntry::displayScheduled(){
	int number = 1;
	vector<Entry>::iterator iter;
	for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< number << ". ";
		iter->display();
		cout<< "- - - - - - - - - - - - - - - - -";
		number++;
	}
}

void ScheduledEntry::displayEntry(int index){
	cout << endl
		<< "- - - - - - - - - - - - - - - - -" << endl
		<< index << ". ";
	_scheduledList[index-1].display();
	cout << "- - - - - - - - - - - - - - - - -";
}

void ScheduledEntry::removeEntry(int index){
	cout << FEEDBACK_DELETED << endl;
	index--;
	displayEntry(index);
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

	//feedback to users
	cout << FEEDBACK_EDITED << entryNumber << endl;
}

void ScheduledEntry::searchTag(string keyword){
	int count = 1;
	vector<Entry>::iterator iterEntry;
	for(iterEntry = _scheduledList.begin(); iterEntry != _scheduledList.end(); iterEntry++){
		iterEntry->searchEntryTag(keyword);
	}
}

void ScheduledEntry::exit(bool& running){
	running = false;
}