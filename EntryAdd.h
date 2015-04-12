#ifndef ENTRYADD_H_
#define ENTRYADD_H_

#include <iostream>
#include <string>
#include <Windows.h>
#include "StringConvertor.h"
#include "Entry.h"

using namespace std;

class EntryAdd{
private:
	static const int BLANK_SPACE_COUNT;
	static const int INITIAL_POSITION;
	static const string AT_MARKER;
	static const string BY_MARKER;
	static const string BLANK_SPACE;
	static const string FROM_MARKER;
	static const string FULLSTOP_MARKER;
	static const string ON_MARKER;
	static const string TAG_MARKER;
	static const string TO_MARKER;
	
public:
	 //@author A0116660L
	 //extract out different components in an add command such as
	 //name, date, time, location or tags
	 //This function will call separate functions to do the specific job
	 void dissectCommand(string, string&, string&, string&, string&, string&, string&, vector<string>&);
	 //Extract the name from the string passed on from the TextUI
	 //with the command word removed
	 void extractName(string&, string&);
	 //Extract the time from the string passed on from the TextUI
	 //with the command word removed
	 void extractTime(string&, string&);
	 //Extract the date from the string passed on from the TextUI
	 //with the command word removed
	 void extractDate(string&, string&);
	 //Extract the location from the string passed on from the TextUI
	 //with the command word removed
	 void extractLocation(string&, string&);
	 //Extract the tag from the string passed on from the TextUI
	 //with the command word removed
	 void extractTag(string&, vector<string>&);
	 //@author A0115902N
	 void convertTime(string, int&, int&);
	 void convertDate(string, int&, int&, int&);

	 HANDLE hConsole;
};

#endif