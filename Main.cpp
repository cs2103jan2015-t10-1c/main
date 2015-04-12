#include "Main.h"

using namespace std;

const string Main::COMMAND_PROMPT = "command: ";
const string Main::COMMAND_ADD = "add";
const string Main::COMMAND_EDIT = "edit";
const string Main::COMMAND_DISPLAY = "display";
const string Main::COMMAND_DELETE = "delete";
const string Main::COMMAND_SEARCH = "search";
const string Main::COMMAND_HELP = "help";
const string Main::COMMAND_UNDO = "undo";
const string Main::COMMAND_EXIT = "exit";
const string Main::COMMAND_RESIZE = "resize";
const string Main::COMMAND_BORDER = "_________________________________________________________";

Main::Main(){
	_userInput = "";
	_entryName = "";
	_stringStartDate = "";
	_stringStartTime = "";
	_stringEndDate = "";
	_stringEndTime = "";
	_entryLocation = "";
	_running = true;
	_viewingScheduledList = true;
	_viewingFloatingList = false;
	_viewingPastEntries = false;
	_viewingClashes = false;
	_pageNumber = 1;
	_searchScheduledPageNumber = 1;
	_searchFloatingPageNumber = 1;
	_previousSearchInput = "";
}

void Main::welcomeMessage(){
	_commandInterface.displayWelcomeMessage();
}

void Main::readPath(){
	ifstream readPath("Path.txt");
	readPath >> _scheduledPath;
	readPath >> _floatingPath;
	readPath.close();
}

void Main::loadScheduledEntries(){
	_loadingEntries = true;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "Loading existing entries..." << endl;
	SetConsoleTextAttribute(hConsole, 15);
	//load existing scheduled entries
	ifstream readSched(_scheduledPath);
	while (getline(readSched, _userInput)){
		Entry newEntry;
		string entryStatus;
		string stringTags;
		vector<string> tags;
		if (_userInput != ""){
			_entryName = _userInput;
			getline(readSched, _stringStartDate);
			getline(readSched, _stringStartTime);
			getline(readSched, _stringEndDate);
			getline(readSched, _stringEndTime);
			getline(readSched, _entryLocation);
			getline(readSched, entryStatus);
			getline(readSched, stringTags);

		//set integer values to 0
		resetIntegerValues();

		EntryAdd parse;
		convertDateTime(parse, _stringStartDate, _intStartDay, _intStartMonth, _intStartYear, _stringStartTime, _intStartHour, _intStartMinute,	
				_stringEndDate, _intEndDay, _intEndMonth, _intEndYear, _stringEndTime, _intEndHour, _intEndMinute);
		parse.extractTag(stringTags, tags);

		//initialise start and end dates, start and end times
			Date startDate(_loadingEntries);
			Date endDate(_loadingEntries);
			Time startTime;
			Time endTime;
			initialiseDateTime(startDate, _intStartDay, _intStartMonth, _intStartYear, startTime, _intStartHour, _intStartMinute,
				endDate, _intEndDay, _intEndMonth, _intEndYear, endTime, _intEndHour, _intEndMinute);
				//initialise entry
			initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, entryStatus, tags);
			int dummy;
			_newList.addEntry(newEntry, dummy);
		}
	}
	readSched.close();
	//reset values
	resetStringValues();
	resetIntegerValues();

	//empty the counter stack
	_newList.emptyCounter();
}

void Main::loadFloatingEntries(){
	_loadingEntries = true;
	ifstream readFloat(_floatingPath);
	while (getline(readFloat, _userInput)){
		Entry newEntry;
		string entryStatus;
		string stringTags;
		vector<string> tags;
		if (_userInput != ""){
			_entryName = _userInput;
			getline(readFloat, _entryLocation);
			getline(readFloat, entryStatus);
			getline(readFloat, stringTags);

			EntryAdd parse;
			parse.extractTag(stringTags, tags);

			//initialise start and end dates, start and end times
			Date startDate(_loadingEntries);
			Date endDate(_loadingEntries);
			Time startTime;
			Time endTime;
			initialiseDateTime(startDate, 0, 0, 0, startTime, 0, 0, endDate, 0, 0, 0, endTime, 0, 0);
						
			//initialise entry
			initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, entryStatus, tags);
			int dummy;
			_newList.addEntry(newEntry, dummy);
		}
	}
	readFloat.close();
	resetIntegerValues();
	resetStringValues();

	//empty the counter stack
	_newList.emptyCounter();
	cout << endl;
	DisplayEntries loadEntries(_newList.getScheduledList(), _newList.getFloatingList());
	cout << COMMAND_BORDER << endl << endl;
	loadEntries.displayToday(); 
	cout << COMMAND_BORDER << endl << endl;
	loadEntries.displayTomorrow();
}

