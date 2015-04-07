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
	bool _printInThePast;
	bool _printToday;
	bool _printTomorrow;
	bool _printThisWeek;
	bool _printNextWeek;
	bool _printThisMonth;
	bool _printNextMonth;
	bool _viewingClashes;

	int _pageNumber;
	date _today;
	date _tomorrow;
	date _thisWeek;
	date _nextWeek;
	date _thisMonth;
	date _nextMonth;

	static const string TYPE_SCHEDULED;
	static const string TYPE_FLOATING;
	static const string TYPE_NEXT;
	static const string TYPE_PREV;
	static const string TYPE_CLASH;
	static const string TYPE_FIRSTPAGE;
	static const string TYPE_LASTPAGE;
	static const string TYPE_SPECIFICPAGE;
	static const string TYPE_PAST;

	static const int BLANKSPACE_COUNT;
	static const int ENTRY_PERPAGE;

	static const string BORDER;


public:
	DisplayEntries(vector<Entry>, vector<Entry>, int, bool);
	//Scheduled Entries
	void execute(string, bool&, int&, bool&);
	void displayScheduledEntryShort();
	void displayOneScheduledEntry(int);
	void displayScheduledEntries();
	//Floating Entries
	void displayFloatingEntries();
	void displayOneFloatingEntry(int index);
	void displayClashes();
	//Jump to first, last, and a specific page
	void displayFirstPage();
	void displayLastPage();
	void displaySpecifiedPage(int);
	void initialiseClashPaging(int&, vector<Entry>, int&, int&);

	/*void displayPastEntries();*/


	int returnPageNumber();

	void initialisePaging(int&, int&, int&, int&);
	void closingMessage(int, int, int);

};

#endif