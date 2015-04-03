#include "DisplayEntries.h"
#include "StringConvertor.h"

const string DisplayEntries::TYPE_SCHEDULED = " scheduled";
const string DisplayEntries::TYPE_FLOATING = " floating";

DisplayEntries::DisplayEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_viewingScheduledList;
	_pageNumber = 1;
}

void DisplayEntries::execute(string command){
	_userInput = command;
	StringConvertor convert;

	if (_userInput == TYPE_SCHEDULED){
		displayScheduledEntryShort();
		cout << endl << "You are currently viewing your SCHEDULED entries" << endl << endl;
		_viewingScheduledList = true;
	}
	else if (_userInput == TYPE_FLOATING){
		displayFloatingEntries();
		cout << endl << "You are currently viewing your FLOATING entries" << endl << endl;
		_viewingScheduledList = false;
	}
	else if (_userInput[1] > '0'){
		int entryNumber;
		convert.convertStringToNumber(_userInput, entryNumber);
		cout << _viewingScheduledList << endl;
		if(_viewingScheduledList){
			cout << "printing scheduled" << endl;
			displayOneScheduledEntry(entryNumber);
		}else if(!_viewingScheduledList){
			cout << "printing floating" << endl;
			displayOneFloatingEntry(entryNumber);
		}
	}
	else {
		cout << "Invalid display command! Try again" << endl << endl;
	}
}

void DisplayEntries::displayScheduledEntryShort(){
	int number = 0;
	vector<Entry>::iterator iter;
	for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
		cout << endl
			<< "- - - - - - - - - - - - - - - - -" << endl
			<< (number + 1) << ". "
			<< iter->getShortDisplay() << endl;
		cout << "- - - - - - - - - - - - - - - - -";
		number++;
	}
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