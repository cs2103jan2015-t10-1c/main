#include "ClashInspector.h"
#include <windows.h>

using namespace std;

ClashInspector::ClashInspector(vector<Entry> entryVector){
	_entryVector = entryVector;
}

void ClashInspector::compareEntry(Entry inputEntry, int count, bool& clashExists, bool printClash){
	vector<Entry>::iterator iter;
	clashExists = false;
	for(unsigned int i = 0; i < _entryVector.size(); i++){
		if(i + 1 != count){
			inspectEntries(inputEntry, _entryVector[i], _entryVector[i].getEntryNumber(), clashExists, printClash);
		}
	}
}

void ClashInspector::inspectEntries(Entry inputEntry, Entry anotherEntry, int listCount, bool& clashExists, bool printClash){
	date startDateInputEntry = inputEntry.getStartDate().getDate();
	date endDateInputEntry = inputEntry.getEndDate().getDate();
	date startDateAnotherEntry = anotherEntry.getStartDate().getDate();
	date endDateAnotherEntry = anotherEntry.getEndDate().getDate();
	ptime startTimeInputEntry = inputEntry.getStartTime().getTime();
	ptime endTimeInputEntry = inputEntry.getEndTime().getTime();
	ptime startTimeAnotherEntry = anotherEntry.getStartTime().getTime();
	ptime endTimeAnotherEntry = anotherEntry.getEndTime().getTime();

	if(startDateInputEntry == startDateAnotherEntry){
		if(printClash){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Clash in Start Date detected with entry no." << listCount 
				<< ": " << anotherEntry.getName()
				<< "! " << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

		}
		clashExists = true;
		if((endTimeAnotherEntry > startTimeInputEntry &&  startTimeAnotherEntry < startTimeInputEntry)
			|| (endTimeAnotherEntry > endTimeInputEntry && startTimeAnotherEntry < endTimeInputEntry)
			|| (startTimeInputEntry < startTimeAnotherEntry &&  endTimeInputEntry > startTimeAnotherEntry)
			|| (startTimeInputEntry < endTimeAnotherEntry && endTimeInputEntry > endTimeAnotherEntry)){
				if(printClash){
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
					cout << "Clash in Time with the same entry is detected!" << endl;
					SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
				}
		}
	}
	else if( (endDateAnotherEntry > startDateInputEntry && startDateAnotherEntry < startDateInputEntry) 
		|| (endDateAnotherEntry > endDateInputEntry && startDateAnotherEntry < endDateInputEntry)
		|| (startDateInputEntry < startDateAnotherEntry && endDateInputEntry > startDateAnotherEntry) 
		|| (startDateInputEntry < endDateAnotherEntry && endDateInputEntry > endDateAnotherEntry)){
			if(printClash){
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
				cout << "Clash in Date periods detected with entry no." << listCount 
				<< ": " << anotherEntry.getName()
				<< "! " << endl;
				SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			}
			clashExists = true;
	}
}





