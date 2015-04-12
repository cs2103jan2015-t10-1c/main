//@author A0115902N
#ifndef CLASHINSPECTOR_H
#define CLASHINSPECTOR_H
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "Entry.h"
class ClashInspector{
	
private:
	vector<Entry> _entryVector;
public:
	ClashInspector(vector<Entry>);
	void compareEntry(Entry, int, bool&, bool);
	void inspectEntries(Entry, Entry, int, bool&, bool);
};

#endif