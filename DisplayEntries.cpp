#include "DisplayEntries.h"
#include "StringConvertor.h"

const string DisplayEntries::TYPE_SCHEDULED = " scheduled";
const string DisplayEntries::TYPE_FLOATING = " floating";
const string DisplayEntries::TYPE_NEXT = " next";
const string DisplayEntries::TYPE_PREV = " prev";



DisplayEntries::DisplayEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries, int pageNumber){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_viewingScheduledList;
	_pageNumber = pageNumber;
}

void DisplayEntries::execute(string command){
	_userInput = command;
	StringConvertor convert;

	if (_userInput == TYPE_SCHEDULED){
		displayScheduledEntryShort(_pageNumber);
		cout << endl << "You are currently viewing your SCHEDULED entries" << endl
			<< "No. of Entries: " << _scheduledList.size() << endl;
		_viewingScheduledList = true;
	}
	else if (_userInput == TYPE_FLOATING){
		displayFloatingEntries();
		cout << endl << "You are currently viewing your FLOATING entries" << endl
			<< "No. of Entries: " << _floatingList.size() << endl;
		_viewingScheduledList = false;
	}
	else if (_userInput == TYPE_NEXT){
		_pageNumber++;
		displayScheduledEntryShort(_pageNumber);
	}
	else if (_userInput == TYPE_PREV){
		_pageNumber--;
		if(_pageNumber < 1){
			_pageNumber = 1;
			cout << "You are on the first page ";
		}
		displayScheduledEntryShort(_pageNumber);
	}
	else if (_userInput[1] > '0'){
		int entryNumber;
		convert.convertStringToNumber(_userInput, entryNumber);
		cout << _viewingScheduledList << endl;
		if(_viewingScheduledList){
			cout << "Scheduled Entry" << endl;
			displayOneScheduledEntry(entryNumber);
		}else if(!_viewingScheduledList){
			cout << "Floating Entry" << endl;
			displayOneFloatingEntry(entryNumber);
		}
	}
	else {
		cout << "Invalid display command! Try again" << endl << endl;
	}
}

void DisplayEntries::displayScheduledEntryShort(int _pageNumber){
	int number = (_pageNumber-1)*5 + 1;
	int firstEntry = 5*(_pageNumber-1);
	int lastEntry = firstEntry + 5;
	for (int i = firstEntry; i < lastEntry; i++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< (number) << ". "
			<< _scheduledList[i].getShortDisplay() << endl;
		cout << "- - - - - - - - - - - - - - - - -" << endl;
		number++;
	}
	cout << "Page: " << _pageNumber << " out of " << _scheduledList.size()/5 << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
}

void DisplayEntries::displayOneScheduledEntry(int index){
	cout << endl
		<< "- - - - - - - - - - - - - - - - -" << endl
		<< index << ". "
		<< _scheduledList[index-1].getFullDisplay()
	 << "- - - - - - - - - - - - - - - - -";
}

void DisplayEntries::displayFloatingEntries(){
	int number = 0;
	vector<Entry>::iterator iter;
	for (iter = _floatingList.begin(); iter != _floatingList.end(); iter++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< (number + 1) << ". "
			<< iter->getShortDisplay() << endl;
		cout << "- - - - - - - - - - - - - - - - -";
		number++;
	}
}

void DisplayEntries::displayOneFloatingEntry(int index){
	cout << endl
		<< "- - - - - - - - - - - - - - - - -" << endl
		<< index << ". "
		<< _floatingList[index-1].getFullDisplay()
	 << "- - - - - - - - - - - - - - - - -";
}

int DisplayEntries::returnPageNumber(){
	return _pageNumber;
}