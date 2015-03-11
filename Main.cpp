#include <sstream>
#include "ScheduledTask.h"
#include "SeparateEntryComponents.h"
#include "Date.h"
#include "TextUI.h"


using namespace std;

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear);
void initialiseTime (Time &inputTime, int inputHour, int inputMinute);

int main (){
	const int END = 0;
    bool RUNNING = true;
    string command;
	string userInput;
	string eventName;
	string eventLocation;
	string date;
	string period;
	int inputStartDay = 0; int inputStartMonth = 0; int inputStartYear = 0;
	int inputEndDay = 0; int inputEndMonth = 0; int inputEndYear = 0;
	int inputStartHour = 0; int inputStartMinute = 0;
	int inputEndHour = 0; int inputEndMinute = 0;

	ScheduledTask NewList;

	while(RUNNING){
		cout << "command: ";
		getline(cin, userInput);
		TextUI task(userInput);
		command = task.findCommand(userInput);
		userInput = task.removeCommand(userInput);
		cout<< command << " " << userInput << endl;
		SeparateEntryComponents Parse;
		
		if(command == "add"){
			Parse.dissectCommand(userInput, eventName, period, date, eventLocation);
			Parse.convertDate(date, inputStartDay, inputStartMonth, inputStartYear);
			Parse.convertTime(period, inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
			
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
		}
		
		else if(command == "display"){
			NewList.display();
		}

		else if(command == "delete"){
			int indexNumber;
			istringstream convertIndexNumber(userInput);
			if (!(convertIndexNumber >> indexNumber)){
				indexNumber = 0;
			}
			NewList.removeEntry(indexNumber);
		}

		else if(command == "exit"){
			RUNNING = false;
		}
	}
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