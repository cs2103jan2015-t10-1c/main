#ifndef SEARCHENTRIES_H
#define SEARCHENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "EntryLists.h"
#include "DateTimeInitialiser.h"
#include "DateTimeInspector.h"
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

	StringConvertor _datetimeParser;
	int _scheduledPageNumber;
	int _floatingPageNumber;
	HANDLE hConsole; 

public:

	SearchEntries(vector<Entry>, vector<Entry>);
	void execute(string input, int&, int&, string&);
	void searchTag(string);
	void searchName(string);
	void searchLocation(string);
	void searchStatus(string);
	void searchDate(string);
	void searchTime(string);
	void searchAll(string);
	void initialiseScheduledPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry);
	void initialiseFloatingPaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry);
	void closingScheduledMessage(int, int, int);
	void closingFloatingMessage(int, int, int);
	void displaySearchResults(vector<Entry>, int, int);
	void initialiseSearchPagingAttributes();
	void loadScheduledSearchResult();
	void loadFloatingSearchResult();

};
#endif


