#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include "StringConvertor.h"
#include "Entry.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EntryEdit{
public:
	enum Field {
		Name, Date, Time, Location, Status
	};

private:
	bool _isScheduled;
	int _entryNumber;
	struct _NEW_CHANGES {
		Field _editedField;
		//new edited information
		string _newInformation;
	};
	vector<_NEW_CHANGES> _changesList;
	bool _dateEdited;
	bool _timeEdited;

	static const int BLANK_SPACE_COUNT;

	//markers
	static const string NAME_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;
	static const string FULLSTOP_MARKER;

public:	
	EntryEdit(bool);
	int getEntryNumber(string&);
	void extractMarkerInfo(string);
	void extractName(string&, _NEW_CHANGES, bool&);
	void extractDate(string&, _NEW_CHANGES, bool&);
	void extractTime(string&, _NEW_CHANGES, bool&);
	void extractLocation(string&, _NEW_CHANGES, bool&);
	void extractStatus(string&, _NEW_CHANGES, bool&);
	void extractRemainder(int, string&, bool&);

	int convertToNumber(string);
	string getName();
	void getDate(int&, int&, int&, int&, int&, int&);
	void getTime(int&, int&, int&, int&);
	string getLocation ();
	string getStatus();

	bool getDateEditStatus();
	bool getTimeEditStatus();
};

#endif