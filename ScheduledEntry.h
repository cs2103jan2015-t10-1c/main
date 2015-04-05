#ifndef SCHEDULEDENTRY_H
#define SCHEDULEDENTRY_H

#include "Date.h"
#include "Time.h"
#include "Entry.h"
#include "UndoActions.h"
#include "EntryEdit.h"
#include "ClashInspector.h"

#include <fstream>

class ScheduledEntry{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;
	UndoActions _counter;

	//Feedback to the users
	static const string FEEDBACK_ADDED;
	static const string FEEDBACK_FROM;
	static const string FEEDBACK_TO;
	static const string FEEDBACK_AT;
	static const string FEEDBACK_EDITED;
	static const string FEEDBACK_DELETED;
	static const string FEEDBACK_INVALID_TYPE;

	//markers
	static const string NAME_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;

	static const string BORDER;

public:
	ScheduledEntry();
	void addEntry(Entry);
	void showAddFeedback(Entry);
	void displayEntry(int index);
	void removeEntry(int);
	void editEntry(string);
	void undo();
	void exit(bool&);
	void sort(int&);
	
	//list accessors
	vector<Entry> getScheduledList();
	vector<Entry> getFloatingList();
};

#endif