void Main::operateFastAdd(){
	_loadingEntries = false;
	while(_running){
		cout << COMMAND_BORDER << endl << endl
			<< COMMAND_PROMPT;
		getline(cin, _userInput);
		cout << COMMAND_BORDER << endl << endl;

		_command = _commandInterface.findCommand(_userInput);
		_userInput = _commandInterface.removeCommand(_userInput);

		//add command
		if(_command == COMMAND_ADD){
			executeAddFunction(_userInput);
		}
		
		//edit command
		else if(_command == COMMAND_EDIT){
			executeEditFunction(_userInput);
		}

		//display scheduled command
		//display allows the user to toggle between 'scheduled' and 'floating' mode
		else if(_command == COMMAND_DISPLAY){
			executeDisplayFunction(_userInput);
		}

		//delete command
		else if(_command == COMMAND_DELETE){
			executeDeleteFunction(_userInput);
		}

		//search command
		else if(_command == COMMAND_SEARCH){
			executeSearchFunction(_userInput);
		}

		//help command
		else if(_command == COMMAND_HELP){
			executeHelpFunction();
		}

		//undo command
		else if (_command == COMMAND_UNDO){
			executeUndoFunction();
		}

		//exit command
		else if(_command == COMMAND_EXIT){
			executeExitFunction();
		}

		else if(_command == COMMAND_RESIZE){
			executeResizeFunction();
		}
		
		else{
			_commandInterface.displayErrorFeedback();
		}
		cout << endl;
	}
}

void Main::executeResizeFunction(){
	_commandInterface.displayResizeOptions();
}

void Main::executeAddFunction(string userInput){
	resetIntegerValues();
	resetStringValues();
	EntryAdd parse;
	vector<string> tags;
	bool dateIsOkay = true;
	bool timeIsOkay = true;

	parse.dissectCommand(userInput, _entryName, _stringStartDate, _stringStartTime, _stringEndDate, _stringEndTime, _entryLocation, tags);

	if (_stringStartDate != ""){
			convertDateTime(parse, _stringStartDate, _intStartDay, _intStartMonth, 
			_intStartYear, _stringStartTime, _intStartHour, _intStartMinute,
			_stringEndDate, _intEndDay, _intEndMonth, _intEndYear,_stringEndTime, 
			_intEndHour, _intEndMinute);
	}
			
	//initialise start and end dates, start and end times
	Date startDate(_loadingEntries);	
	Date endDate(_loadingEntries);
	Time startTime;
	Time endTime;

	//initialise start and end dates
	DateTimeInspector DateInspector;
	if(!DateInspector.dateIsValid(_intStartDay, _intStartMonth, _intStartYear)){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Start Date is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		dateIsOkay = false;
	}
	else{
		initialiseDate(startDate, _intStartDay, _intStartMonth, _intStartYear);
	}
	if(!DateInspector.dateIsValid(_intEndDay, _intEndMonth, _intEndYear)){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "End Date is invalid!" << endl << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		dateIsOkay = false;
	}
	else{
		initialiseDate(endDate, _intEndDay, _intEndMonth, _intEndYear);
	}
	//only when date is ok
	if(dateIsOkay){
	//initialise start and end times
		DateTimeInspector TimeInspector;
		if(!TimeInspector.timeIsValid(_intStartHour, _intStartMinute)){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "Start Time is invalid!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			timeIsOkay = false;
		}
		else{
			initialiseTime(startTime, _intStartHour, _intStartMinute);
		}
		if(!DateInspector.timeIsValid(_intEndHour, _intEndMinute)){
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
			cout << "End Time is invalid!" << endl << endl;
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
			timeIsOkay = false;
		}
		else{
			initialiseTime(endTime, _intEndHour, _intEndMinute);
		}
	}
	//only when time is okay
	if(timeIsOkay){
		//initialise entry
		Entry newEntry;
		initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, "undone", tags);
		if(newEntry.getStartDate().getDate() > newEntry.getEndDate().getDate()){
			cout << "Warning: start date occurs after end date. repeat input" << endl << endl;
			return;
		} else if(newEntry.getStartTime().getTime() > newEntry.getEndTime().getTime()){
			cout << "Warning: start time occurs after end time. repeat input" << endl << endl;
			return;
		}
		int newEntryIndex;
		_newList.addEntry(newEntry, newEntryIndex);
		_newList.showAddFeedback(newEntry, newEntryIndex);
	}
}

