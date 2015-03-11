#include "ScheduledTask.h"
#include <iostream>

ScheduledTask::ScheduledTask(){
}

void ScheduledTask::addEntry(Entry newEntry){
	_scheduledList.push_back(newEntry);
}

void ScheduledTask::display(){
	vector<Entry>::iterator iter;
	for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
		Date entryStartDate = iter->getStartDate();
		Date entryEndDate = iter->getEndDate();
		Time entryStartTime = iter->getStartTime();
		Time entryEndTime = iter->getEndTime();
		cout << iter->getName() << ". "
			<< entryStartDate.getDay() << " "
			<< entryStartDate.getMonth() << " "
			<< entryStartDate.getYear() << " at "
			<< entryStartTime.getHour() << "."
			<< entryStartTime.getMinute() << " to "
			/*<< entryEndDate.getDay() << " "
			<< entryEndDate.getMonth() << " "
			<< entryEndDate.getYear() << " at "*/
			<< entryEndTime.getHour() << "."
			<< entryEndTime.getMinute() << ". " 
			<< iter->getLocation() << endl;
	}
}

void ScheduledTask::displayEntry(int index){
	Date entryStartDate = _scheduledList[index].getStartDate();
	Date entryEndDate = _scheduledList[index].getEndDate();
	Time entryStartTime = _scheduledList[index].getStartTime();
	Time entryEndTime = _scheduledList[index].getEndTime();
	cout << _scheduledList[index].getName() << ". "
		<< entryStartDate.getDay() << " "
		<< entryStartDate.getMonth() << " "
		<< entryStartDate.getYear() << " at "			
		<< entryStartTime.getHour() << "."
		<< entryStartTime.getMinute() <<" to "
		/*<< entryEndDate.getDay() << " "
		<< entryEndDate.getMonth() << " "
		<< entryEndDate.getYear() << " at "*/
		<< entryEndTime.getHour() << "."
		<< entryEndTime.getMinute() << ". " 
		<< _scheduledList[index-1].getLocation() << endl;
}

void ScheduledTask::removeTask(int index){
	cout << "Please enter the number of the entry you want to delete" << endl;
	int index;
	cin >> index;
	cout << "Are you sure you want to delete the following entry" << endl;
	index--;
	displayEntry(index);
	_scheduledList.erase(_scheduledList.begin()+index);
}