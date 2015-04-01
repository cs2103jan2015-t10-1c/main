#ifndef DATETIMEINSPECTOR_H
#define DATETIMEINSPECTOR_H
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class DateTimeInspector{
private:
	date _testDate;
	ptime _testTime;
public:
	DateTimeInspector();
	bool dateIsValid(int, int, int);
	bool timeIsValid (int, int);

};

#endif