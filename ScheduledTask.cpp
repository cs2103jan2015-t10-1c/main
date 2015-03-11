#include "ScheduledTask.h"
#include <iostream>

ScheduledTask::ScheduledTask(){
}

void ScheduledTask::addEntry(Entry newEntry){
	_scheduledList.push_back(newEntry);
}

void ScheduledTask::display(){
	int number = 1;
	vector<Entry>::iterator iter;
	for (iter = _scheduledList.begin(); iter != _scheduledList.end(); iter++){
		Date entryStartDate = iter->getStartDate();
		Date entryEndDate = iter->getEndDate();
		Time entryStartTime = iter->getStartTime();
		Time entryEndTime = iter->getEndTime();
		cout << number << ". "
			<< iter->getName() << ". "
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
		number++;
	}
}