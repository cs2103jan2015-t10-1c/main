#ifndef STRINGCONVERTOR_H_
#define STRINGCONVERTOR_H_

#include <iostream>
#include <sstream>

using namespace std;

class StringConvertor{
private:
	static const string MONTHSHORT_ARRAY[12];
	static const string MONTHLONG_ARRAY[12];
	static const int BLANK_SPACE_COUNT;
	static const string BLANK_SPACE;
	static const string FULLSTOP_MARKER;

public:
	void extractStringDate(string&, string&);
	void extractStringTime(string&, string&);
	void convertDate(string, int&, int&, int&);
	void convertTime(string, int&, int&);
};

#endif