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
	struct Content{
		string _name;
		struct Date _date;
		int _startTime;
		int _endTime; 
	};

	vector<Content> _list;

public:
	DataStructure ();
	void createContent(string, int, int, int);
	void addContent(Content);
	void display();
};
#endif