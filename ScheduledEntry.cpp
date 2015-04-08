#include "ScheduledEntry.h"

//Static variables that cannot be initialised in the header file
const string ScheduledEntry::FEEDBACK_ADDED = "added ";
const string ScheduledEntry::FEEDBACK_FROM = " from ";
const string ScheduledEntry::FEEDBACK_TO = " to ";
const string ScheduledEntry::FEEDBACK_AT = " at ";

const string ScheduledEntry::FEEDBACK_EDITED = "edited ";
const string ScheduledEntry::FEEDBACK_ARROW = " --> ";
const string ScheduledEntry::FEEDBACK_NAME = "Name: ";
const string ScheduledEntry::FEEDBACK_DATE = "Date: ";
const string ScheduledEntry::FEEDBACK_NO_DATE = "No date";
const string ScheduledEntry::FEEDBACK_REMOVED = "removed";
const string ScheduledEntry::FEEDBACK_TIME = "Time: ";
const string ScheduledEntry::FEEDBACK_NO_TIME = "No time";
const string ScheduledEntry::FEEDBACK_LOCATION = "Location: ";
const string ScheduledEntry::FEEDBACK_STATUS = "Status: ";
const string ScheduledEntry::FEEDBACK_TAGS_ADDED = "Tags added: ";
const string ScheduledEntry::FEEDBACK_TAGS_REMOVED = "Tags removed: ";
const string ScheduledEntry::FEEDBACK_MOVED_TO = "Moved to ";
const string ScheduledEntry::FEEDBACK_SCHEDULED_LIST = "Scheduled list.";
const string ScheduledEntry::FEEDBACK_FLOATING_LIST = "Floating list.";

const string ScheduledEntry::FEEDBACK_DELETED = "This entry has been deleted:";
const string ScheduledEntry::FEEDBACK_NO_ENTRIES_LEFT = "No entries left.";
const string ScheduledEntry::FEEDBACK_OUT_OF_BOUND = "Entry number is out of bound.";

const string ScheduledEntry::FEEDBACK_SUCCESSFULLY_STORED = " successfully stored at ";

const string ScheduledEntry::FEEDBACK_WRONG_COMMAND = "Wrong command!";

const string ScheduledEntry::STATUS_DONE = "done";
const string ScheduledEntry::STATUS_UNDONE = "undone";

const string ScheduledEntry::SPECIFY_STORAGE_PROMPT = "Please specify where you want to store your: ";
const string ScheduledEntry::SCHEDULED_ENTRIES_PROMPT = "Scheduled entries";
const string ScheduledEntry::FLOATING_ENTRIES_PROMPT = "Floating entries";

const string ScheduledEntry::SCHEDULED_FILE_NAME = "\\FastAddSched.txt";
const string ScheduledEntry::FLOATING_FILE_NAME = "\\FastAddFloat.txt";

const string ScheduledEntry::BORDER = "- - - - - - - - - - - - - - - - -";

ScheduledEntry::ScheduledEntry(){
}

void ScheduledEntry::emptyCounter(){
	_counter.emptyUndoStack();
}

void ScheduledEntry::addEntry(Entry newEntry){
	int latestEntryIndex;
	//scheduled entry
	if (newEntry.getDateStatus()){
		_scheduledList.push_back(newEntry);
		sort(latestEntryIndex);
		_counter.counterAdd(true, latestEntryIndex);
	}

	//floating entry
	else {
		_floatingList.push_back(newEntry);
		latestEntryIndex = _floatingList.size();
		_counter.counterAdd(false, latestEntryIndex);
	}
}

void ScheduledEntry::showAddFeedback(Entry newEntry){
	string entryName = newEntry.getName();
	Date entryStartDate = newEntry.getStartDate();
	Date entryEndDate = newEntry.getEndDate();
	Time entryStartTime = newEntry.getStartTime();
	Time entryEndTime = newEntry.getEndTime();
	string entryLocation = newEntry.getLocation();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN |  FOREGROUND_INTENSITY));
	cout << FEEDBACK_ADDED << entryName;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	if (newEntry.getDateStatus()){
		cout << FEEDBACK_FROM << entryStartDate.getDay() << " " << entryStartDate.getMonth() << " " << entryStartDate.getYear()
			<< FEEDBACK_AT << entryStartTime.getHour() << ".";
		if (entryStartTime.getMinute() < 10){
			cout << '0';
		}
		cout << entryStartTime.getMinute()
			<< FEEDBACK_TO << entryEndDate.getDay() << " " << entryEndDate.getMonth() << " " << entryEndDate.getYear()
			<< FEEDBACK_AT << entryEndTime.getHour() << ".";
		if (entryEndTime.getMinute() < 10){
			cout << '0';
		}
		cout << entryEndTime.getMinute();
	}
		cout << ". " << entryLocation << endl; 
}


