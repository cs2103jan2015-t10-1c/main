#include "SearchEntries.h"

const string SearchEntries::NAME_MARKER = "name";
const string SearchEntries::LOCATION_MARKER = "place";
const string SearchEntries::STATUS_MARKER = "status";
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
		if (marker == LOCATION_MARKER){
			searchLocation(userInput);
		}
		if (marker == STATUS_MARKER){
			searchStatus(userInput);
		}
		if (marker == ALL_MARKER){
			searchAll(userInput);
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
