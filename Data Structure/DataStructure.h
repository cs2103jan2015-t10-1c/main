#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <string>
#include <vector>
using namespace std;

class DataStructure{
private:
	struct Date{
		int _day;
		int _month;
		int _year;
	};
	struct Time{
		int _hour;
		int _minute;
	};
	struct Content{
		string _name;
		struct Date _date;
		struct Time _startTime;
		struct Time _endTime;
		string _location;
	};

	vector<Content> _list;

public:
	DataStructure ();
	void createContent(string, Date, Time, Time, string);
	Date newDate(int, int, int);
	Time newTime (int, int);
	void insertDate(Content&, Date);
	void insertStartTime(Content&, Time);
	void insertEndTime(Content&, Time);
	void addContent(Content);
	void display();
};
#endif