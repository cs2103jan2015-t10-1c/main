#include "ClashInspector.h"

using namespace std;

ClashInspector::ClashInspector(vector<Entry> scheduledEntry){
	_scheduledEntryList = scheduledEntry;
}

void ClashInspector::compareEntry(Entry inputEntry, int count){
	vector<Entry>::iterator iter;
	bool clash = false;
	int listCount = 0;
	for(iter = _scheduledEntryList.begin(); iter != _scheduledEntryList.end(); iter++){
		if(listCount!=count){
			Entry anotherEntry = *iter;
			inspectEntries(inputEntry, anotherEntry, clash, (listCount+1));
		}
		listCount++;
	}
}

void ClashInspector::inspectEntries(Entry inputEntry, Entry anotherEntry, bool& status, int listCount){
	date startDateInputEntry = inputEntry.getStartDate().getDate();
	date endDateInputEntry = inputEntry.getEndDate().getDate();
	date startDateAnotherEntry = anotherEntry.getStartDate().getDate();
	date endDateAnotherEntry = anotherEntry.getEndDate().getDate();
	ptime startTimeInputEntry = inputEntry.getStartTime().getTime();
	ptime endTimeInputEntry = inputEntry.getEndTime().getTime();
	ptime startTimeAnotherEntry = anotherEntry.getStartTime().getTime();
	ptime endTimeAnotherEntry = anotherEntry.getEndTime().getTime();

	if(startDateInputEntry == startDateAnotherEntry){
		cout << "Clash in Start Date detected with entry no." << listCount << "! " << endl;
		status = true;
		if((endTimeAnotherEntry > startTimeInputEntry &&  startTimeAnotherEntry < startTimeInputEntry)
			|| (endTimeAnotherEntry > endTimeInputEntry && startTimeAnotherEntry < endTimeInputEntry)
			|| (startTimeInputEntry < startTimeAnotherEntry &&  endTimeInputEntry > startTimeAnotherEntry)
			|| (startTimeInputEntry < endTimeAnotherEntry && endTimeInputEntry > endTimeAnotherEntry)){
			cout << "Clash in Time detected with entry no." << listCount << "! " << endl;
		}
	}
	else if( (endDateAnotherEntry > startDateInputEntry && startDateAnotherEntry < startDateInputEntry) 
		|| (endDateAnotherEntry > endDateInputEntry && startDateAnotherEntry < endDateInputEntry)
		|| (startDateInputEntry < startDateAnotherEntry && endDateInputEntry > startDateAnotherEntry) 
		|| (startDateInputEntry < endDateAnotherEntry && endDateInputEntry > endDateAnotherEntry)){
		cout << "Clash in Date periods detected with entry no." << listCount << "! " << endl;
		status = true;
	}
}





