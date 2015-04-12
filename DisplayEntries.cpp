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

const string DisplayEntries::BORDER = "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";

DisplayEntries::DisplayEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_today = (day_clock::local_day());
	_tomorrow = _today + days(1);
	_thisWeek = _today + days(7);
	_nextWeek = _today + days(14);
	_thisMonth = _today.end_of_month();
	_nextMonth = _thisMonth + months(1);
	_now = second_clock::local_time();
	_viewingClashes = false;
	_viewingScheduledList = false;
	_viewingFloatingList = false;
	_viewingPastEntries = false;
	_viewingClashes = false;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}


//@author A0115902N
void DisplayEntries::execute(string command, int& pageNumber, int& lastPage, bool& viewingScheduledList, bool& viewingFloatingList, bool& viewingPast, bool& viewingClashes){
	_lastPage = lastPage;
	_pageNumber = pageNumber;
	_userInput = command;
	StringConvertor convert;
	_viewingClashes = viewingClashes;
	_viewingScheduledList = viewingScheduledList;
	_viewingFloatingList = viewingFloatingList;
	_viewingPastEntries = viewingPast;
	//display scheduled
	if (_userInput == TYPE_SCHEDULED){
		_pageNumber = 1;
		_viewingClashes = false;
		_viewingScheduledList = true;
		_viewingFloatingList = false;
		_viewingPastEntries = false;
		_viewingClashes = false;

		if(_scheduledList.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Scheduled List is empty!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		displayScheduledEntryShort();
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << endl << "You are currently viewing your SCHEDULED entries" << endl
			<< "No. of Entries: " << _scheduledList.size() << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
	
	//display floating
	else if (_userInput == TYPE_FLOATING){
		_pageNumber = 1;
		_viewingClashes = false;
		_viewingScheduledList = false;
		_viewingFloatingList = true;
		_viewingPastEntries = false;
		_viewingClashes = false;

		if(_floatingList.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Floating List is empty!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		displayFloatingEntries();
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << endl << "You are currently viewing your FLOATING entries" << endl
			<< "No. of Entries: " << _floatingList.size() << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
	
	//display next page
	else if (_userInput == TYPE_NEXT){
		displayNextPage();
		pageNumber = _pageNumber;
	}

	//display previous page
	else if (_userInput == TYPE_PREV){
		displayPrevPage();
		pageNumber = _pageNumber;
	}
	
	//display clashing scheduled entries
	else if (_userInput == TYPE_CLASH){
		_viewingScheduledList = false;
		_viewingFloatingList = false;
		_viewingPastEntries = false;
		_viewingClashes = true;
		_pageNumber = 1;
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
		if(_userInput.substr(TYPE_SPECIFICPAGE.size()).empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Page number is missing! " << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		_userInput = _userInput.substr(TYPE_SPECIFICPAGE.size() + BLANKSPACE_COUNT);
		convert.convertStringToNumber(_userInput, inputPageNumber);
		_pageNumber = inputPageNumber;
		if (_viewingClashes){
			displayClashes();
		} else if(_viewingScheduledList){
			displayScheduledEntryShort();
		} else if (_viewingFloatingList){
			displayFloatingEntries();
		} else if (_viewingPastEntries){
			displayPastEntries();
		}
	}

	//display details of an entry
	else if (isdigit(_userInput[1])){
		if(!_viewingScheduledList && !_viewingFloatingList){
			_viewingScheduledList = true;
			_viewingClashes = false;
			_viewingFloatingList = false;
			_viewingPastEntries = false;
		}
		int entryNumber;
		convert.convertStringToNumber(_userInput, entryNumber);
		if(_viewingScheduledList && entryNumber > 0){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Scheduled Entry" << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			displayOneScheduledEntry(entryNumber);
		} 
		else if(_viewingFloatingList && entryNumber > 0){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Floating Entry" << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			displayOneFloatingEntry(entryNumber);
		}
		else if (entryNumber <= 0) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Invalid display command! Try again" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		}
	}
	//display past events
	else if (_userInput == TYPE_PAST){
		_viewingClashes = false;
		_viewingScheduledList = false;
		_viewingFloatingList = false;
		_viewingPastEntries = false;
		_viewingClashes = true;		
		_pageNumber = 1;
		displayPastEntries();
	}

	//if command is invalid
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Invalid display command! Try again" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
	pageNumber = _pageNumber;
	lastPage = _lastPage;
	viewingScheduledList = _viewingScheduledList;
	viewingFloatingList = _viewingFloatingList;
	viewingPast = _viewingPastEntries;
	viewingClashes = _viewingClashes;
}

//@author A0116660L
void DisplayEntries::displayScheduledEntryShort(){
	//marking the boundaries
	_printInThePast = false;
	_printToday = false;
	_printTomorrow = false;
	_printThisWeek = false;
	_printNextWeek = false;
	_printThisMonth = false;
	_printNextMonth = false;
	//initialise vector for entries from today onwards
	vector<Entry> presentAndFutureEntries;
	for (unsigned int i = 0; i < _scheduledList.size() ; i++){
		date entryStartDate = _scheduledList[i].getStartDate().getDate();
		_scheduledList[i].insertEntryNumber(i + 1);
		if(entryStartDate >= _today){
			presentAndFutureEntries.push_back(_scheduledList[i]);
		}
	}
	//initialise for paging
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	int number;
	initialisePaging(presentAndFutureEntries, numberOfPages, firstEntry, lastEntry, number);

	for (int i = firstEntry; i < lastEntry; i++){
		cout << endl;
		date entryStartDate = presentAndFutureEntries[i].getStartDate().getDate();
		if(entryStartDate == _today && _printToday == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events today:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printToday = true;
		}
		if(entryStartDate == _tomorrow && _printTomorrow == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events tomorrow:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printTomorrow = true;
		}
		if(entryStartDate <= _thisWeek && entryStartDate > _tomorrow && _printThisWeek == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events This Week:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printThisWeek = true;
		}
		if(entryStartDate > _thisWeek && entryStartDate <= _nextWeek && _printNextWeek == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events Next Week:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printNextWeek = true;
		}
		if(entryStartDate <= _thisMonth && entryStartDate > _nextWeek && _printThisMonth == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events This Month:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printThisMonth = true;
		}
		if(entryStartDate <= _nextMonth && entryStartDate > _thisMonth && _printNextMonth == false){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << endl << "[Events Next Month:] " << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			_printNextMonth = true;
		}
		if(_today <= entryStartDate){
			_scheduledList[i].insertEntryNumber(number);
			cout << BORDER << endl
				<< presentAndFutureEntries[i].getEntryNumber() << ". "
				<< presentAndFutureEntries[i].getShortDisplay() << endl;
			cout << BORDER << endl;
			number++;
		}
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

//@author A0115902N
void DisplayEntries::displayFloatingEntries(){
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	int number;
	initialisePaging(_floatingList, numberOfPages, firstEntry, lastEntry, number);
	for (int i = firstEntry; i < lastEntry; i++){
		cout << endl
			<< BORDER << endl
			<< (number) << ". "
			<< _floatingList[i].getShortDisplay() << endl
			<< BORDER;
		number++;
	}
	cout << endl;
	closingMessage(numberOfPages, firstEntry, lastEntry);
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
	vector<Entry> listOfClashes;
	bool print = false;
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	int count = 0;
	bool clashExists;
	bool printClash;

	for(unsigned int i = 0; i < _scheduledList.size(); i++){
		if(!isInThePast(_scheduledList[i].getStartTime().getTime())){
			clashExists = false;
			printClash = false;
			_scheduledList[i].insertEntryNumber(i + 1);
			checkEntries.compareEntry(_scheduledList[i], _scheduledList[i].getEntryNumber(), clashExists, printClash);
			if(clashExists){
				listOfClashes.push_back(_scheduledList[i]);
			}
		count++;
		}
	}

	initialisePaging(listOfClashes, numberOfPages, firstEntry, lastEntry, count);
	clashExists = false;
	printClash = true;
	ClashInspector checkSearchResult(listOfClashes);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
	cout << "Entry clashes in the future: " << endl << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN ));
	for (int i = firstEntry; i < lastEntry; i++){
		cout << BORDER << endl
			<< listOfClashes[i].getEntryNumber() << ". "
			<< listOfClashes[i].getName() << endl;
		checkSearchResult.compareEntry(listOfClashes[i], i + 1, clashExists, printClash);
		cout << BORDER << endl;
	}
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void DisplayEntries::displayFirstPage(){
	int firstPage = 1;
	_pageNumber = 1;
		if (_viewingClashes){
			displayClashes();
		} else if(_viewingScheduledList){
			displayScheduledEntryShort();
		} else if (_viewingFloatingList){
			displayFloatingEntries();
		} else if (_viewingPastEntries){
			displayPastEntries();
		}
}

void DisplayEntries::displayLastPage(){
	_pageNumber = _lastPage - 1;
	displayNextPage();
}

void DisplayEntries::displayNextPage(){
	if(_scheduledList.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Scheduled List is empty!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		_pageNumber++;
		if(_viewingClashes){
			displayClashes();
		} else if(_viewingScheduledList){
			displayScheduledEntryShort();
		} else if(_viewingPastEntries){
			displayPastEntries();
		} else{
			displayFloatingEntries();
		}
}

void DisplayEntries::displayPrevPage(){
	if(_scheduledList.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Scheduled List is empty!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		_pageNumber--;
		if(_pageNumber < 1){
			_pageNumber = 1;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			cout << "You are on the first page ";
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN));
		}
		if(_viewingClashes){
			displayClashes();
		} else if(_viewingScheduledList){
			displayScheduledEntryShort();
		} else if(_viewingPastEntries){
			displayPastEntries();
		} else{
			displayFloatingEntries();
		}
}

void DisplayEntries::displaySpecifiedPage(int page){
	_pageNumber = page + 1;
	displayPrevPage();
}

void DisplayEntries::displayPastEntries(){
	vector<Entry>::iterator iterPastEntry;
	vector<Entry> entriesInThePast;

	int number = 1;
	int firstEntry;
	int lastEntry;
	int numberOfPages;
	for(iterPastEntry = _scheduledList.begin(); iterPastEntry != _scheduledList.end(); iterPastEntry++){
		iterPastEntry->insertEntryNumber(number);
		if(isInThePast(iterPastEntry->getStartTime().getTime())){
			entriesInThePast.push_back(*iterPastEntry);
		}
		number++;
	}
	number = 0;
	initialisePaging(entriesInThePast, numberOfPages, firstEntry, lastEntry, number);
	for(int i = firstEntry; i < lastEntry ; i++){
		cout << BORDER << endl
			<< entriesInThePast[i].getEntryNumber() << ". "
			<< _scheduledList[i].getShortDisplay() << endl;
		cout << BORDER << endl;
	}
	closingMessage(numberOfPages, firstEntry, lastEntry);
}

int DisplayEntries::returnPageNumber(){
	return _pageNumber;
}

void DisplayEntries::initialisePaging(vector<Entry> entryVector, int& numberOfPages,int& firstEntry, int& lastEntry, int& number){
	//initialise number of Pages
	numberOfPages = entryVector.size()/ENTRY_PERPAGE;
	int numberOfEntriesOnLastPage = entryVector.size()%ENTRY_PERPAGE;
	if(numberOfEntriesOnLastPage > 0){
		numberOfPages++;
	}

	//prevent abort for exceeding page
	while (_pageNumber > numberOfPages){
		if (_pageNumber = numberOfPages + 1){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Page does not exist!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		}
		_pageNumber--;
	}

	firstEntry = ENTRY_PERPAGE*(_pageNumber-1);
	lastEntry = firstEntry + ENTRY_PERPAGE;
	//case for the last page
	if(_pageNumber == numberOfPages && numberOfEntriesOnLastPage != 0){
		lastEntry = firstEntry + numberOfEntriesOnLastPage;
	}
	//prevent abort for number of entries less than 5
	if(entryVector.size() < ENTRY_PERPAGE){
		lastEntry = entryVector.size();	
	}
	number = (_pageNumber-1) * ENTRY_PERPAGE + 1;
	_lastPage = numberOfPages;
}

void DisplayEntries::closingMessage(int numberOfPages, int firstEntry, int lastEntry){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	if(_pageNumber == numberOfPages && numberOfPages!=1){
		cout << "<<< display prev" << endl << endl;
	} else if(_pageNumber == 1 && numberOfPages!=1){
		cout << "\t \t \t \t display next >>>" << endl << endl;
	} else if (numberOfPages!=1){
		cout << "<<< display prev \t \t display next >>>" << endl << endl;
	}
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void DisplayEntries::displayToday(){
	_pageNumber = 1;
	int number = 1;
	vector<Entry> EventsToday;
	for (unsigned int i = 0; i < _scheduledList.size() ; i++){
		date entryStartDate = _scheduledList[i].getStartDate().getDate();
		date entryEndDate = _scheduledList[i].getEndDate().getDate();
		ptime entryStartTime = _scheduledList[i].getStartTime().getTime();
		_scheduledList[i].insertEntryNumber(i + 1);
		if(entryStartDate == _today || (entryStartDate < _today && entryEndDate >= _today)){
			if(entryStartTime >= _now);
			EventsToday.push_back(_scheduledList[i]);
		}
	}
	cout << "Remaining entries for Today" << endl << endl;
	if(EventsToday.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "You have no entries for today!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}
	for (unsigned int i = 0; i < EventsToday.size(); i++){
		cout << endl
			<< BORDER << endl
			<< (number) << ". "
			<< EventsToday[i].getShortDisplay() << endl
			<< BORDER;
		number++;
	}
	cout << endl;
	cout << "displaying all remaining entries for today" << endl;
	cout << endl << endl;
}

void DisplayEntries::displayTomorrow(){
	_pageNumber = 1;
	int number = 1;
	stringstream intToString;
	string pageSize;
	unsigned int lastEntry = 3;
	vector<Entry> EventsTomorrow;
	for (unsigned int i = 0; i < _scheduledList.size() ; i++){
		date entryStartDate = _scheduledList[i].getStartDate().getDate();
		date entryEndDate = _scheduledList[i].getEndDate().getDate();
		_scheduledList[i].insertEntryNumber(i + 1);
		if(entryStartDate == _tomorrow || (entryStartDate < _tomorrow && _tomorrow <= entryEndDate)){
			EventsTomorrow.push_back(_scheduledList[i]);
		}
	}
	if(lastEntry > EventsTomorrow.size()){
		lastEntry = EventsTomorrow.size();
	}
	cout << "Entries for tomorrow" << endl;
	if(EventsTomorrow.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "You have no entries for tomorrow!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}
	
	for (int i = 0; i < lastEntry; i++){
		cout << endl
			<< BORDER << endl
			<< EventsTomorrow[i].getEntryNumber() << ". "
			<< EventsTomorrow[i].getShortDisplay() << endl
			<< BORDER;
		number++;
	}
	cout << endl;
	cout << "displaying " << lastEntry << " entry from " << EventsTomorrow.size() << " entry for tomorrow" << endl;
	cout << endl << endl;
}

bool DisplayEntries::isInThePast(ptime entryTime){
	ptime now(second_clock::local_time());
	return entryTime < now;
}