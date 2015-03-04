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

void DataStructure::createContent(string name, Date inputDate, Time inputStartTime, Time inputEndTime, string location){
	Content event;
	event._name = name;
	insertDate(event, inputDate);
	insertStartTime(event, inputStartTime);
	insertEndTime(event, inputEndTime);
	event._location = location;
	addContent(event);
}

void DataStructure::insertDate(Content& event, Date inputDate){
	event._date._day = inputDate._day;
	event._date._month = inputDate._month;
	event._date._year = inputDate._year;
}

void DataStructure::insertStartTime(Content& event, Time inputStartTime){
	event._startTime._hour = inputStartTime._hour;
	event._startTime._minute = inputStartTime._minute;
}

void DataStructure::insertEndTime(Content& event, Time inputEndTime){
	event._endTime._hour = inputEndTime._hour;
	event._endTime._minute = inputEndTime._minute;
}

void DataStructure::addContent(Content event){
	_list.push_back(event);
}

void DataStructure::display(){
	vector<Content>::iterator iter;
	for(iter=_list.begin();iter!=_list.end();iter++){
		cout << iter->_name << " " 
			<< iter->_date._day << "/"
			<< iter->_date._month << "/"
			<< iter->_date._year << " "
			<< iter->_startTime._hour << '.'
			<< iter->_startTime._minute << "-"
			<< iter->_endTime._hour << '.'
			<< iter->_endTime._minute << " "
			<< iter->_location << endl;
	}
}