string ScheduledEntry::getEntryDisplay(bool isScheduled, int index){
	ostringstream oss;
	oss << endl
		<< BORDER << endl
		<< index << ". ";
	//scheduled entry
	if (isScheduled){	
		oss << _scheduledList[index-1].getFullDisplay();
	}
	//floating entry
	else {
		oss << _floatingList[index-1].getFullDisplay();
	}
	oss << BORDER;

	return oss.str();
}

void ScheduledEntry::removeEntry(bool isScheduled, int index, string& deleteFeedback){
	deleteFeedback = "";
	ostringstream oss;

	//scheduled entry
	if (isScheduled && !_scheduledList.empty()){
		if (index > _scheduledList.size()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));	
			cout << FEEDBACK_OUT_OF_BOUND << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}

		oss << FEEDBACK_DELETED << endl;
		oss << getEntryDisplay(isScheduled, index);
		deleteFeedback = oss.str();
		_counter.counterDelete(true, index, _scheduledList[index-1]);
		_scheduledList.erase(_scheduledList.begin() + index - 1);
	}

	//floating entry
	else if (!isScheduled && !_floatingList.empty()){
		if (index > _floatingList.size()){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << FEEDBACK_OUT_OF_BOUND << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			return;
		}
		
		oss << FEEDBACK_DELETED << endl;
		oss << getEntryDisplay(isScheduled, index);
		deleteFeedback = oss.str();
		_counter.counterDelete(false, index, _floatingList[index-1]);
		_floatingList.erase(_floatingList.begin() + index - 1);
	}

	//no more entry
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << FEEDBACK_NO_ENTRIES_LEFT << endl;
	}
}

