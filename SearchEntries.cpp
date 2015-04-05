#include "SearchEntries.h"

const string SearchEntries::NAME_MARKER = "name";
const string SearchEntries::LOCATION_MARKER = "place";
const string SearchEntries::STATUS_MARKER = "status";
const string SearchEntries::DATE_MARKER = "date";
const string SearchEntries::TIME_MARKER = "time";
const string SearchEntries::ALL_MARKER = "all";


SearchEntries::SearchEntries(vector<Entry> scheduledEntries, vector<Entry> floatingEntries){
	_scheduledList = scheduledEntries;
	_floatingList = floatingEntries;
}

void SearchEntries::execute(string userInput){
	userInput = userInput.substr(1);
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
}

void SearchEntries::searchTag(string keyword){
	int count = 1;
	vector<Entry>::iterator iterScheduledEntry;
	vector<Entry>::iterator iterFloatingEntry;
	cout << endl << endl
		<< "Scheduled Entries containing tag: " << keyword
		<< endl;
	for(iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
		iterScheduledEntry->searchEntryTag(keyword, count);
		count ++;
	}
	count = 1;
	cout << endl << endl
		<< "Floating Entries containing tag: " << keyword
		<< endl << endl;
	for(iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
		iterFloatingEntry->searchEntryTag(keyword, count);
		count ++;
	}
}

void SearchEntries::searchName(string inputName){
		vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;

		int count = 0;
		cout << "Scheduled Entries containing name:  " << inputName << ":" << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			if (iterScheduledEntry->getName() == inputName){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}
		count = 0;
		cout << "Floating Entries containing name:  " << inputName << ":" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			if (iterFloatingEntry->getName() == inputName){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
			count++;
		}
}

void SearchEntries::searchLocation(string inputLocation){
		vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;

		int count = 1;
		cout << "Scheduled Entries containing location " << inputLocation << ":" << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			if (iterScheduledEntry->getLocation() == inputLocation){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
		count = 1;
		cout << "Floating Entries containing location " << inputLocation << ":" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			if (iterFloatingEntry->getLocation() == inputLocation){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getFullDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
}

void SearchEntries::searchStatus(string inputStatus){
		vector<Entry>::iterator iterScheduledEntry;
		vector<Entry>::iterator iterFloatingEntry;
		int count = 1;
		cout << "Scheduled Entries that is/are " << inputStatus << ":" << endl;
		for (iterScheduledEntry = _scheduledList.begin(); iterScheduledEntry != _scheduledList.end(); iterScheduledEntry++){
			if (iterScheduledEntry->getStatus() == inputStatus){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterScheduledEntry->getShortDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
		count = 1;
		cout << "Floating Entries that is/are " << inputStatus << ":" << endl;
		for (iterFloatingEntry = _floatingList.begin(); iterFloatingEntry != _floatingList.end(); iterFloatingEntry++){
			if (iterFloatingEntry->getStatus() == inputStatus){
				cout << "- - - - - - - - - - - - - - -" << endl;
				cout << count << ". " << iterFloatingEntry->getShortDisplay();
				cout << "- - - - - - - - - - - - - - -" << endl;				
				cout << endl;
			}
			count++;
		}
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
