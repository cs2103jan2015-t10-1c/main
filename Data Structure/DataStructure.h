#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <string>
#include <vector>
using namespace std;

class DataStructure{
private:
	struct Content{
		string _name;
		int _startTime;
		int _endTime;
	};
	vector<Content> _list;

public:
	DataStructure ();
	void createContent(string, int, int);
	void addContent(Content);
	void display();
};
#endif