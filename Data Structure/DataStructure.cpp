#include <iostream>
#include <string>
#include "DataStructure.h"

using namespace std;

DataStructure::DataStructure(){
}

DataStructure::Date DataStructure::newDate(int inputDay, int inputMonth, int inputYear){
	Date inputDate;
	inputDate._day = inputDay;
	inputDate._month = inputMonth;
	inputDate._year = inputYear;

	return inputDate;
}

DataStructure::Time DataStructure::newTime(int inputHour, int inputMinute){
	Time inputTime;
	inputTime._hour = inputHour;
	inputTime._minute = inputMinute;
	return inputTime;
}

void DataStructure::createContent(string name, Date newDate, Time newTime){
	Content event;
	event._name = name;
	insertDate(event, newDate);
	insertTime(event, newTime);
	addContent(event);
}

void DataStructure::insertDate(Content& event, Date inputDate){
	event._date._day = inputDate._day;
	event._date._month = inputDate._month;
	event._date._year = inputDate._year;
}

void DataStructure::insertTime(Content& event, Time inputTime){
	event._time._hour = inputTime._hour;
	event._time._minute = inputTime._minute;

}

void DataStructure::addContent(Content event){
	_list.push_back(event);
}

void DataStructure::display(){
	vector<Content>::iterator iter;
	for(iter=_list.begin();iter!=_list.end();iter++){
		cout << iter->_name << " " 
			<< iter->_date._day << " "
			<< iter->_date._month << " "
			<< iter->_date._year << " "
			<< iter->_time._hour << " "
			<< iter->_time._minute << endl;
	}
}



	

