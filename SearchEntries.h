#ifndef SEARCHENTRIES_H
#define SEARCHENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ScheduledEntry.h"

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

	static const string ALL_MARKER;
	StringConvertor _datetimeParser;
public:

	SearchEntries(vector<Entry>, vector<Entry>);
	void execute(string input);
	void searchTag(string);
	void searchName(string);
	void searchLocation(string);
	void searchStatus(string);
	void searchDate(string);
	void searchTime(string);
	void searchAll(string);

};
#endif


