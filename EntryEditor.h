#ifndef ENTRYEDITOR_H
#define ENTRYEDITOR_H
#include "SeparateEntryComponents.h"

#include <iostream>
#include <string>

using namespace std;

class EntryEditor{
private:
	int _taskNumber;
	string _parameter;//-l -d -t
	string _newInformation;//date or time or location or name
public:	
	EntryEditor ();
	int getEntryNumber (string);
	string getMarker(string);
	int convertToNumber(string);
	string getName ();
	void getTime (int&, int&, int&, int&);
	void getDate (int&, int&, int&);
	string getLocation ();
};

#endif