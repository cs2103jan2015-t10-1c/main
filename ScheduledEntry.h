#ifndef SCHEDULEDENTRY_H
#define SCHEDULEDENTRY_H
#include "Date.h"
#include "Time.h"
#include "Entry.h"
#include "EntryEdit.h"
#include <vector>

class ScheduledEntry{
private:
	vector<Entry> _scheduledList;

	//Feedback to the users
	static const string FEEDBACK_ADDED;
	static const string FEEDBACK_FROM;
	static const string FEEDBACK_TO;
	static const string FEEDBACK_EDITED;
	static const string FEEDBACK_DELETED;

	//marker
	static const string NAME_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const string LOCATION_MARKER;

public:
	ScheduledEntry();
	void addEntry(Entry);
	void showAddFeedback(Entry);
	void display();
	void displayEntry(int);
	void removeEntry(int);
	void editEntry(string);
	void searchTag(string);
};

#endif