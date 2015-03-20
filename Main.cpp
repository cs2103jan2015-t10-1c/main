#include <sstream>
#include "ScheduledEntry.h"
#include "SeparateEntryComponents.h"
#include "TextUI.h"
#include "EntryEditor.h"

#include <assert.h>

using namespace std;

const string COMMAND_PROMPT = "command: ";

//commands
const string COMMAND_ADD = "add";
const string COMMAND_EDIT = "edit";
const string COMMAND_DISPLAY = "display";
const string COMMAND_DELETE = "delete";
const string COMMAND_EXIT = "exit";

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear);
void initialiseTime (Time &inputTime, int inputHour, int inputMinute);
void initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation);

/*
class InvalidInputException: public exception {
private:
	string message;
public:
	InvalidInputException(string msg){
		message = msg;
	}

	virtual constant char* what() const throw(){
		return message.c_str();
	}
};
*/

int main (){
    bool running = true;
    string command;
	string userInput;
	string entryName;
	string date;
	string period;
	string entryLocation;
	int inputStartDay = 0; int inputStartMonth = 0; int inputStartYear = 0;
	int inputEndDay = 0; int inputEndMonth = 0; int inputEndYear = 0;
	int inputStartHour = 0; int inputStartMinute = 0;
	int inputEndHour = 0; int inputEndMinute = 0;

	ScheduledEntry newList;

	while(running){
		cout << COMMAND_PROMPT;
		getline(cin, userInput);
		TextUI task(userInput);
		command = task.findCommand(userInput);
		userInput = task.removeCommand(userInput);
		SeparateEntryComponents parse;
		
		//add command
		if(command == COMMAND_ADD){
			parse.dissectCommand(userInput, entryName, period, date, entryLocation);
			parse.convertDate(date, inputStartDay, inputStartMonth, inputStartYear);
			parse.convertTime(period, inputStartHour, inputStartMinute, inputEndHour, inputEndMinute);
			
			assert(inputStartDay >= 0);
			assert(inputStartMonth >= 0);
			assert(inputEndDay >= 0);
			assert(inputEndMonth >= 0);

			//initialise start and end dates
			Date startDate;
			Date endDate;
			initialiseDate(startDate, inputStartDay, inputStartMonth, inputStartYear);
			initialiseDate(endDate, inputEndDay, inputEndMonth, inputEndYear);
			
			//initialise start and end times
			Time startTime;
			Time endTime;
			initialiseTime(startTime, inputStartHour, inputStartMinute);
			initialiseTime(endTime, inputEndHour, inputEndMinute);
						
			//initialise entry
			Entry newEntry;
			initialiseEntry(newEntry, entryName, startDate, endDate, startTime, endTime, entryLocation);
			
			//add new entry to the list
			newList.addEntry(newEntry);
		}
		
		//edit command
		else if(command == COMMAND_EDIT){ 		
			newList.editEntry(userInput);
		}
		
		//display command
		else if(command == COMMAND_DISPLAY){
			newList.display();
		}

		//delete command
		else if(command == COMMAND_DELETE){
			int indexNumber;
			istringstream convertIndexNumber(userInput);
			if (!(convertIndexNumber >> indexNumber)){
				indexNumber = 0;
			}
			newList.removeEntry(indexNumber);
		}

		//exit command
		else if(command == COMMAND_EXIT){
			running = false;
		}
	}

	system("pause");
	return 0;
	}

void initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear){
	inputDate.insertDay(inputDay);
	inputDate.insertMonth(inputMonth);
	inputDate.insertYear(inputYear);
}

void initialiseTime(Time& inputTime, int inputHour, int inputMinute){
	inputTime.insertHour(inputHour);
	inputTime.insertMinute(inputMinute);
}

void initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation){
	newEntry.insertName(entryName);
	newEntry.insertStartDate(startDate);
	newEntry.insertEndDate(endDate);
	newEntry.insertStartTime(startTime);
	newEntry.insertEndTime(endTime);
	newEntry.insertLocation(entryLocation);
}