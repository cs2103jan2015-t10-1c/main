#include "SearchEntries.h"
#include <algorithm>
#include <iterator>
#include <cctype>
#include <Windows.h>

const string SearchEntries::NAME_MARKER = "name";
const string SearchEntries::LOCATION_MARKER = "place";
const string SearchEntries::STATUS_MARKER = "status";
const string SearchEntries::DATE_MARKER = "date";
const string SearchEntries::TIME_MARKER = "time";
const string SearchEntries::ALL_MARKER = "all";
const string SearchEntries::NEXT_MARKER = "next";
const string SearchEntries::PREV_MARKER = "prev";
const string SearchEntries::DAY_MARKER = "day";
const int SearchEntries::ENTRY_PERPAGE = 3;
const string SearchEntries::BORDER = "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -";


inline bool caseInsCharCompSingle(char a, char b) {
   return(toupper(a) == b);
}

string::const_iterator caseInsFind(string& s, const string& p) {
   string tmp;

   transform(p.begin(), p.end(),            
             back_inserter(tmp),                 
             toupper);

   return(search(s.begin(), s.end(),         
                 tmp.begin(), tmp.end(),     
                 caseInsCharCompSingle));        
}

SearchEntries::SearchEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
	_scheduledPageNumber = 1;
	_floatingPageNumber = 1;
	 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void SearchEntries::execute(string userInput, int& scheduledPageNumber, int& floatingPageNumber, string& previousSearchInput){
	_scheduledPageNumber = scheduledPageNumber;
	_floatingPageNumber = floatingPageNumber;
	userInput = userInput.substr(1);
	if (userInput == NEXT_MARKER){
		_scheduledPageNumber++;
		_floatingPageNumber++;
		userInput = previousSearchInput;
	} else if (userInput == PREV_MARKER){
		_scheduledPageNumber--;
		_floatingPageNumber--;
		userInput = previousSearchInput;
	} else{
		previousSearchInput = userInput;
	}
	if (userInput[0] == '#'){
		searchTag(userInput);
	}
	else{
		string marker = userInput.substr(0, userInput.find_first_of(' '));
		userInput = userInput.erase(0, userInput.find_first_of(' ')+1);
		if (marker == NAME_MARKER){
			searchName(userInput);
		}
		else if (marker == LOCATION_MARKER){
			searchLocation(userInput);
		}
		else if (marker == STATUS_MARKER){
			searchStatus(userInput);
		}
		else if (marker == DATE_MARKER){
			searchDate(userInput);
		}
		else if (marker == TIME_MARKER){
			searchTime(userInput);
		}
		
		else {
			searchAll(userInput);
		}

		/*else {
			cout << "Wrong search input is given!" << endl << endl;
		}*/
	}
	scheduledPageNumber = _scheduledPageNumber;
	floatingPageNumber = _floatingPageNumber;
}

