#include "ClashInspector.h"

using namespace std;

ClashInspector::ClashInspector(vector<Entry> scheduledEntry){
	_scheduledEntryList = scheduledEntry;
}

void ClashInspector::compareEntry(Entry inputEntry, int count, bool& clashExists, bool printClash){
	vector<Entry>::iterator iter;
	clashExists = false;
	int listCount = 0;
	for(iter = _scheduledEntryList.begin(); iter != _scheduledEntryList.end(); iter++){
		if(listCount!=count){
			Entry anotherEntry = *iter;
			inspectEntries(inputEntry, anotherEntry, (listCount+1), clashExists, printClash);
		}
		listCount++;
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
			cout << "Clash in Start Date detected with entry no." << listCount 
				<< ": " << anotherEntry.getName()
				<< "! " << endl;
		}
		clashExists = true;
		if((endTimeAnotherEntry > startTimeInputEntry &&  startTimeAnotherEntry < startTimeInputEntry)
			|| (endTimeAnotherEntry > endTimeInputEntry && startTimeAnotherEntry < endTimeInputEntry)
			|| (startTimeInputEntry < startTimeAnotherEntry &&  endTimeInputEntry > startTimeAnotherEntry)
			|| (startTimeInputEntry < endTimeAnotherEntry && endTimeInputEntry > endTimeAnotherEntry)){
				if(printClash){
					cout << "Clash in Time with the same entry is detected!" << endl;
				}
		}
	}
	else if( (endDateAnotherEntry > startDateInputEntry && startDateAnotherEntry < startDateInputEntry) 
		|| (endDateAnotherEntry > endDateInputEntry && startDateAnotherEntry < endDateInputEntry)
		|| (startDateInputEntry < startDateAnotherEntry && endDateInputEntry > startDateAnotherEntry) 
		|| (startDateInputEntry < endDateAnotherEntry && endDateInputEntry > endDateAnotherEntry)){
			if(printClash){
				cout << "Clash in Date periods detected with entry no." << listCount 
				<< ": " << anotherEntry.getName()
				<< "! " << endl;
			}
			clashExists = true;
	}
}





