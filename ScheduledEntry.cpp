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

const string ScheduledEntry::NAME_MARKER = "-n";
const string ScheduledEntry::DATE_MARKER = "-d";
const string ScheduledEntry::TIME_MARKER = "-t";
const string ScheduledEntry::LOCATION_MARKER = "-l";
const string ScheduledEntry::STATUS_MARKER = "-s";

const string ScheduledEntry::TYPE_SCHEDULED = "scheduled";
const string ScheduledEntry::TYPE_FLOATING = "floating";

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
	if (newEntry.getDateStatus()){
		cout << FEEDBACK_FROM << entryStartDate.getDay() << " " << entryStartDate.getMonth() << " " << entryStartDate.getYear()
			<< FEEDBACK_AT << entryStartTime.getHour() << "." << entryStartTime.getMinute()
			<< FEEDBACK_TO << entryEndDate.getDay() << " " << entryEndDate.getMonth() << " " << entryEndDate.getYear()
			<< FEEDBACK_AT << entryEndTime.getHour() << "." << entryEndTime.getMinute();
	}
		cout << ". " << entryLocation << endl; 
}

void ScheduledEntry::display(){
	string listType;
	getline(cin, listType);
	if (listType == TYPE_SCHEDULED){
		displayScheduled();
	}
	else if (listType == TYPE_FLOATING){
		displayFloating();
	}
	else {
		cout << FEEDBACK_INVALID_TYPE << endl;
	}
}

void ScheduledEntry::displayScheduled(){
	int number = 0;
	vector<Entry>::iterator iter;
	for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< (number + 1) << ". "
		<< iter->getDisplay() << endl;
		ClashInspector inspect(_scheduledList);
		inspect.compareEntry(*iter, number);
		cout << "- - - - - - - - - - - - - - - - -";
		number++;
	}
}

void ScheduledEntry::displayFloating(){
	int number = 0;
	vector<Entry>::iterator iter;
	for (iter = _floatingList.begin(); iter != _floatingList.end(); iter++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< (number + 1) << ". "
		<< iter->getDisplay() << endl;
		cout << "- - - - - - - - - - - - - - - - -";
		number++;
	}
}

void ScheduledEntry::displayEntry(int index){
	cout << endl
		<< "- - - - - - - - - - - - - - - - -" << endl
		<< index << ". "
	<< _scheduledList[index-1].getDisplay()
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

void ScheduledEntry::searchTag(string keyword){
	int count = 1;
	vector<Entry>::iterator iterEntry;
	for(iterEntry = _scheduledList.begin(); iterEntry != _scheduledList.end(); iterEntry++){
		iterEntry->searchEntryTag(keyword, count);
		count ++;
	}
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

void ScheduledEntry::searchEntry(string userInput){
	string marker = userInput.substr(0,2);
	userInput = userInput.erase(0, 3);
			
	if (marker == NAME_MARKER){
		vector<Entry>::iterator iter;
		int count = 0;
		cout << "Search result(s) with keyword " << userInput << ":" << endl;
		for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
			if (iter->getName() == userInput){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iter->getDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}
	}
	
	/*if (marker == TIME_MARKER){
		
	}
	
	if (marker == DATE_MARKER){
		
	}*/
			
	if (marker == LOCATION_MARKER){
		vector<Entry>::iterator iter;
		int count = 1;
		cout << "Search result(s) with keyword " << userInput << ":" << endl;
		for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
			if (iter->getLocation() == userInput){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iter->getDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
	}

	if (marker == STATUS_MARKER){
		vector<Entry>::iterator iter;
		int count = 1;
		cout << "The task(s) that is/are " << userInput << ":" << endl;
		for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
			if (iter->getStatus() == userInput){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iter->getDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
	}
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
