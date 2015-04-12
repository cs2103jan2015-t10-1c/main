#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include <iostream>
#include <string>
#include <vector>
#include "StringConvertor.h"
#include "Entry.h"

using namespace std;

//@author A0115656A
class EntryEdit {
public:
	enum Field {
		Name, Date, Time, Location, Status, TagAdd, TagRemove
	};

private:
	bool _isScheduled;
	bool _isEdited;
	bool _dateEdited;
	bool _timeEdited;
	bool _tagAdded;
	bool _tagRemoved;

	int _entryNumber;
	struct _NEW_CHANGES {
		Field _editedField;
		//new edited information
		string _newInformation;
	};
	vector<_NEW_CHANGES> _changesList;
	
	static const int BLANK_SPACE_COUNT;
	static const int INITIAL_POSITION;

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
	EntryEdit(bool);
	int getEntryNumber(string&);
	//@author A0116660L
	//extract the markers and strings of new information, and push them into _changesList vector
	void extractMarkerInfo(string);
	//Extract out the component which is the name to be edited
	void extractName(string&, _NEW_CHANGES, bool&);
	//@author A0115656A
	void extractDate(string&, _NEW_CHANGES, bool&);
	void extractTime(string&, _NEW_CHANGES, bool&);
	//@author A0116660L
	//Extract out the component which is the location to be edited
	void extractLocation(string&, _NEW_CHANGES, bool&);
	//Extract out the component which is the status to be edited
	void extractStatus(string&, _NEW_CHANGES, bool&);
	//@author A0115656A
	void extractAddedTag(string&, _NEW_CHANGES, bool&);
	void extractRemovedTag(string&, _NEW_CHANGES, bool&);
	void extractRemainder(int, string&, bool&);

	//@author A0115902N
	int convertToNumber(string);
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