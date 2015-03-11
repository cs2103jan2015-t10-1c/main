#include <sstream>
#include "sepNumnComponents.h"



void sepNumnComponent::getTaskNumber (string taskComponents){
	size_t pos = 0;
	string numberString= taskComponents.substr(0);
	taskComponents.erase(0, 1);
	pos=0;		
	_taskNumber=convertNumber(numberString);
}

void sepNumnComponent::getNewPart (string taskComponents){
	size_t pos = 0;
	string time = "-t";
	string date = "-d";
	string loca = "-l";
	char end = '.';
	
	//for item, n=name, t= time, d=date, l=location
	

	if ((pos = taskComponents.find(time)) != std::string::npos || (pos = taskComponents.find(date)) != std::string::npos ||
		(pos = taskComponents.find(loca)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	_newPart = taskComponents.substr(0, pos);
    	taskComponents.erase(0, pos);
    	pos = 0;
		_item = "name";
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 't'){
		if ((pos = taskComponents.find(date)) != std::string::npos ||
		   (pos = taskComponents.find(loca)) != std::string::npos ||(pos = taskComponents.find(end)) != std::string::npos) {
    	_newPart = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		_item = 'time';
		}
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 'd'){
		if ((pos = taskComponents.find(time)) != std::string::npos ||
		   (pos = taskComponents.find(loca)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	_newPart = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		_item = 'date';
		}
	}
	
	if (taskComponents[0] == '-' && taskComponents[1] == 'l'){
		if ((pos = taskComponents.find(time)) != std::string::npos ||
		   (pos = taskComponents.find(date)) != std::string::npos||(pos = taskComponents.find(end)) != std::string::npos) {
    	_newPart = taskComponents.substr(3, pos-3);
    	taskComponents.erase(0, pos);
    	pos = 0;
		_item = 'loc';
		}
	}
	
	return;
}

void SeparateTaskComponents::convertTime(string taskTime, int &startHour, int &startMin, int &endHour, int &endMin){
	istringstream iss(taskTime);
	string start;
	string end;
	iss >> start >> end;

	size_t startDot = start.find_first_of(".");
	string startHourString = start.substr(0, startDot);
	istringstream convertStartHour(startHourString);
	if (!(convertStartHour >> startHour)) {
		startHour = 0;  
	}
	
	string startMinString = start.substr(startDot+1, string::npos);
	istringstream convertStartMin(startMinString);
	if (!(convertStartMin >> startMin)) {
		startMin = 0;  
	}
	
	size_t endDot = end.find_first_of("."); 
	string endHourString = end.substr(0, endDot);
	istringstream convertEndHour(endHourString);
	if (!(convertEndHour >> endHour)) {
		endHour = 0;  
	}

	string endMinString = end.substr(endDot+1, string::npos);
	istringstream convertEndMin(endMinString);
	if (!(convertEndMin >> endMin)) {
		endMin = 0;  
	}
	return;
}

void SeparateTaskComponents::convertDate(string taskDate, int &day, int &month, int &year){
	istringstream iss(taskDate);
	string dayString;
	string monthString;
	string yearString;

	iss >> dayString
		>> monthString
		>> yearString;

	//day
	istringstream convertDay(dayString);
	if (!(convertDay >> day)) {
		day = 0;  
	}
	//month
	if(monthString=="February"){
		month = 2;
	}
	else{
		month = 0;
	}
	//year
	istringstream convertYear(yearString);
	if (!(convertYear >> year)) {
		year = 0;  
	}

}

void SeparateTaskComponents::convertNumber(string numberString, int&number){
	istringstream iss(taskDate);
	iss >> numberString
	istringstream convertNumber(numberString);
	if (!(convertNumber >> number)) {
		number = 0;  
	}
}