#ifndef ENTRY_H
#define ENTRY_H
#include "Date.h"
#include "Time.h"

class Entry{
private:
	string _name;
	Date _startDate;
	Date _endDate;
	Time _startTime;
	Time _endTime;
	string _location;

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

	//Time
	//input start time and end time into an Entry object
	void insertStartTime(Time);
	void insertEndTime(Time);
	//return the values of Time type private attributes
	Time getStartTime();
	Time getEndTime();
	
	//input location into an Entry object
	void insertLocation(string);
	//return the value of _location
	string getLocation();
};

#endif