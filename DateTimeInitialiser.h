#ifndef DATETIMEINITIALISER_H
#define DATETIMEINITIALISER_H

#include "Date.h"
#include "MyTime.h"
#include <boost\date_time\gregorian\gregorian.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class DateTimeInitialiser{

public:
	DateTimeInitialiser();
	void initialiseDate(Date&, int, int, int);
	void initialiseTime(Time&, int, int, date);
};
#endif