void ScheduledEntry::editEntry(bool isScheduled, string userInput, string& editFeedback){
	editFeedback = "";
	ostringstream oss;
	
	EntryEdit editComponent(isScheduled);
	int entryNumber = editComponent.getEntryNumber(userInput);
	editComponent.extractMarkerInfo(userInput);
	
	if (!editComponent.getEditStatus()){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << FEEDBACK_WRONG_COMMAND << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		return;
	}
	else {
		oss << FEEDBACK_EDITED << entryNumber << endl;
	}

	//find the entry to be edited
	vector<Entry>::iterator iter;
	if (isScheduled){
		iter = _scheduledList.begin();
	}
	else {
		iter = _floatingList.begin();
	}
	//loop to find the ith entry
	for (int i = 1; i < entryNumber; i++){
			iter++;
	}
	_counter.counterEdit(isScheduled, entryNumber, *iter);

	//update name
	string newName = editComponent.getName();
	if (newName != ""){
		oss << FEEDBACK_NAME << iter->getName();
		iter->insertName(newName);
		oss << FEEDBACK_ARROW << iter->getName() << endl; 
	}

	//update date
	int inputStartDay;
	if (editComponent.getDateEditStatus()){
		oss << FEEDBACK_DATE;
		Date currentStartDate = iter->getStartDate();
		if (currentStartDate.getDateStatus()){
			int currentStartDay = currentStartDate.getDay();
			string currentStartMonth = currentStartDate.getMonth();
			int currentStartYear = currentStartDate.getYear();
			oss << currentStartDay << " " << currentStartMonth << " " << currentStartYear;

			Date currentEndDate = iter->getEndDate();
			int currentEndDay = currentEndDate.getDay();
			string currentEndMonth = currentEndDate.getMonth();
			int currentEndYear = currentEndDate.getYear();
			bool diffStartEndDay = currentEndDay != currentStartDay;
			bool diffStartEndMonth = currentEndMonth != currentStartMonth;
			bool diffStartEndYear = currentEndYear != currentStartYear;
			if (diffStartEndDay || diffStartEndMonth || diffStartEndYear){
				oss << FEEDBACK_TO << currentEndDay << " " << currentEndMonth << " " << currentEndYear;
			}
		}
		else {	
			oss << FEEDBACK_NO_DATE;		
		}

		int inputStartMonth;
		int inputStartYear;
		int inputEndDay;
		int inputEndMonth;
		int inputEndYear;		
		editComponent.getDate(inputStartDay, inputStartMonth, inputStartYear, inputEndDay, inputEndMonth, inputEndYear);
		/*DateTimeInspector inspector;
		if(!inspector.dateIsValid(inputStartDay, inputStartMonth, inputStartYear)
			|| !inspector.dateIsValid(inputEndDay, inputEndMonth, inputEndYear)){
			editFeedback = "Invalid date\n";
			return;
		}*/

		Date newStartDate;
		newStartDate.insertDay(inputStartDay);
		newStartDate.insertMonth(inputStartMonth);
		newStartDate.insertYear(inputStartYear);
		Date newEndDate;
		newEndDate.insertDay(inputEndDay);
		newEndDate.insertMonth(inputEndMonth);
		newEndDate.insertYear(inputEndYear);
		
		iter->insertStartDate(newStartDate);
		iter->insertEndDate(newEndDate);
		oss << FEEDBACK_ARROW;
		if (inputStartDay == 0){
			oss << FEEDBACK_REMOVED << endl;
		}
		else {
			newStartDate = iter->getStartDate();
			string inputStartMonthString = newStartDate.getMonth();
			oss << inputStartDay << " " << inputStartMonthString << " " << inputStartYear;
			
			newEndDate = iter->getEndDate();
			string inputEndMonthString = newEndDate.getMonth();
			bool diffStartEndDay = inputEndDay != inputStartDay;
			bool diffStartEndMonth = inputEndMonthString != inputStartMonthString;
			bool diffStartEndYear = inputEndYear != inputStartYear;
			if (diffStartEndDay || diffStartEndMonth || diffStartEndYear){
				oss << FEEDBACK_TO << inputEndDay << " " << inputEndMonthString << " " << inputEndYear;
			}
			oss << endl;
		}

		//initialise time for sorting
		Time startTimeInitialiser = iter->getStartTime();
		Time endTimeInitialiser = iter->getEndTime();
		iter->insertStartTime(startTimeInitialiser);
		iter->insertEndTime(endTimeInitialiser);
	}

	//update time
	if (editComponent.getTimeEditStatus()){
		oss << FEEDBACK_TIME ;
		Time currentStartTime = iter->getStartTime();
		int currentStartHour = currentStartTime.getHour();
		int currentStartMinute = currentStartTime.getMinute();
		if (currentStartTime.getTimeStatus() && (currentStartHour != 0 || currentStartMinute != 0)){
			oss << currentStartHour << ".";
			if (currentStartMinute < 10){
					oss << '0';
			}
			oss << currentStartMinute;

			Time currentEndTime = iter->getEndTime();
			int currentEndHour = currentEndTime.getHour();
			int currentEndMinute = currentEndTime.getMinute();
			if (currentEndTime.getTime() != currentStartTime.getTime()){
				oss << FEEDBACK_TO << currentEndHour << ".";
				if (currentEndMinute < 10){
					oss << '0';
				}
				oss << currentEndMinute;
			} 
		}
		else {
			oss << FEEDBACK_NO_TIME;
		}

		int inputStartHour;
		int inputStartMinute;
		int inputEndHour;
		int inputEndMinute;
		editComponent.getTime(inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
		DateTimeInspector inspector;
		if(!inspector.timeIsValid(inputStartHour, inputStartMinute)
			|| !inspector.timeIsValid(inputEndHour, inputEndMinute)){
			editFeedback = "Invalid time\n";
			return;
		}

		Time newStartTime;
		Time newEndTime;
		newStartTime.insertHour(inputStartHour);
		newStartTime.insertMinute(inputStartMinute);
		newEndTime.insertHour(inputEndHour);
		newEndTime.insertMinute(inputEndMinute);

		iter->insertStartTime(newStartTime);
		iter->insertEndTime(newEndTime);
		oss << FEEDBACK_ARROW;
		oss << inputStartHour << ".";
		if (inputStartMinute < 10){
			oss << '0';
		}
		oss << inputStartMinute;
			
		newStartTime = iter->getStartTime();
		newEndTime = iter->getEndTime();
		if (newEndTime.getTime() != newStartTime.getTime()){
			oss << FEEDBACK_TO << inputEndHour << ".";
			if (inputEndMinute < 10){
				oss << '0';
			}
			oss << inputEndMinute;
		}
		oss << endl;
	}

	//update location
	string newLocation = editComponent.getLocation();
	if (newLocation != ""){
		oss << FEEDBACK_LOCATION << iter->getLocation();
		iter->insertLocation(newLocation);
		oss << FEEDBACK_ARROW << iter->getLocation() << endl; 
	}

	//update status
	string newStatus = editComponent.getStatus();
	if (newStatus != ""){
		if (newStatus == STATUS_DONE){
		oss << FEEDBACK_STATUS << iter->getStatus();
		iter->changeStatus();
		oss << FEEDBACK_ARROW << iter->getStatus() << endl; 
		}
		else if (newStatus == STATUS_UNDONE){
			oss << FEEDBACK_STATUS << iter->getStatus();
			iter->initialiseStatus();
			oss << FEEDBACK_ARROW << iter->getStatus() << endl;
		}
	}

	//update added tags
	if (editComponent.getTagAddedStatus()){
		oss << FEEDBACK_TAGS_ADDED;
		editComponent.addTag(*iter, oss);
	}

	//update removed tags
	if (editComponent.getTagRemovedStatus()){
		oss << FEEDBACK_TAGS_REMOVED;
		editComponent.removeTag(*iter, oss);
	}
	
	//sort the list again if either date or time has been edited
	//if date editing is done on scheduled list AND date is not deleted, i.e. no shift from scheduled to floating
	bool dateEditedSort = editComponent.getDateEditStatus() && isScheduled && inputStartDay != 0;
	//if time editing is done on scheduled list. there is no need to check the time as time must have been edited properly
	bool timeEditedSort = editComponent.getTimeEditStatus() && isScheduled;
	if (dateEditedSort || timeEditedSort){
		Entry newEntry = *iter;
		string dummy;
		removeEntry(isScheduled, entryNumber, dummy);
		addEntry(newEntry);
	}

	//move entry from floating to scheduled list and vice versa
	bool isScheduledToFloating = isScheduled && editComponent.getDateEditStatus() && (inputStartDay == 0);
	bool isFloatingToScheduled = !isScheduled && editComponent.getDateEditStatus() && editComponent.getTimeEditStatus();
	if (isScheduledToFloating || isFloatingToScheduled){
		moveScheduledFloating(isScheduled, entryNumber, *iter);
		oss << FEEDBACK_MOVED_TO;
		if (isScheduled){
			oss << FEEDBACK_FLOATING_LIST << endl;
		}
		else {
			oss << FEEDBACK_SCHEDULED_LIST << endl;
		}
	}

	editFeedback = oss.str();
}

void ScheduledEntry::moveScheduledFloating(bool isScheduled, int entryNumber, Entry movedEntry){
	string dummy;
	removeEntry(isScheduled, entryNumber, dummy);
	addEntry(movedEntry);
}

void ScheduledEntry::undo(){
	_counter.execute(_scheduledList, _floatingList);
}

void ScheduledEntry::exit(bool& running){
	cout << SPECIFY_STORAGE_PROMPT << endl;
	
	//write scheduled
	ofstream writeSched;
	string scheduledPath;
	cout << SCHEDULED_ENTRIES_PROMPT << ": ";
	cin >> scheduledPath;
	scheduledPath = scheduledPath + SCHEDULED_FILE_NAME;
	writeSched.open(scheduledPath);
	vector<Entry>::iterator iterSched;

	for (iterSched = _scheduledList.begin(); iterSched != _scheduledList.end(); iterSched++){
		writeSched << iterSched->storeEntry() << endl;
	}
	writeSched.close();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << SCHEDULED_ENTRIES_PROMPT << FEEDBACK_SUCCESSFULLY_STORED << scheduledPath << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	//write floating
	ofstream writeFloat;
	string floatingPath;
	cout << FLOATING_ENTRIES_PROMPT << ": ";
	cin >> floatingPath;
	floatingPath = floatingPath + FLOATING_FILE_NAME;
	writeFloat.open(floatingPath);
	vector<Entry>::iterator iterFloat;

	for (iterFloat = _floatingList.begin(); iterFloat != _floatingList.end(); iterFloat++){
		writeFloat << iterFloat->storeEntry() << endl;
	}
	writeFloat.close();
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << FLOATING_ENTRIES_PROMPT << FEEDBACK_SUCCESSFULLY_STORED << floatingPath << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	running = false;
}

void ScheduledEntry::sort(int& latestEntryIndex){
	latestEntryIndex = _scheduledList.size();
	vector<Entry>::iterator firstIter;
	vector<Entry>::iterator secondIter;
	int count = 0;
	Entry tempEntry;

	//bubble sort
	for (firstIter = _scheduledList.begin(); firstIter != _scheduledList.end(); firstIter++){
		for(secondIter = _scheduledList.begin()+1; secondIter != _scheduledList.end() - count; secondIter++){
			bool isSwapped = false;
			//if the previous entry is larger than the next entry, swap
			if((secondIter - 1)->getStartTime().getTime() > (secondIter)->getStartTime().getTime()){
				tempEntry = *(secondIter-1);
				*(secondIter-1) = *(secondIter);
				*(secondIter) = tempEntry;
				isSwapped = true;
			}

			//if: 1. it is the last iteration of the inner loop, that is the iteration which
			//compares the last element of inner loop with the element before it, and
			//2. a swap occurs in this iteration
			//decrement latesEntryIndex so it will match the index number of latest Entry
			if (secondIter == _scheduledList.end() - count - 1 && isSwapped) {
				latestEntryIndex--;
			}
		}
		count++;
	}
}

vector<Entry> ScheduledEntry::getScheduledList(){
	vector<Entry> ScheduledEntries = _scheduledList;
	return ScheduledEntries;
}

vector<Entry> ScheduledEntry::getFloatingList(){
	vector<Entry> FloatingEntries = _floatingList;
	return FloatingEntries;
}