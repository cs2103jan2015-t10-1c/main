#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <sstream>
#include "EntryDate.h"
#include "EntryTime.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Entry{
private:
	int _entryNumber;
	static const string FEEDBACK_AT;

	string _name;
	string _location;

	Date _startDate;
	Date _endDate;
	
	Time _startTime;
	Time _endTime;

	bool _hasTime;
	bool _hasDate;
	bool _status;
	
	vector<string> _tags;

public:
	Entry();
	//@author A0115656A
	void insertEntryNumber(int entryNumber);
	int getEntryNumber();
	//input name of entry into an Entry object
	void insertName(string);
	//return the value of _name
	string getName();
	
	//@author A0115902N
	//Date
	//input start date and end date into an Entry object
	void insertStartDate(Date);
	void insertEndDate(Date);
	//return the values of Date type private attributes
	Date getStartDate();
	Date getEndDate();
	bool getDateStatus();

	//Time
	//input start time and end time into an Entry object
	void insertStartTime(Time);
	void insertEndTime(Time);
	//return the values of Time type private attributes
	Time getStartTime();
	Time getEndTime();

	//@author A0116660L
	//Status of an entry indicates whether the tast is done or undone. 
	//Status is an attribute of the object called Entry
	//By default all tasks after being created will have the status of undone
	void initialiseStatus();
	//Change the status of the entry to done
	void changeStatus();
	//Return the status of the entry, to the user wants to see if it is done or undone
	string getStatus();
	
	//@author A0115656A
	//input location into an Entry object
	void insertLocation(string);
	//return the value of _location
	string getLocation();
	
	//@author A0116660L
	//Tags is an attribute of an object called Entry, and it is a string
	//Used to include the tags in the object when the user wants to do so
	void insertTags(vector<string>&);
	//Search for a tag and it returns value to indicate whether the tag is found or not
	void searchEntryTag(string, bool&);
	//@author A0115656A
	string getTags();
	void addTag(string);
	void removeTag(string);

	//@author A0115902N
	date_duration calculateDaysFromToday();
	date_duration calculateEventDurationInDays();
	time_duration calculateEventDurationInHours();

	//@author A0115656A
	string storeEntry();
	//@author A0115902N
	string getFullDisplay();
	string getShortDisplay();
};

#endif