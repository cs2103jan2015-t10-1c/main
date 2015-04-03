#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H
#include "StringConvertor.h"

#include <iostream>
#include <string>

using namespace std;

class EntryEdit{
private:
	int _entryNumber;
	//-n, -d, -t, -l
	string _marker;
	//new edited information
	string _newInformation;

public:	
	EntryEdit ();
	int getEntryNumber (string&);
	string getMarker(string&);
	int convertToNumber(string);
	string getName ();
	void getTime (int&, int&, int&, int&);
	void getDate (int&, int&, int&, int&, int&, int&);
	string getLocation ();
	string getStatus();
};

#endif