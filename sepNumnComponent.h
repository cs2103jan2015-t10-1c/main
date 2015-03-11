#ifndef SEPNUMNCOMPONENT_H_
#define SEPNUMNCOMPONENT_H_

#include <iostream>
#include <string>

using namespace std;

class sepNumnComponent{
private:
	int _taskNumber;
	string _item;//indication of which item the user wanna change
	string _newPart;

public:	
	static void getTaskNumber (string taskComponents);
	static void getNewPart (string taskComponents);
	static void convertTime(string taskTime, int &startHour, int &startMin, int &endHour, int &endMin);
	static void convertDate(string taskDate, int &day, int &month, int &year);
	static void convertNumber(string numberString, int&number);
};

#endif