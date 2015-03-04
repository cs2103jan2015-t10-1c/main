#include <iostream>
#include <string>
#include "DataStructure.h"

using namespace std;

DataStructure::DataStructure(){
}

void DataStructure::createContent(string name, int day, int startTime, int endTime){
	Content event;
	event._name = name;
	event._date._day = day;
	event._startTime = startTime;
	event._endTime = endTime;
	addContent(event);
}

void DataStructure::addContent(Content event){
	_list.push_back(event);
}

void DataStructure::display(){
	vector<Content>::iterator iter;
	for(iter=_list.begin();iter!=_list.end();iter++){
		cout << iter->_name << " " 
			<< iter->_date._day << " "
			<< iter->_startTime << " "
			<< iter->_endTime << endl;
	}
}



	

