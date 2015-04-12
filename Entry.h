#ifndef ENTRY_H
#define ENTRY_H

#include "EntryDate.h"
#include "EntryTime.h"

#include <vector>
#include <sstream>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Entry{
private:
	int _entryNumber;
	static const string FEEDBACK_AT;

	string _name;

	Date _startDate;
	Date _endDate;
	bool _hasDate;

	Time _startTime;
	Time _endTime;
	bool _hasTime;
	
	string _location;
	
	vector<string> _tags;

	bool _status;
	

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
	void initialiseStatus();
	void changeStatus();
	string getStatus();
	
	//@author A0115656A
	//input location into an Entry object
	void insertLocation(string);
	//return the value of _location
	string getLocation();
	
	//@author A0116660L
	void insertTags(vector<string>&);
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