void SearchEntries::searchTag(string keyword){
	initialiseSearchPagingAttributes();
	bool print = false;
	//initialise search results
	for(unsigned int i = 0; i < _scheduledList.size(); i++){
		bool tagFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		_scheduledList[i].searchEntryTag(keyword, tagFound);
		if(tagFound){
			_scheduledSearchResult.push_back(_scheduledList[i]);
		}
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << endl << endl
		<< "Scheduled Entries containing tag: " << keyword
		<< endl;
	if(_scheduledSearchResult.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		loadScheduledSearchResult();
	}

	//floatingEntries
	print = false;
	//initialise search results
	for(unsigned int i = 0; i < _floatingList.size(); i++){
		bool tagFound = false;
		_floatingList[i].insertEntryNumber(i+1);
		_floatingList[i].searchEntryTag(keyword, tagFound);
		if(tagFound){
			_floatingSearchResult.push_back(_scheduledList[i]);
		}
	}
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << endl << endl
		<< "Floating Entries containing tag: " << keyword
		<< endl;
	if(_floatingSearchResult.empty()){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		loadFloatingSearchResult();
	}
}
void SearchEntries::searchName(string inputName){
	initialiseSearchPagingAttributes();
		//initialise search results
		for(unsigned int i = 0; i < _scheduledList.size(); i++){
			bool nameFound = false;
			_scheduledList[i].insertEntryNumber(i+1);
			string entryName = _scheduledList[i].getName();
			string::const_iterator it = caseInsFind(entryName, inputName);
			if (it != entryName.end()){
				nameFound = true;
			}
			if(nameFound){
				_scheduledSearchResult.push_back(_scheduledList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries containing " << inputName << " in their name:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_scheduledSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadScheduledSearchResult();
		}
		//floating search
		for(unsigned int i = 0; i < _floatingList.size(); i++){
			bool nameFound = false;
			_floatingList[i].insertEntryNumber(i+1);
			string entryName = _floatingList[i].getName();
			string::const_iterator it = caseInsFind(entryName, inputName);
			if (it != entryName.end()){
				nameFound = true;
			}
			if(nameFound){
				_floatingSearchResult.push_back(_scheduledList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Floating Entries containing " << inputName << " in their name:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_floatingSearchResult.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadFloatingSearchResult();
		}
}

void SearchEntries::searchLocation(string inputLocation){
	initialiseSearchPagingAttributes();
		//initialise search results
		for(unsigned int i = 0; i < _scheduledList.size(); i++){
			bool locationFound = false;
			_scheduledList[i].insertEntryNumber(i+1);
			string entryLocation = _scheduledList[i].getLocation();
			string::const_iterator it = caseInsFind(entryLocation, inputLocation);
			if (it != entryLocation.end()){
				locationFound = true;
			}
			if(locationFound){
				_scheduledSearchResult.push_back(_scheduledList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries containing " << inputLocation << " in their location:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_scheduledSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
		loadScheduledSearchResult();
		}
		//initialise floating search result
		for(unsigned int i = 0; i < _floatingList.size(); i++){
			bool locationFound = false;
			_floatingList[i].insertEntryNumber(i+1);
			string entryLocation = _floatingList[i].getLocation();
			string::const_iterator it = caseInsFind(entryLocation, inputLocation);
			if (it != entryLocation.end()){
				locationFound = true;
			}
			if(locationFound){
				_floatingSearchResult.push_back(_floatingList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Floating Entries containing " << inputLocation << " in their location:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_floatingSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadFloatingSearchResult();
		}
}

void SearchEntries::searchStatus(string inputStatus){
	initialiseSearchPagingAttributes();
		//initialise search results
		for(unsigned int i = 0; i < _scheduledList.size(); i++){
			bool statusMatches = false;
			_scheduledList[i].insertEntryNumber(i+1);
			if(inputStatus == _scheduledList[i].getStatus()){
				statusMatches = true;
				_scheduledSearchResult.push_back(_scheduledList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries that is/are " << inputStatus << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_scheduledSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadScheduledSearchResult();
		}

		//Floating Search Result
		for(unsigned int i = 0; i < _floatingList.size(); i++){
			bool statusMatches = false;
			_floatingList[i].insertEntryNumber(i+1);
			if(inputStatus == _floatingList[i].getStatus()){
				statusMatches = true;
				_floatingSearchResult.push_back(_floatingList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Floating Entries that is/are " << inputStatus << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		if(_floatingSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadFloatingSearchResult();
		}
}

void SearchEntries::searchDate(string userInput){
	DateTimeInitialiser _initialiser;

	vector<Entry>::iterator iterScheduledEntry;
	//Date initialisation
	Date inputDate;
	int inputDay;
	int inputMonth;
	int inputYear;
	DateTimeInspector inspectDate;
	_datetimeParser.convertDate(userInput, inputDay, inputMonth, inputYear);
	if(!inspectDate.dateIsValid(inputDay, inputMonth, inputYear)){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Date search input is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		_initialiser.initialiseDate(inputDate, inputDay, inputMonth, inputYear);
	}

	//initialise search results
	for(unsigned int i = 0; i < _scheduledList.size(); i++){
		bool dateFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		Date entryStartDate = _scheduledList[i].getStartDate();
		Date entryEndDate = _scheduledList[i].getEndDate();
		if(inputDate.getDate() >= entryStartDate.getDate() && inputDate.getDate() <= entryEndDate.getDate()){
			dateFound = true;
			_scheduledSearchResult.push_back(_scheduledList[i]);
		}
	}
	if(_scheduledSearchResult.empty()){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Scheduled Entries on the date " << inputDate.getDay() << " "
		<< inputDate.getMonth() << " "
		<< inputDate.getYear() << " "
		":" << endl << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	if(_scheduledSearchResult.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		loadScheduledSearchResult();
	}
}

void SearchEntries::searchTime(string userInput){
	initialiseSearchPagingAttributes();
	DateTimeInitialiser _initialiser;
	date today(day_clock::local_day());
	//initialise inputTime
	Time inputTime;
	int inputHour;
	int inputMinute;
	int entryStartHour;
	int entryStartMinute;
	int entryEndHour;
	int entryEndMinute;
	DateTimeInspector inspectTime;
	_datetimeParser.convertTime(userInput, inputHour, inputMinute);
	if(!inspectTime.timeIsValid(inputHour, inputMinute)){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Time search input is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		_initialiser.initialiseTime(inputTime, inputHour, inputMinute, today);
	}

	for(unsigned int i = 0; i < _scheduledList.size(); i++){
		bool timeFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		Time entryStartTime;
		Time entryEndTime;
		entryStartHour = _scheduledList[i].getStartTime().getHour();
		entryStartMinute = _scheduledList[i].getStartTime().getMinute();
		entryEndHour = _scheduledList[i].getEndTime().getHour();
		entryEndMinute = _scheduledList[i].getEndTime().getMinute();
		_initialiser.initialiseTime(entryStartTime, entryStartHour, entryStartMinute, today);
		_initialiser.initialiseTime(entryEndTime, entryEndHour, entryEndMinute, today);
		bool isInBetweenStartTimeAndEndTime = entryStartTime.getTime() <= inputTime.getTime() && entryEndTime.getTime() >= inputTime.getTime();
			if (isInBetweenStartTimeAndEndTime){
				_scheduledSearchResult.push_back(_scheduledList[i]);
			}
	}

	if(_scheduledSearchResult.empty()){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Scheduled Entries on the time " << inputTime.getHour() << "."
		<< inputTime.getMinute()
		<< " :" << endl << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	if(_scheduledSearchResult.empty()){
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		loadScheduledSearchResult();
	}
}


void SearchEntries::searchAll(string userInput){
		//initialise search results

		for(unsigned int i = 0; i < _scheduledList.size(); i++){
			_scheduledList[i].insertEntryNumber( i + 1);
			bool allFound = false;
			_scheduledList[i].insertEntryNumber(i+1);
			string entryName = _scheduledList[i].getName();
			string::const_iterator it = caseInsFind(entryName, userInput);
			if (it != entryName.end()){
				allFound = true;
			}
			string entryLocation = _scheduledList[i].getLocation();
			it = caseInsFind(entryLocation, userInput);
			if (it != entryLocation.end()){
				allFound = true;
			}
			string entryTag = _scheduledList[i].getTags();
			it = caseInsFind(entryTag, userInput);
			if (it != entryTag.end()){
				allFound = true;
			}
			if (allFound){
				_scheduledSearchResult.push_back(_scheduledList[i]);
			}
		}

		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries with keyword " << userInput << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_scheduledSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadScheduledSearchResult();
		}
		
		//floating Entries
		for(unsigned int i = 0; i < _floatingList.size(); i++){
			_floatingList[i].insertEntryNumber( i + 1);
			bool allFound = false;
			_floatingList[i].insertEntryNumber(i+1);
			string entryName = _floatingList[i].getName();
			string::const_iterator it = caseInsFind(entryName, userInput);
			if (it != entryName.end()){
				allFound = true;
			}
			string entryLocation = _floatingList[i].getLocation();
			it = caseInsFind(entryLocation, userInput);
			if (it != entryLocation.end()){
				allFound = true;
			}
			string entryTag = _floatingList[i].getTags();
			it = caseInsFind(entryTag, userInput);
			if (it != entryTag.end()){
				allFound = true;
			}
			if (allFound){
				_floatingSearchResult.push_back(_floatingList[i]);
			}
		}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries with keyword " << userInput << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		if(_floatingSearchResult.empty()){
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		} else {
			loadFloatingSearchResult();
		}
}

void SearchEntries::initialiseScheduledPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry){
	//initialise search result parameters
	numberOfPages = searchResult.size()/ENTRY_PERPAGE;
	int numberOfEntriesOnLastPage = searchResult.size()%ENTRY_PERPAGE;
	if(numberOfEntriesOnLastPage > 0){
		numberOfPages++;
	}
	//prevent abort for exceeding page
	if(_scheduledPageNumber > numberOfPages){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Page does not exist!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		_scheduledPageNumber--;
	}
	firstEntry = ENTRY_PERPAGE*(_scheduledPageNumber-1);
	lastEntry = firstEntry + ENTRY_PERPAGE;
	//case for the last page
	if(_scheduledPageNumber == numberOfPages){
		lastEntry = firstEntry + numberOfEntriesOnLastPage;
	}
	//prevent abort for number of entries less than maximum page
	if(searchResult.size() <= ENTRY_PERPAGE){
		lastEntry = searchResult.size();	
	}
}

void SearchEntries::initialiseFloatingPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry){
	//initialise search result parameters
	numberOfPages = searchResult.size()/ENTRY_PERPAGE;
	int numberOfEntriesOnLastPage = searchResult.size()%ENTRY_PERPAGE;
	if(numberOfEntriesOnLastPage > 0){
		numberOfPages++;
	}
	//prevent abort for exceeding page
	if(_floatingPageNumber > numberOfPages){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Page does not exist!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		_floatingPageNumber--;
	}
	firstEntry = ENTRY_PERPAGE*(_floatingPageNumber-1);
	lastEntry = firstEntry + ENTRY_PERPAGE;
	//case for the last page
	if(_floatingPageNumber == numberOfPages){
		lastEntry = firstEntry + numberOfEntriesOnLastPage;
	}
	//prevent abort for number of entries less than maximum page
	if(searchResult.size() <= ENTRY_PERPAGE){
		lastEntry = searchResult.size();	
	}
}

void SearchEntries::displaySearchResults(vector<Entry> searchResult, int firstEntry, int lastEntry){
	for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
	}
}

void SearchEntries::closingScheduledMessage(int numberOfPages, int firstEntry, int lastEntry){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _scheduledPageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void SearchEntries::closingFloatingMessage(int numberOfPages, int firstEntry, int lastEntry){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _floatingPageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void SearchEntries::initialiseSearchPagingAttributes(){
	_scheduledSearchResult.clear();
	_floatingSearchResult.clear();
	_firstScheduledEntry = 1;
	_lastScheduledEntry = 1;
	_firstScheduledEntry = 1;
	_lastScheduledEntry = 1;
	_numberOfPagesScheduledResult = 1;
	_numberOfPagesFloatingResult = 1;
}

void SearchEntries::loadScheduledSearchResult(){
	initialiseScheduledPaging(_numberOfPagesScheduledResult, _scheduledSearchResult, _firstScheduledEntry, _lastScheduledEntry);
	displaySearchResults(_scheduledSearchResult, _firstScheduledEntry, _lastScheduledEntry);

	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	closingScheduledMessage(_numberOfPagesScheduledResult, _firstScheduledEntry, _lastScheduledEntry);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void SearchEntries::loadFloatingSearchResult(){
	initialiseFloatingPaging(_numberOfPagesFloatingResult, _floatingSearchResult, _firstFloatingEntry, _lastFloatingEntry);
	displaySearchResults(_floatingSearchResult, _firstFloatingEntry, _lastFloatingEntry);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	closingFloatingMessage(_numberOfPagesFloatingResult, _firstFloatingEntry, _lastFloatingEntry);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	cout << endl;
}
