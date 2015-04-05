#ifndef DISPLAYENTRIES_H
#define DISPLAYENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ScheduledEntry.h"
#include "StringConvertor.h"
#include "ClashInspector.h"

using namespace std;
using namespace boost::gregorian;

class DisplayEntries{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	string _userInput;
	bool _viewingScheduledList;
	int _pageNumber;

	static const string TYPE_SCHEDULED;
	static const string TYPE_FLOATING;
	static const string TYPE_NEXT;
	static const string TYPE_PREV;
	static const string TYPE_CLASH;

	static const string BORDER;

public:
	DisplayEntries(vector<Entry>, vector<Entry>, int, bool);
	//Scheduled Entries
	void execute(string, bool&, int&);
	void displayScheduledEntryShort(int);
	void displayOneScheduledEntry(int index);
	void displayScheduledEntries();
	//Floating Entries
	void displayFloatingEntries();
	void displayOneFloatingEntry(int index);
	void displayClashes();
	int returnPageNumber();
};

#endif