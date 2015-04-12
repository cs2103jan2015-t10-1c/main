//@author A0115902N
#include "ClashInspector.h"
#include <windows.h>
using namespace std;

const string ClashInspector::CLASH_MESSAGE = "Clashes with entry no.";
const string ClashInspector::COLON = ":";
const string ClashInspector::EXCLAMATION_MARK = "!";


ClashInspector::ClashInspector(vector<Entry> entryVector){
	_entryVector = entryVector;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ClashInspector::compareEntry(Entry inputEntry, int count, bool& clashExists, bool printClash){
	vector<Entry>::iterator iter;
	clashExists = false;
	for(unsigned int i = 0; i < _entryVector.size(); i++){
		Entry entryBeingCompared = _entryVector[i];
		if(i + 1 != count){
			inspectEntries(inputEntry, entryBeingCompared, entryBeingCompared.getEntryNumber(), clashExists, printClash);
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
			if((endTimeAnotherEntry > startTimeInputEntry &&  startTimeAnotherEntry < startTimeInputEntry)//input start time is in between the other entry's 2 time values
				|| (endTimeAnotherEntry > endTimeInputEntry && startTimeAnotherEntry < endTimeInputEntry)//input end time is in between the other entry's 2 time values
				|| (startTimeInputEntry < startTimeAnotherEntry &&  endTimeInputEntry > startTimeAnotherEntry)//the other entry's start time is in between input entry's 2 time values
				|| (startTimeInputEntry < endTimeAnotherEntry && endTimeInputEntry > endTimeAnotherEntry)){//the other entry's end time is in between input entry's 2 time values
					if(printClash){
						SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
						cout << CLASH_MESSAGE << listCount
							<< COLON  
							<< anotherEntry.getName()
							<< EXCLAMATION_MARK << endl;
						clashExists = true;
						SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
					}
			}
		}
	}
	else if( (endDateAnotherEntry > startDateInputEntry && startDateAnotherEntry < startDateInputEntry) //input start date is in between the other entry's 2 date values
		|| (endDateAnotherEntry > endDateInputEntry && startDateAnotherEntry < endDateInputEntry)//input end date is in between the other entry's 2 date values
		|| (startDateInputEntry < startDateAnotherEntry && endDateInputEntry > startDateAnotherEntry) //the other entry's start date is in between input entry's 2 date values
		|| (startDateInputEntry < endDateAnotherEntry && endDateInputEntry > endDateAnotherEntry)){//the other entry's end date is in between input entry's 2 date values
			if(printClash){
				SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
				cout << CLASH_MESSAGE << listCount 
					<< COLON 
					<< anotherEntry.getName()
					<< EXCLAMATION_MARK << endl;
				SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			}
			clashExists = true;
	}
}