void Main::executeEditFunction(string userInput){
	string editFeedback;
	_newList.editEntry(_viewingScheduledList, userInput, editFeedback);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << editFeedback;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void Main::executeSearchFunction(string userInput){
	SearchEntries search(_newList.getScheduledList(), _newList.getFloatingList());
	search.execute(userInput, _searchScheduledPageNumber, _searchFloatingPageNumber,_previousSearchInput);
}

void Main::executeDisplayFunction(string userInput){
	DisplayEntries display(_newList.getScheduledList(), _newList.getFloatingList());
	display.execute(userInput, _pageNumber, _lastPage, _viewingScheduledList, _viewingFloatingList, _viewingPastEntries, _viewingClashes);
}

void Main::executeDeleteFunction(string userInput){
	int indexNumber;
	StringConvertor convertToNumber;
	convertToNumber.convertStringToNumber(userInput, indexNumber);
	string deleteFeedback;
	_newList.removeEntry(_viewingScheduledList, indexNumber, deleteFeedback);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << deleteFeedback;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void Main::executeHelpFunction(){
	_commandInterface.displayHelp();
}

void Main::executeUndoFunction(){
	_newList.undo();
}

void Main::executeExitFunction(){
	_newList.exit(_running);
}

void Main::resetStringValues(){
	_userInput = "";
	_entryName = "";
	_stringStartDate = "";
	_stringStartTime = "";
	_stringEndDate = "";
	_stringEndTime = "";
	_entryLocation = "";
	_command = "";
}

void Main::resetIntegerValues(){
	_intStartDay = 0; _intStartMonth = 0; _intStartYear = 0;
	_intEndDay = 0; _intEndMonth = 0; _intEndYear = 0;
	_intStartHour = 0; _intStartMinute = 0;
	_intEndHour = 0; _intEndMinute = 0;
}

void Main::initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear){
	int year = inputYear;
	int month = inputMonth;
	int day = inputDay;
	
	inputDate.insertDay(inputDay);
	inputDate.insertMonth(inputMonth);
	inputDate.insertYear(inputYear);
}

void Main::initialiseTime(Time& inputTime, int inputHour, int inputMinute){
	inputTime.insertHour(inputHour);
	inputTime.insertMinute(inputMinute);
}

void Main::convertDateTime(EntryAdd& parse, string stringStartDate, int& intStartDay, int& intStartMonth, int& intStartYear,
					 string stringStartTime, int& intStartHour, int& intStartMinute,
					 string stringEndDate, int& intEndDay, int& intEndMonth, int& intEndYear,
					 string stringEndTime, int& intEndHour, int& intEndMinute){
	parse.convertDate(stringStartDate, intStartDay, intStartMonth, intStartYear);
	parse.convertTime(stringStartTime, intStartHour, intStartMinute);
	parse.convertDate(stringEndDate, intEndDay, intEndMonth, intEndYear);
	parse.convertTime(stringEndTime, intEndHour, intEndMinute);
}

void Main::initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime,
						   string entryLocation, string entryStatus, vector<string>& tags){
	newEntry.insertName(entryName);
	newEntry.insertStartDate(startDate);
	newEntry.insertEndDate(endDate);
	newEntry.insertStartTime(startTime);
	newEntry.insertEndTime(endTime);
	newEntry.insertLocation(entryLocation);
	if (entryStatus == "done") {
		newEntry.changeStatus();
	} else if (entryStatus == "undone") {
		newEntry.initialiseStatus();
	}
	newEntry.insertTags(tags);
}

void Main::initialiseDateTime(Date& startDate, int intStartDay, int intStartMonth, int intStartYear, Time& startTime, int intStartHour, int intStartMinute,
						Date& endDate, int intEndDay, int intEndMonth, int intEndYear, Time& endTime, int intEndHour, int intEndMinute){
	initialiseDate(startDate, intStartDay, intStartMonth, intStartYear);
	initialiseDate(endDate, intEndDay, intEndMonth, intEndYear);
	initialiseTime(startTime, intStartHour, intStartMinute);
	initialiseTime(endTime, intEndHour, intEndMinute);
}