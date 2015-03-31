#ifndef CLASHINSPECTOR_H
#define CLASHINSPECTOR_H
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "Entry.h"
class ClashInspector{
	
private:
	vector<Entry> _scheduledEntryList;
public:
	ClashInspector(vector<Entry>);
	void compareEntry(Entry, int);
	void inspectEntries(Entry, Entry, bool&, int);
};

#endif