#ifndef DISPLAYENTRIES_H
#define DISPLAYENTRIES_H

#include <string>
#include <windows.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ClashInspector.h"
#include "EntryLists.h"
#include "StringConvertor.h"


using namespace std;
using namespace boost::gregorian;

class DisplayEntries{
private:
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
	
	HANDLE hConsole;

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

public:
	DisplayEntries(vector<Entry>, vector<Entry>);
	
	//@author A0115902N
	//Scheduled Entries
	void execute(string, int&, int&, bool&, bool&, bool&, bool&);
	//@author A00116660L
	//Function is used to display entries from the scheduled list in short version
	//Short version of an entry only contains the entry name, date and time.
	void displayScheduledEntryShort();
	//Function is used to display one particular entry from the scheduled list in full version
	//Full version of an entry contains entry name, date and time, deadline, status, time left and tags etc.
	void displayOneScheduledEntry(int);
	
	//@author A0115902N
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
	bool isInThePast(ptime);


};

#endif