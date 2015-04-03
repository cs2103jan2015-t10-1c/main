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

public:

	SearchEntries(vector<Entry>, vector<Entry>);
	void execute(string input);
	void searchTag(string);
	void searchName(string);
	void searchLocation(string);
	void searchStatus(string);


};
#endif


