#ifndef SEPARATEENTRYCOMPONENTS_H_
#define SEPARATEENTRYCOMPONENTS_H_

#include <iostream>
#include <string>

using namespace std;

class SeparateEntryComponents{
private:
	
	static const string MONTH_ARRAY[12];
	static const int BLANK_SPACE_COUNT;
	static const string AT_MARKER;
	static const string BLANK_SPACE;
	static const string FROM_MARKER;
	static const string FULLSTOP_MARKER;
	static const string ON_MARKER;
	static const string TAG_MARKER;
	static const string TO_MARKER;
	
public:
	 void dissectCommand(string, string&, string&, string&, string&, string&, string&, string&);
	 void extractName(string&, string&);
	 void extractTime(string&, string&);
	 void extractDate(string&, string&);
	 void extractLocation(string&, string&);
	 void extractTag(string&, string&);
	 void convertTime(string, int&, int&);
	 void convertDate(string, int&, int&, int&);
};

#endif