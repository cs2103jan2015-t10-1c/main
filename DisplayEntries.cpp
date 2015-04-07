#include "DisplayEntries.h"

const string DisplayEntries::TYPE_SCHEDULED = " scheduled";
const string DisplayEntries::TYPE_FLOATING = " floating";
const string DisplayEntries::TYPE_NEXT = " next";
const string DisplayEntries::TYPE_PREV = " prev";
const string DisplayEntries::TYPE_CLASH = " clashes";
const string DisplayEntries::TYPE_FIRSTPAGE = " first page";
const string DisplayEntries::TYPE_LASTPAGE = " last page";
const string DisplayEntries::TYPE_SPECIFICPAGE = " page";
const string DisplayEntries::TYPE_PAST = " past";

const int DisplayEntries::ENTRY_PERPAGE = 5;
const int DisplayEntries::BLANKSPACE_COUNT = 1;

const string DisplayEntries::BORDER = "- - - - - - - - - - - - - - - - - - - - - - -";

DisplayEntries::DisplayEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries, int pageNumber, bool atScheduledList){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_pageNumber = pageNumber;
	_viewingScheduledList = atScheduledList;
	_today = (day_clock::local_day());
	_tomorrow = _today + days(1);
	_thisWeek = _today + days(7);
	_nextWeek = _today + days(14);
	_thisMonth = _today.end_of_month();
	_nextMonth = _thisMonth + months(1);
}

void DisplayEntries::execute(string command, bool& atScheduledList, int& pageNumber){
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
		atScheduledList = _viewingScheduledList;
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
		atScheduledList = _viewingScheduledList;
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
	//display first page
	else if (_userInput == TYPE_FIRSTPAGE){
		displayFirstPage();
	}
	//display last page
	else if (_userInput == TYPE_LASTPAGE){
		displayLastPage();
	}
	//display specified page
	else if (_userInput.substr(0, TYPE_SPECIFICPAGE.size()) == TYPE_SPECIFICPAGE){
		int inputPageNumber;
		_userInput = _userInput.substr(TYPE_SPECIFICPAGE.size() + BLANKSPACE_COUNT);
		convert.convertStringToNumber(_userInput, inputPageNumber);
		displaySpecifiedPage(inputPageNumber);
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

	/*else if (_userInput == TYPE_PAST){
		displayPastEntries();
	}*/

	//if command is invalid
	else {
		cout << "Invalid display command! Try again" << endl << endl;
	}
	pageNumber = _pageNumber;
}

void DisplayEntries::displayScheduledEntryShort(int& _pageNumber){
	//marking the boundaries
	_printInThePast = false;
	_printToday = false;
	_printTomorrow = false;
	_printThisWeek = false;
	_printNextWeek = false;
	_printThisMonth = false;
	_printNextMonth = false;
	//initialise for paging
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	int number;
	initialisePaging(numberOfPages, firstEntry, lastEntry, number);

	for (int i = firstEntry; i < lastEntry; i++){
		cout << endl;
		date entryStartDate = _scheduledList[i].getStartDate().getDate();
		if(entryStartDate < _today && _printInThePast == false){
			cout << endl << "[Events in the past:] " << endl << endl;
			_printInThePast = true;
		}
		if(entryStartDate == _today && _printToday == false){
			cout << endl << "[Events today:] " << endl << endl;
			_printToday = true;
		}
		if(entryStartDate == _tomorrow && _printTomorrow == false){
			cout << endl << "[Events tomorrow:] " << endl << endl;
			_printTomorrow = true;
			_printThisWeek = true;
		}
		if(entryStartDate <= _thisWeek && entryStartDate >= _today && _printThisWeek == false){
			cout << endl << "[Events This Week:] " << endl << endl;
			_printThisWeek = true;
		}
		if(entryStartDate > _thisWeek && entryStartDate <= _nextWeek && _printNextWeek == false){
			cout << endl << "[Events Next Week:] " << endl << endl;
			_printNextWeek = true;
		}
		if(entryStartDate <= _thisMonth && entryStartDate > _nextWeek && _printThisMonth == false){
			cout << endl << "[Events This Month:] " << endl << endl;
			_printThisMonth = true;
		}
		if(entryStartDate <= _nextMonth && entryStartDate > _thisMonth && _printNextMonth == false){
			cout << endl << "[Events Next Month:] " << endl << endl;
			_printNextMonth = true;
		}
		_scheduledList[i].insertEntryNumber(number);
		cout << BORDER << endl
			<< _scheduledList[i].getEntryNumber() << ". "
			<< _scheduledList[i].getShortDisplay() << endl;
		cout << BORDER << endl;
		number++;
	}
	closingMessage(numberOfPages, firstEntry, lastEntry);
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
		bool clashExists = false;
		bool printClash = false;
		checkEntries.compareEntry(*thisEntry, count, clashExists, printClash);
		if(clashExists){
			cout << count + 1 << ". " << thisEntry->getName() << endl;
			printClash = true;
			checkEntries.compareEntry(*thisEntry, count, clashExists, printClash);
			cout << endl;
		}
		count++;
	}
}

void DisplayEntries::displayFirstPage(){
	int firstPage = 1;
	displayScheduledEntryShort(firstPage);
}

void DisplayEntries::displayLastPage(){
	int numberOfPages = _scheduledList.size()/ENTRY_PERPAGE;
	if(_scheduledList.size() % ENTRY_PERPAGE > 0){
		numberOfPages++;
	}
	displayScheduledEntryShort(numberOfPages);
}

void DisplayEntries::displaySpecifiedPage(int page){
	displayScheduledEntryShort(page);
	_pageNumber = page;
}

/*void DisplayEntries::displayPastEntries(){
	vector<Entry>::iterator iterPastEntry;
	bool isToday;
	for(iterPastEntry = _scheduledList.begin(); iterPastEntry != _scheduledList.end(); iterPastEntry++){
		cout << iterPastEntry->getShortDisplay();
		cout << endl << endl;
	}
}*/

int DisplayEntries::returnPageNumber(){
	return _pageNumber;
}

void DisplayEntries::initialisePaging(int& numberOfPages, int& firstEntry, int& lastEntry, int& number){
	//initialise number of Pages
	numberOfPages = _scheduledList.size()/ENTRY_PERPAGE;
	int numberOfEntriesOnLastPage = _scheduledList.size()%ENTRY_PERPAGE;
	if(numberOfEntriesOnLastPage > 0){
		numberOfPages++;
	}
	//prevent abort for exceeding page
	if(_pageNumber > numberOfPages){
		cout << "Page does not exist!" << endl << endl;
		_pageNumber--;
	}
	firstEntry = ENTRY_PERPAGE*(_pageNumber-1);
	lastEntry = firstEntry + ENTRY_PERPAGE;
	//case for the last page
	if(_pageNumber == numberOfPages){
		lastEntry = firstEntry + numberOfEntriesOnLastPage;
	}
	//prevent abort for number of entries less than 5
	if(_scheduledList.size() < ENTRY_PERPAGE){
		lastEntry = _scheduledList.size();	
	}
	number = (_pageNumber-1) * ENTRY_PERPAGE + 1;
}

void DisplayEntries::closingMessage(int numberOfPages, int firstEntry, int lastEntry){
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
}

