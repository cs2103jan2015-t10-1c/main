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

void DataStructure::createContent(string name, Date newDate, int startTime, int endTime){
	Content event;

	event._name = name;
	insertDate(event, newDate);
	event._startTime = startTime;
	event._endTime = endTime;
	addContent(event);
}

void DataStructure::insertDate(Content& event, Date inputDate){
	event._date._day = inputDate._day;
	event._date._month = inputDate._month;
	event._date._year = inputDate._year;

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
			<< iter->_startTime << " "
			<< iter->_endTime << endl;
	}
}



	

