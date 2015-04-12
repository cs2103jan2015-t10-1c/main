#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include "StringConvertor.h"
#include "Entry.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//@author A0115656A
class EntryEdit {
public:
	enum Field {
		Name, Date, Time, Location, Status, TagAdd, TagRemove
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
	bool _isEdited;
	bool _dateEdited;
	bool _timeEdited;
	bool _tagAdded;
	bool _tagRemoved;

	static const int BLANK_SPACE_COUNT;

	//markers
	static const string NAME_MARKER;
	static const string DATE_MARKER;
	static const string TIME_MARKER;
	static const string LOCATION_MARKER;
	static const string STATUS_MARKER;
	static const string TAG_ADD_MARKER;
	static const string TAG_REMOVE_MARKER;
	static const string FULLSTOP_MARKER;

public:	
	//@author A0115656A
	EntryEdit(bool);
	int getEntryNumber(string&);
	//@author A0116660L
	void extractMarkerInfo(string);
	void extractName(string&, _NEW_CHANGES, bool&);
	//@author A0115656A
	void extractDate(string&, _NEW_CHANGES, bool&);
	void extractTime(string&, _NEW_CHANGES, bool&);
	//@author A0116660L
	void extractLocation(string&, _NEW_CHANGES, bool&);
	void extractStatus(string&, _NEW_CHANGES, bool&);
	//@author A0115656A
	void extractAddedTag(string&, _NEW_CHANGES, bool&);
	void extractRemovedTag(string&, _NEW_CHANGES, bool&);
	void extractRemainder(int, string&, bool&);

	//@author A0115902N
	string getName();
	void getDate(int&, int&, int&, int&, int&, int&);
	void getTime(int&, int&, int&, int&);
	//@author A0116660L
	string getLocation();
	string getStatus();
	//@author A0115656A
	void addTag(Entry&, ostringstream&);
	void removeTag(Entry&, ostringstream&);

	bool getEditStatus();
	bool getDateEditStatus();
	bool getTimeEditStatus();
	bool getTagAddedStatus();
	bool getTagRemovedStatus();
};

#endif