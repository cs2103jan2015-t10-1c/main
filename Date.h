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
	date _entryDate;

public:
	Date();
	
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
	date getDate();

};

#endif