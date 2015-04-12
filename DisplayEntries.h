#ifndef DISPLAYENTRIES_H
#define DISPLAYENTRIES_H

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "EntryLists.h"
#include "StringConvertor.h"
#include "ClashInspector.h"
#include <windows.h>

using namespace std;
using namespace boost::gregorian;

class DisplayEntries{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	string _userInput;
	bool _viewingScheduledList;
	bool _viewingFloatingList;
	bool _viewingPastEntries;
	bool _viewingClashes;

	bool _printInThePast;
	bool _printToday;
	bool _printTomorrow;
	bool _printThisWeek;
	bool _printNextWeek;
	bool _printThisMonth;
	bool _printNextMonth;

	int _pageNumber;
	int _lastPage;
	date _today;
	date _tomorrow;
	date _thisWeek;
	date _nextWeek;
	date _thisMonth;
	date _nextMonth;
	ptime _now;

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
	DisplayEntries(vector<Entry>, vector<Entry>);
	//Scheduled Entries
	void execute(string, int&, int&, bool&, bool&, bool&, bool&);
	void displayScheduledEntryShort();
	void displayOneScheduledEntry(int);
	//Floating Entries
	void displayFloatingEntries();
	void displayOneFloatingEntry(int index);
	void displayClashes();
	//Jump to first, last, and a specific page
	void displayFirstPage();
	void displayLastPage();
	void displayPrevPage();
	void displayNextPage();
	void displaySpecifiedPage(int);
	void displayPastEntries();
	void displayToday();
	void displayTomorrow();


	int returnPageNumber();

	void initialisePaging(vector<Entry>, int&, int&, int&, int&);
	void closingMessage(int, int, int);
	/*void displayTodayAndTomorrow(int&, int&, bool&, bool&, bool&, bool&);*/
	bool isInThePast(ptime);

};

#endif