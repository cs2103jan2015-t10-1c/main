#include "SearchEntries.h"

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
		
		else if (marker == ALL_MARKER){
			searchAll(userInput);
		}
		else {
			cout << "Wrong search input is given!" << endl << endl;
		}
	}
	pageNumber = _pageNumber;
}

void SearchEntries::searchTag(string keyword){
	vector<Entry> searchResult;
	bool print = false;
	int numberOfPages;
	int firstEntry;
	int lastEntry;
	//initialise search results
	for(int i = 0; i < _scheduledList.size(); i++){
		bool tagFound = false;
		_scheduledList[i].insertEntryNumber(i+1);
		_scheduledList[i].searchEntryTag(keyword, tagFound, print);
		if(tagFound){
			searchResult.push_back(_scheduledList[i]);
		}
	}
	cout << endl << endl
		<< "Scheduled Entries containing tag: " << keyword
		<< endl;
	initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);

	for (int i = firstEntry; i < lastEntry; i++){
		cout << BORDER << endl
			<< searchResult[i].getEntryNumber() << ". "
			<< searchResult[i].getShortDisplay() << endl
			<< BORDER << endl;
	}
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
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
			size_t found = _scheduledList[i].getName().find(inputName);
			if (found != string::npos){
				nameFound = true;
			}
			if(nameFound){
				searchResult.push_back(_scheduledList[i]);
			}
		}

		cout << "Scheduled Entries containing " << inputName << " in their name:" << endl;

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);

		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
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
			size_t found = _scheduledList[i].getLocation().find(inputLocation);
			if (found != string::npos){
				locationFound = true;
			}
			if(locationFound){
				searchResult.push_back(_scheduledList[i]);
			}
		}
		cout << "Scheduled Entries containing " << inputLocation << " in their location:" << endl;

		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;

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
				statusMatches == true;
				searchResult.push_back(_scheduledList[i]);
			}
		}
		cout << "Scheduled Entries that is/are " << inputStatus << ":" << endl;
		initialisePaging(numberOfPages, searchResult, firstEntry, lastEntry);
		for (int i = firstEntry; i < lastEntry; i++){
			cout << BORDER << endl
				<< searchResult[i].getEntryNumber() << ". "
				<< searchResult[i].getShortDisplay() << endl
				<< BORDER << endl;
			}
		cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
			<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl;

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
	Date inputDate;
	int inputDay;
	int inputMonth;
	int inputYear;
	_datetimeParser.convertDate(userInput, inputDay, inputMonth, inputYear);
	_initialiser.initialiseDate(inputDate, inputDay, inputMonth, inputYear);
	int count = 1;
	cout << "Scheduled Entries on the date " << inputDate.getDay() << " "
		<< inputDate.getMonth() << " "
		<< inputDate.getYear() << " "
		":" << endl << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			bool isInBetweenStartDateAndEndDate = iterScheduledEntry->getStartDate().getDate() <= inputDate.getDate() && iterScheduledEntry->getEndDate().getDate() >= inputDate.getDate();
			if (isInBetweenStartDateAndEndDate){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getShortDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}
}

void SearchEntries::searchTime(string userInput){
	DateTimeInitialiser _initialiser;
	vector<Entry>::iterator iterScheduledEntry;
	date today(day_clock::local_day());
	//initialise inputTime
	Time inputTime;
	int inputHour;
	int inputMinute;
	int entryStartHour;
	int entryStartMinute;
	int entryEndHour;
	int entryEndMinute;
	_datetimeParser.convertTime(userInput, inputHour, inputMinute);
	_initialiser.initialiseTime(inputTime, inputHour, inputMinute, today);

	int count = 1;
	cout << "Scheduled Entries on the time " << inputTime.getHour() << "."
		<< inputTime.getMinute()
		<< " :" << endl << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			Time entryStartTime;
			Time entryEndTime;
			entryStartHour = iterScheduledEntry->getStartTime().getHour();
			entryStartMinute = iterScheduledEntry->getStartTime().getMinute();
			entryEndHour = iterScheduledEntry->getEndTime().getHour();
			entryEndMinute = iterScheduledEntry->getEndTime().getMinute();
			_initialiser.initialiseTime(entryStartTime, entryStartHour, entryStartMinute, today);
			_initialiser.initialiseTime(entryEndTime, entryEndHour, entryEndMinute, today);
		
			bool isInBetweenStartTimeAndEndTime = entryStartTime.getTime() <= inputTime.getTime() && entryEndTime.getTime() >= inputTime.getTime();
			if (isInBetweenStartTimeAndEndTime){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getShortDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}
}


void SearchEntries::searchAll(string userInput){
		vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;

		int count = 0;
		cout << "Scheduled Entries containing " << userInput << ":" << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			size_t found = iterScheduledEntry->getName().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}

			found = iterScheduledEntry->getLocation().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}

			found = iterScheduledEntry->getTags().find(userInput);
			if (found != string::npos){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}

		count = 0;
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
		}
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
	if(searchResult.size() < ENTRY_PERPAGE){
		lastEntry = searchResult.size();	
	}
}

void SearchEntries::closingMessage(int numberOfPages, int firstEntry, int lastEntry){
	cout << "Page: " << _pageNumber << " out of " << numberOfPages << endl
		<< "displaying entries " << firstEntry+1 << " to " << lastEntry << endl; 
}
