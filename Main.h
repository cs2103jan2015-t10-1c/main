#ifndef MAIN_H
#define MAIN_H

#include <sstream>
#include "ScheduledEntry.h"
#include "EntryAdd.h"
#include "TextUI.h"
#include "EntryEdit.h"
#include "DateTimeInitialiser.h"
#include "DateTimeInspector.h"
#include "DisplayEntries.h"
#include "SearchEntries.h"
#include "UndoActions.h"
#include <assert.h>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Main{
private:
	static const string COMMAND_PROMPT;
	static const string COMMAND_ADD;
	static const string COMMAND_EDIT;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_DELETE;
	static const string COMMAND_SEARCH;
	static const string COMMAND_HELP;
	static const string COMMAND_UNDO;
	static const string COMMAND_EXIT;

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
	bool _atScheduledEntries;
	int _pageNumber;
	int _numberOfEntriesFound;
	int _lastIteration;
	ScheduledEntry _newList;
	//TextUI
	TextUI _commandInterface;
	DateTimeInitialiser _initialiser;

public:
	Main();
	void welcomeMessage();
	void loadScheduledEntries();
	void loadFloatingEntries();
	void resetStringValues();
	void resetIntegerValues();
	void operateFastAdd();
	
	//FastAdd CRUD
	void executeAddFunction(string);
	void executeEditFunction(string);
	void executeDisplayFunction(string);
	void executeDeleteFunction(string);
	//FastAdd additional features
	void executeSearchFunction(string);
	void executeHelpFunction();
	void executeUndoFunction();
	void executeExitFunction();

	void initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear);
	void initialiseTime(Time& inputTime, int inputHour, int inputMinute);
	void convertDateTime(EntryAdd&, string, int&, int&, int&,
					 string, int&, int&,
					 string, int&, int&, int&,
					 string, int&, int&);
	void initialiseEntry(Entry& newEntry, string entryName, Date startDate, 
					Date endDate, Time startTime, Time endTime, string entryLocation,
					vector<string>& tags);
	void initialiseDateTime(Date&, int, int, int, Time&, int, int,
						Date&, int, int, int, Time& , int, int);
};

#endif
