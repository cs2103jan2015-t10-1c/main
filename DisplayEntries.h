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
	//bool values related to display modes
	bool _viewingScheduledList;
	bool _viewingFloatingList;
	bool _viewingPastEntries;
	bool _viewingClashes;
	//bool values related to entry organisation
	bool _printInThePast;
	bool _printToday;
	bool _printTomorrow;
	bool _printThisWeek;
	bool _printNextWeek;
	bool _printThisMonth;
	bool _printNextMonth;
	//navigation attributes
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
	static const string MESSAGE_SCHEDULEDENTRY;
	static const string MESSAGE_FLOATINGENTRY;
	static const string MESSAGE_DISPLAYING;
	static const string MESSAGE_SCHEDULEDISEMPTY;
	static const string MESSAGE_ENTRIESNUMBER;
	static const string MESSAGE_FLOATINGISEMPTY;
	static const string MESSAGE_VIEWINGSCHEDULED;
	static const string MESSAGE_VIEWINGFLOATING;
	static const string MESSAGE_VIEWINGENTRYCLASHES;
	static const string MESSAGE_VIEWINGPAST;
	static const string MESSAGE_MISSINGPAGE;
	static const string MESSAGE_ENTRYCLASHES;
	static const string MESSAGE_ONFIRSTPAGE;
	static const string MESSAGE_PAGEDOESNOTEXIST;
	static const string MESSAGE_ARROWDISPLAYPREV;
	static const string MESSAGE_ARROWDISPLAYNEXT;
	static const string MESSAGE_BOTHARROWS;
	static const string MESSAGE_INVALID;
	static const string MESSAGE_PAGE;
	static const string MESSAGE_OUTOF;
	static const string MESSAGE_DISPLAYENTRIES;
	static const string MESSAGE_TO;
	static const string MESSAGE_REMAININGTODAY;
	static const string MESSAGE_NOENTRIESTODAY; 
	static const string MESSAGE_DISPLAYINGTODAY;
	static const string MESSAGE_ENTRIESTOMORROW;
	static const string MESSAGE_NOENTRIESTOMORROW;
	static const string MESSAGE_ENTRYFROM;


	HANDLE hConsole;

public:
	DisplayEntries(vector<Entry>, vector<Entry>);
	
	//@author A0115902N
	//Scheduled Entries
	void execute(string, int&, int&, bool&, bool&, bool&, bool&);
	//@author A0116660L
	void displayScheduledEntryShort();
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