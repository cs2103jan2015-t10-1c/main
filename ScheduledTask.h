#ifndef SCHEDULEDTASK_H
#define SCHEDULEDTASK_H
#include "Date.h"
#include "Time.h"
#include "Entry.h"
#include <vector>

class ScheduledTask{
private:
	vector<Entry> _scheduledList;
public:
	ScheduledTask();
	void addEntry(Entry);
	void display();
	void displayEntry(int);
	void removeTask(int);
};

#endif