//@author A0115902N
#ifndef CLASHINSPECTOR_H
#define CLASHINSPECTOR_H
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "Entry.h"
#include <windows.h>
class ClashInspector{
	
private:
	vector<Entry> _entryVector;
	static const string CLASH_MESSAGE;
	static const string COLON;
	static const string EXCLAMATION_MARK;
	HANDLE hConsole;

public:
	ClashInspector(vector<Entry>);
	void compareEntry(Entry, int, bool&, bool);
	void inspectEntries(Entry, Entry, int, bool&, bool);
};

#endif