#ifndef DATE_H
#define DATE_H
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

class Date{
private:
	int _day;
	int _month;
	int _year;
	bool _hasDate;
	bool _inThePast;
	bool _loading;
	date _entryDate;

public:
	Date();
	Date(bool);
	
	//input day, month and year into a Date object
	void insertDay(int);
	void insertMonth(int);
	void insertYear(int);
	void initialiseDate();
	
	//return the values of the private attributes
	int getDay();
	string getMonth();
	int getMonthNumber();
	int getYear();
	bool getDateStatus();
	date getDate();
	void printDayOfDate();
};

#endif