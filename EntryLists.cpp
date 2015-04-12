#include "EntryLists.h"

//Static variables that cannot be initialised in the header file
const string EntryLists::FEEDBACK_ADDED_AT_NUMBER = "added at number ";
const string EntryLists::FEEDBACK_FROM = " from ";
const string EntryLists::FEEDBACK_TO = " to ";
const string EntryLists::FEEDBACK_AT = " at ";
const string EntryLists::FEEDBACK_EDITED = "edited ";
const string EntryLists::FEEDBACK_ARROW = " --> ";
const string EntryLists::FEEDBACK_NAME = "Name: ";
const string EntryLists::FEEDBACK_DATE = "Date: ";
const string EntryLists::FEEDBACK_NO_DATE = "No date";
const string EntryLists::FEEDBACK_REMOVED = "removed";
const string EntryLists::FEEDBACK_TIME = "Time: ";
const string EntryLists::FEEDBACK_NO_TIME = "No time";
const string EntryLists::FEEDBACK_LOCATION = "Location: ";
const string EntryLists::FEEDBACK_STATUS = "Status: ";
const string EntryLists::FEEDBACK_INVALID_STATUS = "Invalid status!";
const string EntryLists::FEEDBACK_TAGS_ADDED = "Tags added: ";
const string EntryLists::FEEDBACK_TAGS_REMOVED = "Tags removed: ";
const string EntryLists::FEEDBACK_MOVED_TO = "Moved to ";
const string EntryLists::FEEDBACK_SCHEDULED_LIST = "Scheduled list.";
const string EntryLists::FEEDBACK_FLOATING_LIST = "Floating list.";
const string EntryLists::FEEDBACK_CURRENT_ENTRY_NUMBER = "Current entry number: ";

const string EntryLists::FEEDBACK_DELETED = "This entry has been deleted:";
const string EntryLists::FEEDBACK_NO_ENTRIES_LEFT = "No entries left.";
const string EntryLists::FEEDBACK_OUT_OF_BOUND = "Entry number is out of bound.";

const string EntryLists::FEEDBACK_SUCCESSFULLY_STORED = " successfully stored at ";

const string EntryLists::FEEDBACK_WRONG_COMMAND = "Wrong command!";

const string EntryLists::STATUS_DONE = "done";
const string EntryLists::STATUS_UNDONE = "undone";

const string EntryLists::SPECIFY_STORAGE_PROMPT = "Please specify where you want to store your lists: ";
const string EntryLists::SCHEDULED_ENTRIES_PROMPT = "Scheduled entries";
const string EntryLists::FLOATING_ENTRIES_PROMPT = "Floating entries";

const string EntryLists::SCHEDULED_FILE_NAME = "\\FastAddSched.txt";
const string EntryLists::FLOATING_FILE_NAME = "\\FastAddFloat.txt";

const string EntryLists::BORDER = "- - - - - - - - - - - - - - - - -";

//@author A0115902N
EntryLists::EntryLists(){
}

//@author A0115656A
//Empties the _counter stack. The purpose of this function is such that additions of entries during loading
//at the beginning of running the program cannot be undone
void EntryLists::emptyCounter() {
	_counter.emptyUndoStack();
}

//@author A0116660L
void EntryLists::addEntry(Entry newEntry, int& latestEntryIndex) {
	if (newEntry.getDateStatus()) {
		_scheduledList.push_back(newEntry);
		sort(latestEntryIndex);
		_counter.counterAdd(true, latestEntryIndex);
	} else {
		_floatingList.push_back(newEntry);
		latestEntryIndex = _floatingList.size();
		_counter.counterAdd(false, latestEntryIndex);
	}
}

//@author A0115902N
void EntryLists::showAddFeedback(Entry newEntry, int latestEntryIndex) {
	string entryName = newEntry.getName();
	Date entryStartDate = newEntry.getStartDate();
	Date entryEndDate = newEntry.getEndDate();
	Time entryStartTime = newEntry.getStartTime();
	Time entryEndTime = newEntry.getEndTime();
	string entryLocation = newEntry.getLocation();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN |  FOREGROUND_INTENSITY));
	cout << FEEDBACK_ADDED_AT_NUMBER << latestEntryIndex << ". " << entryName;
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
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}


string EntryLists::getEntryDisplay(bool isScheduled, int index){
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

void EntryLists::removeEntry(bool isScheduled, unsigned int index, string& deleteFeedback){
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

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));	
		oss << FEEDBACK_DELETED << endl;
		oss << getEntryDisplay(isScheduled, index);
		deleteFeedback = oss.str();
		_counter.counterDelete(true, index, _scheduledList[index-1]);
		_scheduledList.erase(_scheduledList.begin() + index - 1);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
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
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		oss << FEEDBACK_DELETED << endl;
		oss << getEntryDisplay(isScheduled, index);
		deleteFeedback = oss.str();
		_counter.counterDelete(false, index, _floatingList[index-1]);
		_floatingList.erase(_floatingList.begin() + index - 1);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}

	//no more entry
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << FEEDBACK_NO_ENTRIES_LEFT << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
}

