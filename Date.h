#ifndef DATE_H
#define DATE_H
#include <string>

using namespace std;

class Date{
private:
	int _day;
	int _month;
	int _year;

public:
	Date();
	
	//input day, month and year into a Date object
	void insertDay(int);
	void insertMonth(int);
	void insertYear(int);
	
	//return the values of the private attributes
	int getDay();
	string getMonth();
	int getYear();

};

#endif