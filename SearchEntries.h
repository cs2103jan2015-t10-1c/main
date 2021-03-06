#ifndef SEARCHENTRIES_H
#define SEARCHENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "EntryLists.h"
#include "DateTimeInitialiser.h"
#include "DateTimeInspector.h"
#include "StringConvertor.h"

using namespace std;
using namespace boost::gregorian;

class SearchEntries{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	vector<Entry> _scheduledSearchResult;
	vector<Entry> _floatingSearchResult;
	int _numberOfPagesScheduledResult;
	int _numberOfPagesFloatingResult;
	int _firstScheduledEntry;
	int _lastScheduledEntry;
	int _firstFloatingEntry;
	int _lastFloatingEntry;
	static const string NAME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const int ENTRY_PERPAGE;
	static const string ALL_MARKER;
	static const string NEXT_MARKER;
	static const string PREV_MARKER;
	static const string DAY_MARKER;
	static const string BORDER;
	static const string DAYSOFWEEK[7];
	static const string SYSTEMDAYSOFWEEK[7];
	static const string MON, TUE, WED, THU, FRI, SAT, SUN;
	static const string SYSTEMMON, SYSTEMTUE, SYSTEMWED, SYSTEMTHU, SYSTEMFRI, SYSTEMSAT, SYSTEMSUN;
	static const string SLOT_MARKER;
	StringConvertor _datetimeParser;
	int _scheduledPageNumber;
	int _floatingPageNumber;
	HANDLE hConsole; 

public:

	//@author A0116660L
	//Contructor of SearchEntries which takes in two vectors containing Scheduled and Floating lists
	//The Search will be conducted on both list simultaneously
	SearchEntries(vector<Entry>, vector<Entry>);
	//The function to activate the whole chain of commands for search
	//Used to distinguish different types of search such as search by name, location, date or time etc.
	void execute(string input, int&, int&, string&);
	//Function dedicated to search for the tag only
	void searchTag(string);
	//Function dedicated to search for the name only
	void searchName(string);
	//Function dedicated to search for the location only
	void searchLocation(string);
	//Function dedicated to search for the status only
	void searchStatus(string);
	//@author A0115902N
	void searchDate(string);
	void searchTime(string);
	void searchDay(string);
	//@author A0116660L
	//Function dedicated to search for anything that contains the keyword given by the user
	void searchAll(string);
	//@author A0115902N
	void searchSlot(string);
	void initialiseScheduledPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry);
	void initialiseFloatingPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry);
	void closingScheduledMessage(int, int, int);
	void closingFloatingMessage(int, int, int);
	void displaySearchResults(vector<Entry>, int, int);
	void initialiseSearchPagingAttributes();
	void loadScheduledSearchResult();
	void loadFloatingSearchResult();

	int calculateDifferenceBetweenTwoWeekDays(string, string);

};
#endif


