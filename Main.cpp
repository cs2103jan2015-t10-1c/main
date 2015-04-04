#include "Main.h"

const string Main::COMMAND_PROMPT = "command: ";
const string Main::COMMAND_ADD = "add";
const string Main::COMMAND_EDIT = "edit";
const string Main::COMMAND_DISPLAY = "display";
const string Main::COMMAND_DELETE = "delete";
const string Main::COMMAND_EXIT = "exit";
const string Main::COMMAND_SEARCH = "search";
const string Main::COMMAND_HELP = "help";

Main::Main(){
	_userInput = "";
	_entryName = "";
	_stringStartDate = "";
	_stringStartTime = "";
	_stringEndDate = "";
	_stringEndTime = "";
	_entryLocation = "";
	running = true;
	_atScheduledEntries = true;
	_pageNumber = 1;
}

void Main::welcomeMessage(){
	_commandInterface.displayWelcomeMessage();
	_commandInterface.displayCurrentDateTime();
}
void Main::loadScheduledEntries(){
	cout << "Loading existing entries..." << endl << endl;
	//load existing scheduled entries
	ifstream readSched("FastAddSched.txt");
	while (getline(readSched, _userInput)){
		Entry newEntry;
		string stringTags;
		vector<string> tags;
		if (_userInput != ""){
			_entryName = _userInput;
			getline(readSched, _stringStartDate);
			getline(readSched, _stringStartTime);
			getline(readSched, _stringEndDate);
			getline(readSched, _stringEndTime);
			getline(readSched, _entryLocation);
			getline(readSched, stringTags);

		//set integer values to 0
		resetIntegerValues();

		EntryAdd parse;
		convertDateTime(parse, _stringStartDate, _intStartDay, _intStartMonth, _intStartYear, _stringStartTime, _intStartHour, _intStartMinute,	
				_stringEndDate, _intEndDay, _intEndMonth, _intEndYear, _stringEndTime, _intEndHour, _intEndMinute);
		parse.extractTag(stringTags, tags);

		//initialise start and end dates, start and end times
			Date startDate;
			Date endDate;
			Time startTime;
			Time endTime;
			initialiseDateTime(startDate, _intStartDay, _intStartMonth, _intStartYear, startTime, _intStartHour, _intStartMinute,
				endDate, _intEndDay, _intEndMonth, _intEndYear, endTime, _intEndHour, _intEndMinute);
				//initialise entry
			initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, tags);
			_newList.addEntry(newEntry);
		}
	}
	readSched.close();
	//reset values
	resetStringValues();
	resetIntegerValues();
}

void Main::loadFloatingEntries(){
	ifstream readFloat("FastAddFloat.txt");
	while (getline(readFloat, _userInput)){
		Entry newEntry;
		string stringTags;
		vector<string> tags;
		if (_userInput != ""){
			_entryName = _userInput;
			getline(readFloat, _entryLocation);
			getline(readFloat, stringTags);

			EntryAdd parse;
			parse.extractTag(stringTags, tags);

			//initialise start and end dates, start and end times
			Date startDate;
			Date endDate;
			Time startTime;
			Time endTime;
			initialiseDateTime(startDate, 0, 0, 0, startTime, 0, 0, endDate, 0, 0, 0, endTime, 0, 0);
						
			//initialise entry
			initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, tags);
			_newList.addEntry(newEntry);
		}
	}
	readFloat.close();
	resetIntegerValues();
	resetStringValues();
	cout << endl << "Loading done..." << endl << endl;
}

void Main::operateFastAdd(){
	while(running){
		cout << "_____________________________________________" << endl << endl
			<< COMMAND_PROMPT;
		getline(cin, _userInput);
		cout << "_____________________________________________" << endl << endl;

		_command = _commandInterface.findCommand(_userInput);
		_userInput = _commandInterface.removeCommand(_userInput);

		//add command
		if(_command == COMMAND_ADD){
			executeAddFunction(_userInput);
		}
		else if(_command == COMMAND_EDIT){
			executeEditFunction(_userInput);
		}
		else if(_command == COMMAND_SEARCH){
			executeSearchFunction(_userInput);
		}
		else if(_command == COMMAND_DISPLAY){
			executeDisplayFunction(_userInput);
		}
		else if(_command == COMMAND_DELETE){
			executeDeleteFunction(_userInput);
		}
		else if(_command == COMMAND_HELP){
			executeHelpFunction();
		}
		else if(_command == COMMAND_EXIT){
			executeExitFunction();
		}
		else{
			_commandInterface.displayErrorFeedback();
		}
		cout << endl;
	}
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
	Date startDate;	
	Date endDate;
	Time startTime;
	Time endTime;

	//initialise start and end dates
	DateTimeInspector DateInspector;
	if(!DateInspector.dateIsValid(_intStartDay, _intStartMonth, _intStartYear)){
		cout << "Start Date is invalid!" << endl << endl;
		dateIsOkay = false;
	}
	else{
		initialiseDate(startDate, _intStartDay, _intStartMonth, _intStartYear);
	}
	if(!DateInspector.dateIsValid(_intEndDay, _intEndMonth, _intEndYear)){
		cout << "End Date is invalid!" << endl << endl;
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
			cout << "Start Time is invalid!" << endl << endl;
			timeIsOkay = false;
		}
		else{
			initialiseTime(startTime, _intStartHour, _intStartMinute);
		}
		if(!DateInspector.timeIsValid(_intEndHour, _intEndMinute)){
			cout << "End Time is invalid!" << endl << endl;
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
		initialiseEntry(newEntry, _entryName, startDate, endDate, startTime, endTime, _entryLocation, tags);
		//add new entry to the list
		_newList.addEntry(newEntry);
		_newList.showAddFeedback(newEntry);
	}
}

void Main::executeEditFunction(string userInput){
	_newList.editEntry(userInput);
}

void Main::executeSearchFunction(string userInput){
	SearchEntries search(_newList.getScheduledList(), _newList.getFloatingList());
	search.execute(userInput);
}

void Main::executeDisplayFunction(string userInput){
	DisplayEntries display(_newList.getScheduledList(), _newList.getFloatingList(), _pageNumber, _atScheduledEntries);
	display.execute(userInput, _atScheduledEntries, _pageNumber);
}

void Main::executeDeleteFunction(string userInput){
	int indexNumber;
	StringConvertor convertToNumber;
	convertToNumber.convertStringToNumber(userInput, indexNumber);
	_newList.removeEntry(indexNumber);
}

void Main::executeHelpFunction(){
	_commandInterface.displayHelp();
}

void Main::executeExitFunction(){
	_newList.exit(running);
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

void Main::initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation, vector<string>& tags){
	newEntry.insertName(entryName);
	newEntry.insertStartDate(startDate);
	newEntry.insertEndDate(endDate);
	newEntry.insertStartTime(startTime);
	newEntry.insertEndTime(endTime);
	newEntry.insertLocation(entryLocation);
	newEntry.addTags(tags);
}

void Main::initialiseDateTime(Date& startDate, int intStartDay, int intStartMonth, int intStartYear, Time& startTime, int intStartHour, int intStartMinute,
						Date& endDate, int intEndDay, int intEndMonth, int intEndYear, Time& endTime, int intEndHour, int intEndMinute){
	initialiseDate(startDate, intStartDay, intStartMonth, intStartYear);
	initialiseDate(endDate, intEndDay, intEndMonth, intEndYear);
	initialiseTime(startTime, intStartHour, intStartMinute);
	initialiseTime(endTime, intEndHour, intEndMinute);
}