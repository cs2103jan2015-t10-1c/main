#ifndef ENTRYLISTS_H
#define ENTRYLISTS_H

#include "EntryDate.h"
#include "EntryTime.h"
#include "Entry.h"
#include "UndoActions.h"
#include "EntryEdit.h"
#include "ClashInspector.h"
#include "DateTimeInspector.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>

class EntryLists{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	UndoActions _counter;

	HANDLE hConsole;

	//Feedback to the users
	static const string FEEDBACK_ADDED_AT_NUMBER;
	static const string FEEDBACK_FROM;
	static const string FEEDBACK_TO;
	static const string FEEDBACK_AT;

	static const string FEEDBACK_EDITED;
	static const string FEEDBACK_ARROW;
	static const string FEEDBACK_NAME;
	static const string FEEDBACK_DATE;
	static const string FEEDBACK_NO_DATE;
	static const string FEEDBACK_REMOVED;
	static const string FEEDBACK_TIME;
	static const string FEEDBACK_NO_TIME;
	static const string FEEDBACK_LOCATION;
	static const string FEEDBACK_STATUS;
	static const string FEEDBACK_INVALID_STATUS;
	static const string FEEDBACK_TAGS_ADDED;
	static const string FEEDBACK_TAGS_REMOVED;
	static const string FEEDBACK_MOVED_TO;
	static const string FEEDBACK_SCHEDULED_LIST;
	static const string FEEDBACK_FLOATING_LIST;
	static const string FEEDBACK_CURRENT_ENTRY_NUMBER;

	static const string FEEDBACK_DELETED;
	static const string FEEDBACK_NO_ENTRIES_LEFT;
	static const string FEEDBACK_OUT_OF_BOUND;
	
	static const string FEEDBACK_SUCCESSFULLY_STORED;

	static const string FEEDBACK_WRONG_COMMAND;

	static const string STATUS_DONE;
	static const string STATUS_UNDONE;

	//Prompts at exit
	static const string SPECIFY_STORAGE_PROMPT;
	static const string SCHEDULED_ENTRIES_PROMPT;
	static const string FLOATING_ENTRIES_PROMPT;

	//File names
	static const string SCHEDULED_FILE_NAME;
	static const string FLOATING_FILE_NAME;

	static const string BORDER;

public:
	//@author A0115902N
	EntryLists();
	//@author A0115656A
	void emptyCounter();
	//@author A0116660L
	void addEntry(Entry, int&);
	//@author A0115902N
	void showAddFeedback(Entry, int);
	string getEntryDisplay(bool, int);
	void removeEntry(bool, unsigned int, string&);
	//@author A0115656A
	void editEntry(bool, string, string&);
	void moveScheduledFloating(bool, int&, Entry);
	void undo();
	void exit(bool&);
	//@author A0115902N
	void sort(int&);
	
	//list accessors
	vector<Entry> getScheduledList();
	vector<Entry> getFloatingList();
};

#endif