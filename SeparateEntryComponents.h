#ifndef SEPARATEENTRYCOMPONENTS_H_
#define SEPARATEENTRYCOMPONENTS_H_

#include <iostream>
#include <string>

using namespace std;

class SeparateEntryComponents{
private:
	static const string MONTH_ARRAY[12];
	static const string STARTDATE_MARKER;
	static const string ENDDATE_MARKER;
	static const string LOCATION_MARKER;
	static const string NAME_MARKER;
	static const string TAG_MARKER;

public:
	 void dissectCommand(string, string&, string&, string&, string&, string&, string&, string&);
	 void extractName(string&, size_t, string&);
	 void extractTime(string&, size_t, string&);
	 void extractDate(string&, size_t, string&);
	 void extractLocation(string&, size_t, string&);
	 void extractTag(string&, size_t, string&);
	 void convertTime(string, int&, int&);
	 void convertDate(string, int&, int&, int&);
};

#endif