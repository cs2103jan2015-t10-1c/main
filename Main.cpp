#include "ScheduledTask.h"
#include "Date.h"
using namespace std;

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear);
void initialiseTime (Time &inputTime, int inputHour, int inputMinute);

int main (){
	int inputStartDay=10; int inputStartMonth=3; int inputStartYear=2014;
	int inputEndDay=15; int inputEndMonth=12; int inputEndYear=2015;
	int inputStartHour=10; int inputStartMinute=30;
	int inputEndHour=16; int inputEndMinute=45;
	ScheduledTask NewList;
	//initialise Date
	Date StartDate;
	Date EndDate;
	initialiseDate(StartDate, inputStartDay, inputStartMonth, inputStartYear);
	initialiseDate(EndDate, inputEndDay, inputEndMonth, inputEndYear);
	//initialise Time
	Time StartTime;
	Time EndTime;
	initialiseTime(StartTime, inputStartHour, inputStartMinute);
	initialiseTime(EndTime, inputEndHour, inputEndMinute);
	//initialise strings
	string eventName = "Meeting with Bisma";
	string eventLocation = "UTown";
	//initialise content
	Entry Task;
	Task.insertName(eventName);
	Task.insertStartDate(StartDate);
	Task.insertEndDate(EndDate);
	Task.insertStartTime(StartTime);
	Task.insertEndTime(EndTime);
	Task.insertLocation(eventLocation);
	//initialise list
	NewList.addEntry(Task);
	NewList.display();
	system("pause");
	return 0;
}

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear){
	inputDate.insertDay(inputDay);
	inputDate.insertMonth(inputMonth);
	inputDate.insertYear(inputYear);
}

void initialiseTime (Time &inputTime, int inputHour, int inputMinute){
	inputTime.insertHour(inputHour);
	inputTime.insertMinute(inputMinute);
}