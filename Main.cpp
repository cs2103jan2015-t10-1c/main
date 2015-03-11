<<<<<<< HEAD
#include "DataStructure.h"

using namespace std;

int main(){
	DataStructure helloworld;
	helloworld.createContent("bisma", helloworld.newDate(2, 3, 1980), helloworld.newTime(19, 30), helloworld.newTime(20, 30), "haw par villa");
	helloworld.createContent("hawe", helloworld.newDate(3, 4, 1995), helloworld.newTime(10, 40), helloworld.newTime(11, 40), "joo koon");
	helloworld.display();
	system("pause");
	return 0;
=======
#include "ScheduledTask.h"
#include "SeparateEntryComponents.h"
#include "Date.h"
#include "TextUI.h"
#include "EntryEditor.h"

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

	if(command == "add")
		{
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
		else if(command == "edit")
		{ 			
			EntryEditor editComponent;
			int taskNumber= editComponent.getEntryNumber(userInput);
			string marker= editComponent.getMarker(userInput);
				
			
			//loop find the ith entry
			if (marker == "-n"){
				string newName = editComponent.getName();
			vector<Entry>::iterator iter;
			for(int i = 0; i < taskNumber; i++){
					iter++;
			}
			iter->insertName(newName);
			}
			/*if (marker == "-t"){
				Parse.convertTime(period, inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
				Task.insertStartTime(StartTime);
				Task.insertEndTime(EndTime);
			}
			if (marker == "-d"){
				Parse.convertDate(date, inputStartDay, inputStartMonth, inputStartYear);
				Task.insertStartDate(StartDate);
				Task.insertEndDate(EndDate);
			}
			if (marker == "-l"){
				Task.insertLocation(newPart);
			}*/
	}
	else if(command == "display"){
			NewList.display();
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
>>>>>>> 5de87de1938b84af4698d592d9a3bd3d139baa75
}