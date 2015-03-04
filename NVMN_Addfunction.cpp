#include <iostream>
#include <string>

using namespace std;

void seperateTaskComponents (string taskComponents, string &taskName, string &taskTime,
							 string &taskDate, string &taskLocation);

int main (){
	string example = "Dinner with Christian -t 7pm -d 13 February -l UTOWN.";
	string taskName;
	string taskTime;
	string taskDate;
	string taskLocation;
	seperateTaskComponents(example,taskName,taskTime,taskDate,taskLocation);
	cout << "Task given: " << example << endl;
	cout << "Task name is: " << taskName << endl;
	cout << "Task time is: " << taskTime << endl;
	cout << "Task date is: " << taskDate << endl;
	cout << "Task location is: " << taskLocation << endl;
	
	return 0;
}


void seperateTaskComponents (string taskComponents, string &taskName, string &taskTime,
							 string &taskDate, string &taskLocation){
	size_t pos = 0;
	string time = "-t";
	string date = "-d";
	string loca = "-l";
	char end = '.';
	if ((pos = taskComponents.find(time)) != std::string::npos || (pos = taskComponents.find(date)) != std::string::npos ||
		(pos = taskComponents.find(loca)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	taskName = taskComponents.substr(0, pos);
    	taskComponents.erase(0, pos);
    	pos = 0;
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 't'){
		if ((pos = taskComponents.find(date)) != std::string::npos ||
		   (pos = taskComponents.find(loca)) != std::string::npos ||(pos = taskComponents.find(end)) != std::string::npos) {
    	taskTime = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		}
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 'd'){
		if ((pos = taskComponents.find(time)) != std::string::npos ||
		   (pos = taskComponents.find(loca)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	taskDate = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		}
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 'l'){
		if ((pos = taskComponents.find(time)) != std::string::npos ||
		   (pos = taskComponents.find(date)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	taskLocation = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		}
	}
	
	return;
}
