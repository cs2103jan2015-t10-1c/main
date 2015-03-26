#ifndef STRINGCONVERTOR_H_
#define STRINGCONVERTOR_H_

#include <iostream>
#include <sstream>

using namespace std;

class StringConvertor{
private:
	static const string FULLSTOP_MARKER;
	static const string MONTH_ARRAY[12];

public:
	void convertDate(string, int&, int&, int&);
	void convertTime(string, int&, int&);
};

#endif