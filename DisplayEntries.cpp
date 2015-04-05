#include "DisplayEntries.h"

const string DisplayEntries::TYPE_SCHEDULED = " scheduled";
const string DisplayEntries::TYPE_FLOATING = " floating";
const string DisplayEntries::TYPE_NEXT = " next";
const string DisplayEntries::TYPE_PREV = " prev";
const string DisplayEntries::TYPE_CLASH = " clashes";

const string DisplayEntries::BORDER = "- - - - - - - - - - - - - - - - -";

DisplayEntries::DisplayEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries, int pageNumber){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_pageNumber = pageNumber;
}

void DisplayEntries::execute(string command, bool& isScheduled){
	_userInput = command;
	StringConvertor convert;

	//display scheduled
	if (_userInput == TYPE_SCHEDULED){
		if(_scheduledList.empty()){
			cout << "Scheduled List is empty!" << endl << endl;
			return;
		}
		displayScheduledEntryShort(_pageNumber);
		cout << endl << "You are currently viewing your SCHEDULED entries" << endl
			<< "No. of Entries: " << _scheduledList.size() << endl;
		_viewingScheduledList = true;
	}
	
	//display floating
	else if (_userInput == TYPE_FLOATING){
		if(_scheduledList.empty()){
			cout << "Scheduled List is empty!" << endl << endl;
			return;
		}
		displayFloatingEntries();
		cout << endl << "You are currently viewing your FLOATING entries" << endl
			<< "No. of Entries: " << _floatingList.size() << endl;
		_viewingScheduledList = false;
	}
	
	//display next page
	else if (_userInput == TYPE_NEXT){
		if(_scheduledList.empty()){
			cout << "Scheduled List is empty!" << endl << endl;
			return;
		}
		_pageNumber++;
		displayScheduledEntryShort(_pageNumber);
	}

	//display previous page
	else if (_userInput == TYPE_PREV){
		if(_scheduledList.empty()){
			cout << "Scheduled List is empty!" << endl << endl;
			return;
		}
		_pageNumber--;
		if(_pageNumber < 1){
			_pageNumber = 1;
			cout << "You are on the first page ";
		}
		displayScheduledEntryShort(_pageNumber);
	}
	
	//display clashing scheduled entries
	else if (_userInput == TYPE_CLASH){
		displayClashes();
	}

	//display details of an entry
	else if (_userInput[1] > '0'){
		int entryNumber;
		convert.convertStringToNumber(_userInput, entryNumber);
		if(_viewingScheduledList){
			cout << "Scheduled Entry" << endl;
			displayOneScheduledEntry(entryNumber);
		} else if(!_viewingScheduledList){
			cout << "Floating Entry" << endl;
			displayOneFloatingEntry(entryNumber);
		}
	}

	//if command is invalid
	else {
		cout << "Invalid display command! Try again" << endl << endl;
	}

	isScheduled = _viewingScheduledList;
}

void DisplayEntries::displayScheduledEntryShort(int _pageNumber){
	int number = (_pageNumber-1)*5 + 1;
	int firstEntry = 5*(_pageNumber-1);
	int lastEntry = firstEntry + 5;
	for (int i = firstEntry; i < lastEntry; i++){
		cout << endl
			<< BORDER << endl
			<< (number) << ". "
			<< _scheduledList[i].getShortDisplay() << endl
			<< BORDER << endl;
		number++;
	}
	cout << "Page: " << _pageNumber << " out of " << _scheduledList.size()/5 << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
}

void DisplayEntries::displayOneScheduledEntry(int index){
	cout << endl
		<< BORDER << endl
		<< index << ". "
		<< _scheduledList[index-1].getFullDisplay()
		<< BORDER;
}

void DisplayEntries::displayFloatingEntries(){
	int number = 0;
	vector<Entry>::iterator iter;
	for (iter = _floatingList.begin(); iter != _floatingList.end(); iter++){
		cout << endl
			<< BORDER << endl
			<< (number + 1) << ". "
			<< iter->getShortDisplay() << endl
			<< BORDER;
		number++;
	}
}

void DisplayEntries::displayOneFloatingEntry(int index){
	cout << endl
		<< BORDER << endl
		<< index << ". "
		<< _floatingList[index-1].getFullDisplay()
		<< BORDER;
}

void DisplayEntries::displayClashes(){
	ClashInspector checkEntries(_scheduledList);
	vector<Entry>::iterator thisEntry;
	int count = 0;
	for(thisEntry = _scheduledList.begin(); thisEntry != _scheduledList.end(); thisEntry++){
		cout << count + 1 << ". " << thisEntry->getName() << endl;
		checkEntries.compareEntry(*thisEntry, count);
		cout << endl;
		count++;
	}
}

int DisplayEntries::returnPageNumber(){
	return _pageNumber;
}