//@author A0115656A
//Edits an entry in either the scheduled or floating list and return a string of feedback
//editFeedback is initially empty. An EntryEdit object is created every time the function is called 
void EntryLists::editEntry(bool isScheduled, string userInput, string& editFeedback){
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
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		oss << FEEDBACK_EDITED << entryNumber << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	}
	int oldEntryNumber = entryNumber;

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
	Entry oldEntry = *iter;

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
			bool diffDates = diffStartEndDay || diffStartEndMonth || diffStartEndYear;
			if (diffDates) {
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
			bool diffDates = diffStartEndDay || diffStartEndMonth || diffStartEndYear;
			if (diffDates) {
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
	if (editComponent.getTimeEditStatus()) {
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
		if (inputStartMinute < 10) {
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
	if (newStatus != "") {
		if (newStatus == STATUS_DONE) {
		oss << FEEDBACK_STATUS << iter->getStatus();
		iter->changeStatus();
		oss << FEEDBACK_ARROW << iter->getStatus() << endl; 
		} else if (newStatus == STATUS_UNDONE) {
			oss << FEEDBACK_STATUS << iter->getStatus();
			iter->initialiseStatus();
			oss << FEEDBACK_ARROW << iter->getStatus() << endl;
		} else {
			oss << FEEDBACK_INVALID_STATUS << endl;
		}
	}

	//update added tags
	if (editComponent.getTagAddedStatus()) {
		oss << FEEDBACK_TAGS_ADDED;
		editComponent.addTag(*iter, oss);
	}

	//update removed tags
	if (editComponent.getTagRemovedStatus()) {
		oss << FEEDBACK_TAGS_REMOVED;
		editComponent.removeTag(*iter, oss);
	}
	
	//sort the list again if either date or time has been edited
	//if date editing is done on scheduled list AND date is not deleted, i.e. no shift from scheduled to floating
	bool dateEditedSort = editComponent.getDateEditStatus() && isScheduled && inputStartDay != 0;
	//if time editing is done on scheduled list. there is no need to check the time as time must have been edited properly
	bool timeEditedSort = editComponent.getTimeEditStatus() && isScheduled;
	if (dateEditedSort || timeEditedSort) {
		Entry newEntry = *iter;
		string dummy;
		removeEntry(isScheduled, entryNumber, dummy);
		_counter.removeCounter();
		addEntry(newEntry, entryNumber);
		_counter.removeCounter();
	}

	//move entry from floating to scheduled list and vice versa
	UndoActions::SuppCommand changeListCommand;
	bool isScheduledToFloating = isScheduled && editComponent.getDateEditStatus() && (inputStartDay == 0);
	bool isFloatingToScheduled = !isScheduled && editComponent.getDateEditStatus() && editComponent.getTimeEditStatus();
	if (isScheduledToFloating || isFloatingToScheduled) {
		moveScheduledFloating(isScheduled, entryNumber, *iter);
		oss << FEEDBACK_MOVED_TO;
		if (isScheduled) {
			changeListCommand = UndoActions::BackToScheduled;
			oss << FEEDBACK_FLOATING_LIST << endl;
		} else {
			changeListCommand = UndoActions::BackToFloating;
			oss << FEEDBACK_SCHEDULED_LIST << endl;
		}
	} else {
		changeListCommand = UndoActions::NoChange;
	}

	oss << FEEDBACK_CURRENT_ENTRY_NUMBER << entryNumber << endl;
	_counter.counterEdit(isScheduled, oldEntryNumber, changeListCommand, entryNumber, oldEntry);
	
	editFeedback = oss.str();
}

void EntryLists::moveScheduledFloating(bool isScheduled, int& entryNumber, Entry movedEntry) {
	string dummy;
	removeEntry(isScheduled, entryNumber, dummy);
	_counter.removeCounter();
	addEntry(movedEntry, entryNumber);
	_counter.removeCounter();
}

void EntryLists::undo() {
	_counter.execute(_scheduledList, _floatingList);
}

void EntryLists::exit(bool& running) {
	running = false;
}

//@author A0115902N
void EntryLists::sort(int& latestEntryIndex){
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

vector<Entry> EntryLists::getScheduledList(){
	vector<Entry> ScheduledEntries = _scheduledList;
	return ScheduledEntries;
}

vector<Entry> EntryLists::getFloatingList(){
	vector<Entry> FloatingEntries = _floatingList;
	return FloatingEntries;
}