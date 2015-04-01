#ifndef SCHEDULEDENTRY_H
#define SCHEDULEDENTRY_H

#include "Date.h"
#include "Time.h"
#include "Entry.h"
#include "EntryEdit.h"
#include "ClashInspector.h"

#include <fstream>

class ScheduledEntry{
private:
	vector<Entry> _scheduledList;
	vector<Entry> _floatingList;

	//Feedback to the users
	static const string FEEDBACK_ADDED;
	static const string FEEDBACK_FROM;
	static const string FEEDBACK_TO;
	static const string FEEDBACK_AT;
	static const string FEEDBACK_EDITED;
	static const string FEEDBACK_DELETED;

	//markers
	static const string NAME_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;

public:
	ScheduledEntry();
	void addEntry(Entry);
	void showAddFeedback(Entry);
	void displayScheduled();
	void displayEntry(int);
	void removeEntry(int);
	void editEntry(string);
	void searchTag(string);
	void searchEntry(string);
	void exit(bool&);
	void sort();
};

#endif