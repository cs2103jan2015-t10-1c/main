#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ScheduledEntry.h"

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

public:
	DisplayEntries(vector<Entry>, vector<Entry>);
	//Scheduled Entries
	void execute(string);
	void displayScheduledEntryShort();
	void displayOneScheduledEntry(int index);
	void displayScheduledEntries();
	//Floating Entries
	void displayFloatingEntries();
	void displayOneFloatingEntry(int index);
};

#endif