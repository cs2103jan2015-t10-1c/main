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
const int SearchEntries::ENTRY_PERPAGE = 3;
const string SearchEntries::BORDER = "- - - - - - - - - - - - - - - - - - - - - - -";


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
	_pageNumber = 1;

}

void SearchEntries::execute(string userInput, int& pageNumber, string& previousSearchInput){
	_pageNumber = pageNumber;
	userInput = userInput.substr(1);
	if (userInput == NEXT_MARKER){
		_pageNumber++;
		userInput = previousSearchInput;
	} else if (userInput == PREV_MARKER){
		_pageNumber--;
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
	pageNumber = _pageNumber;
}

void SearchEntries::searchTag(string keyword){
	vector<Entry> searchResult;
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	bool print = false;
	//initialise search results
	for(int i = 0; i < _scheduledList.size(); i++){
		bool tagFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		_scheduledList[i].searchEntryTag(keyword, tagFound);
		if(tagFound){
			searchResult.push_back(_scheduledList[i]);
		}
	}
	if(searchResult.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		return;
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << endl << endl
		<< "Scheduled Entries containing tag: " << keyword
		<< endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);

	for (int i = firstEntry; i < lastEntry; i++){
		cout << BORDER << endl
			<< searchResult[i].getEntryNumber() << ". "
			<< searchResult[i].getShortDisplay() << endl
			<< BORDER << endl;
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	//__________________________________________________________________________//

	/*count = 1;
	cout << endl << endl
		<< "Floating Entries containing tag: " << keyword
		<< endl << endl;
	for(int i = 0; i < _floatingList.size(); i++){
		_floatingList[i].searchEntryTag(keyword, count);
		count ++;
		}*/
}

void SearchEntries::searchName(string inputName){
		/*vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;*/

		vector<Entry> searchResult;
		int numberOfPages;
		int firstEntry;
		int lastEntry;
		//initialise search results
		for(int i = 0; i < _scheduledList.size(); i++){
			bool nameFound = false;
			_scheduledList[i].insertEntryNumber(i+1);
			string entryName = _scheduledList[i].getName();
			string::const_iterator it = caseInsFind(entryName, inputName);
			if (it != entryName.end()){
				nameFound = true;
			}
			if(nameFound){
				searchResult.push_back(_scheduledList[i]);
			}
		}
		if(searchResult.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries containing " << inputName << " in their name:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);

		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		/*count = 0;
		cout << "Floating Entries containing " << inputName << " in their name:" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			size_t found = iterFloatingEntry->getName().find(inputName);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}*/
}

void SearchEntries::searchLocation(string inputLocation){
		/*vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;*/

		vector<Entry> searchResult;
		int numberOfPages;
		int firstEntry;
		int lastEntry;
		//initialise search results
		for(int i = 0; i < _scheduledList.size(); i++){
			bool locationFound = false;
			_scheduledList[i].insertEntryNumber(i+1);
			string entryLocation = _scheduledList[i].getLocation();
			string::const_iterator it = caseInsFind(entryLocation, inputLocation);
			if (it != entryLocation.end()){
				locationFound = true;
			}
			if(locationFound){
				searchResult.push_back(_scheduledList[i]);
			}
		}

		if(searchResult.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries containing " << inputLocation << " in their location:" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		/*count = 1;
		cout << "Floating Entries containing " << inputLocation << " in their location:" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			size_t found = iterFloatingEntry->getLocation().find(inputLocation);
			if (iterFloatingEntry->getLocation() == inputLocation){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}*/
}

void SearchEntries::searchStatus(string inputStatus){
		/*vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;*/
		vector<Entry> searchResult;
		int numberOfPages;
		int firstEntry;
		int lastEntry;
		//initialise search results
		for(int i = 0; i < _scheduledList.size(); i++){
			bool statusMatches = false;
			_scheduledList[i].insertEntryNumber(i+1);
			if(inputStatus == _scheduledList[i].getStatus()){
				statusMatches = true;
				searchResult.push_back(_scheduledList[i]);
			}
		}

		cout << searchResult.size() << endl;

		if(searchResult.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries that is/are " << inputStatus << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		/*count = 1;
		cout << "Floating Entries that is/are " << inputStatus << ":" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			if (iterFloatingEntry->getStatus() == inputStatus){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getShortDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}*/
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
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "date search input is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}
	_initialiser.initialiseDate(inputDate, inputDay, inputMonth, inputYear);
	//search result vector initialisation

	vector<Entry> searchResult;
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	//initialise search results
	for(int i = 0; i < _scheduledList.size(); i++){
		bool dateFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		Date entryStartDate = _scheduledList[i].getStartDate();
		Date entryEndDate = _scheduledList[i].getEndDate();
		if(inputDate.getDate() >= entryStartDate.getDate() && inputDate.getDate() <= entryEndDate.getDate()){
			dateFound = true;
			searchResult.push_back(_scheduledList[i]);
		}
	}
	if(searchResult.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Scheduled Entries on the date " << inputDate.getDay() << " "
		<< inputDate.getMonth() << " "
		<< inputDate.getYear() << " "
		":" << endl << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
	for (int i = firstEntry; i < lastEntry; i++){
		cout << BORDER << endl
			<< searchResult[i].getEntryNumber() << ". "
			<< searchResult[i].getShortDisplay() << endl
			<< BORDER << endl;
		}
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

}

void SearchEntries::searchTime(string userInput){
	DateTimeInitialiser _initialiser;
	vector<Entry> searchResult;
	int numberOfPages;
	int firstEntry;
	int lastEntry;
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
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "time search input is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}
	_initialiser.initialiseTime(inputTime, inputHour, inputMinute, today);

	for(int i = 0; i < _scheduledList.size(); i++){
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
				searchResult.push_back(_scheduledList[i]);
			}
	}
	if(searchResult.empty()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Entries are not found" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Scheduled Entries on the time " << inputTime.getHour() << "."
		<< inputTime.getMinute()
		<< " :" << endl << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
	for (int i = firstEntry; i < lastEntry; i++){
		cout << BORDER << endl
			<< searchResult[i].getEntryNumber() << ". "
			<< searchResult[i].getShortDisplay() << endl
			<< BORDER << endl;
		}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}


void SearchEntries::searchAll(string userInput){
		/*vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;*/
		vector<Entry> searchResult;
		int numberOfPages;
		int firstEntry;
		int lastEntry;
		//initialise search results
		for(int i = 0; i < _scheduledList.size(); i++){
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
				searchResult.push_back(_scheduledList[i]);
			}
		}

		if(searchResult.empty()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Entries are not found" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Scheduled Entries with keyword " << userInput << ":" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		

		/*count = 0;
		cout << "Floating Entries containing " << userInput << ":" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			size_t found = iterFloatingEntry->getName().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}

			found = iterFloatingEntry->getLocation().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}

			found = iterFloatingEntry->getTags().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}*/
}

void SearchEntries::initialisePaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry){
	//initialise search result parameters
	numberOfPages = searchResult.size()/ENTRY_PERPAGE;
	int numberOfEntriesOnLastPage = searchResult.size()%ENTRY_PERPAGE;
	if(numberOfEntriesOnLastPage > 0){
		numberOfPages++;
	}
	//prevent abort for exceeding page
	if(_pageNumber > numberOfPages){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Page does not exist!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		_pageNumber--;
	}
	firstEntry = ENTRY_PERPAGE*(_pageNumber-1);
	lastEntry = firstEntry + ENTRY_PERPAGE;
	//case for the last page
	if(_pageNumber == numberOfPages){
		lastEntry = firstEntry + numberOfEntriesOnLastPage;
	}
	//prevent abort for number of entries less than 5
	if(searchResult.size() <= ENTRY_PERPAGE){
		lastEntry = searchResult.size();	
	}
}

void SearchEntries::closingMessage(int numberOfPages, int firstEntry, int lastEntry){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}
