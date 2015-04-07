#ifndef SEARCHENTRIES_H
#define SEARCHENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ScheduledEntry.h"
#include "DateTimeInitialiser.h"

using namespace std;
using namespace boost::gregorian;

class SearchEntries{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	static const string NAME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const int ENTRY_PERPAGE;

	static const string ALL_MARKER;
	static const string NEXT_MARKER;
	static const string PREV_MARKER;

	static const string BORDER;

	StringConvertor _datetimeParser;
	int _pageNumber;
public:

	SearchEntries(vector<Entry>, vector<Entry>);
	void execute(string input, int&, string&);
	void searchTag(string);
	void searchName(string);
	void searchLocation(string);
	void searchStatus(string);
	void searchDate(string);
	void searchTime(string);
	void searchAll(string);
	void initialisePaging(int& numberOfPages, vector<Entry> searchResult, int& firstEntry, int& lastEntry);
	void closingMessage(int, int, int);

};
#endif


