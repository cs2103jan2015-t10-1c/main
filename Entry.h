#ifndef ENTRY_H
#define ENTRY_H

#include "Date.h"
#include "Time.h"

#include <vector>
#include <sstream>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Entry{
private:
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
	//input name of entry into an Entry object
	void insertName(string);
	//return the value of _name
	string getName();
	
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

	void initialiseStatus();
	void changeStatus();
	string getStatus();
	
	//input location into an Entry object
	void insertLocation(string);
	//return the value of _location
	string getLocation();
	
	void insertTags(vector<string>&);
	void searchEntryTag(string, int);
	string getTags();
	void addTag(string);
	void removeTag(string);

	date_duration calculateDaysFromToday();
	date_duration calculateEventDurationInDays();
	time_duration calculateEventDurationInHours();

	string storeEntry();
	string getFullDisplay();
	string getShortDisplay();
};

#endif