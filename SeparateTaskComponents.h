#ifndef SEPARATETASKCOMPONENTS_H_
#define SEPARATETASKCOMPONENTS_H_

#include <iostream>
#include <string>

using namespace std;

class SeparateTaskComponents{
public:
	
	static void dissectCommand (string taskComponents, string &taskName, string &taskTime,
								 string &taskDate, string &taskLocation);
	static void convertTime(string taskTime, int &startHour, int &startMin, int &endHour, int &endMin);
	static void convertDate(string taskDate, int &day, int &month, int &year);
};

#endif