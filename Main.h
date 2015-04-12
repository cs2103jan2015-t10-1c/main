#ifndef MAIN_H
#define MAIN_H

#include <sstream>
#include <assert.h>
#include <windows.h>
#include "EntryLists.h"
#include "EntryAdd.h"
#include "TextUI.h"
#include "EntryEdit.h"
#include "DateTimeInitialiser.h"
#include "DateTimeInspector.h"
#include "DisplayEntries.h"
#include "SearchEntries.h"
#include "UndoActions.h"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Main {
private:
	static const string COMMAND_PROMPT;
	static const string COMMAND_ADD;
	static const string COMMAND_EDIT;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_DELETE;
	static const string COMMAND_SEARCH;
	static const string COMMAND_HELP;
	static const string COMMAND_UNDO;
	static const string COMMAND_SAVE;
	static const string COMMAND_SAVE_AT;
	static const string COMMAND_EXIT;
	static const string COMMAND_RESIZE;
	static const string COMMAND_BORDER;

	static const string FEEDBACK_SUCCESSFULLY_STORED;

	static const string SPECIFY_STORAGE_PROMPT;
	static const string SCHEDULED_ENTRIES_PROMPT;
	static const string FLOATING_ENTRIES_PROMPT;

	//File names
	static const string PATH_FILE_NAME;
	static const string SCHEDULED_FILE_NAME;
	static const string FLOATING_FILE_NAME;

	string _userInput;
	string _entryName;
	string _stringStartDate;
	string _stringStartTime;
	string _stringEndDate;
	string _stringEndTime;
	string _entryLocation;
	string _command;
	string _previousSearchInput;

	int _intStartDay; int _intStartMonth; int _intStartYear;
	int _intEndDay; int _intEndMonth; int _intEndYear;
	int _intStartHour; int _intStartMinute;
	int _intEndHour; int _intEndMinute;

	bool _running;

	bool _viewingScheduledList;
	bool _viewingFloatingList;
	bool _viewingPastEntries;
	bool _viewingClashes;
	int _pageNumber;
	int _searchScheduledPageNumber;
	int _searchFloatingPageNumber;
	int _lastPage;

	//loading
	bool _loadingEntries;
	string _scheduledPath;
	string _floatingPath;

	EntryLists _newList;

	TextUI _commandInterface;
	DateTimeInitialiser _initialiser;

public:
	//@author A0100750Y
	Main();
	void welcomeMessage();
	//@author A0115656A
	void readPath();
	void loadScheduledEntries();
	void loadFloatingEntries();
	void resetStringValues();
	void resetIntegerValues();
	//@author A0100750Y
	void operateFastAdd();
	
	//FastAdd CRUD
	//@author A0116660L
	//Function used to activate the whole chain of functions to add a new entry
	//The string received is from the user without the command word
	//The Command word has been removed through the TextUI
	void executeAddFunction(string);
	//@author A0115656A
	void executeEditFunction(string);
	//@author A0115902N
	void executeDisplayFunction(string);
	//@author A0116660L
	void executeDeleteFunction(string);
	//FastAdd additional features
	//@author A0116660L
	//Function used to activate the whole chain of functions to search for a new entry
	//The string received is from the user without the command word
	//The Command word has been removed through the TextUI
	void executeSearchFunction(string);
	//@author A0100750Y
	void executeHelpFunction();
	//@author A0115656A
	void executeUndoFunction();
	void executeSaveFunction();
	void executeSaveAtFunction();
	void executeExitFunction();
	//@author A0116660L
	//Function used to resize the command prompt window size
	//Two options available small and large
	void executeResizeFunction();

	//@author A0115902N
	void initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear);
	void initialiseTime(Time& inputTime, int inputHour, int inputMinute);
	void convertDateTime(EntryAdd&, string, int&, int&, int&,
						 string, int&, int&,
						 string, int&, int&, int&,
						 string, int&, int&);
	void initialiseEntry(Entry&, string, Date, 
						Date, Time, Time, string,
						string, vector<string>&);
	void initialiseDateTime(Date&, int, int, int, Time&, int, int,
							Date&, int, int, int, Time& , int, int);

	HANDLE hConsole;
};

#endif
