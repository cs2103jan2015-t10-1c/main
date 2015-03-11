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
		<< _scheduledList[index].getLocation() << endl;
}

void ScheduledTask::removeEntry(int index){
	cout << "This entry has been deleted" << endl;
	index--;
	displayEntry(index);
	_scheduledList.erase(_scheduledList.begin()+index);
}

void ScheduledTask::editEntry(string userInput){
	
	EntryEditor editComponent;
			int taskNumber= editComponent.getEntryNumber(userInput);
			string marker= editComponent.getMarker(userInput);
			
			//loop find the ith entry
			if (marker == "-n"){
				string newName = editComponent.getName();
				vector<Entry>::iterator iter = _scheduledList.begin();
			for(int i = 1; i < taskNumber; i++){
					iter++;
			}
			iter->insertName(newName);
			}

			
			if (marker == "-t"){
				int inputStartHour;
				int inputStartMinute;
				int inputEndHour;
				int inputEndMinute;
				editComponent.getTime(inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
				vector<Entry>::iterator iter = _scheduledList.begin();
				for(int i = 1; i < taskNumber; i++){
					iter++;
				}
				Time newStartTime;
				Time newEndTime;
				newStartTime.insertHour(inputStartHour);
				newStartTime.insertMinute(inputStartMinute);
				newEndTime.insertHour(inputEndHour);
				newEndTime.insertMinute(inputEndMinute);

				iter->insertStartTime(newStartTime);
				iter->insertEndTime(newEndTime);
			}
			if (marker == "-d"){
				int inputStartDay;
				int inputStartMonth;
				int inputStartYear;
				
				editComponent.getDate(inputStartDay, inputStartMonth, inputStartYear);
				vector<Entry>::iterator iter = _scheduledList.begin();
				for(int i = 1; i < taskNumber; i++){
					iter++;
				}
				Date newStartDate;
				newStartDate.insertDay(inputStartDay);
				newStartDate.insertMonth(inputStartMonth);
				newStartDate.insertYear(inputStartYear);

				iter->insertStartDate(newStartDate);
							}
			
			if (marker == "-l"){
				string newLocation = editComponent.getLocation();
				vector<Entry>::iterator iter = _scheduledList.begin();
			for(int i = 1; i < taskNumber; i++){
					iter++;
			}
			iter->insertLocation(newLocation);
			}
}