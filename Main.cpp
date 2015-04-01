#include <sstream>
#include "ScheduledEntry.h"
#include "EntryAdd.h"
#include "TextUI.h"
#include "EntryEdit.h"


#include <assert.h>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string COMMAND_PROMPT = "command: ";

//commands
const string COMMAND_ADD = "add";
const string COMMAND_EDIT = "edit";
const string COMMAND_DISPLAY = "display";
const string COMMAND_DELETE = "delete";
const string COMMAND_EXIT = "exit";
const string COMMAND_SEARCH = "search";
const string COMMAND_HELP = "help";

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear);
void initialiseTime (Time &inputTime, int inputHour, int inputMinute);
void initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation, vector<string>& tags);

int main (){
    bool running = true;
    string command;
	string userInput;
	string entryName;
	string startDate;
	string endDate;
	string startTime;
	string endTime;
	string entryLocation;
	string keyword;

	TextUI task(userInput);
	task.displayWelcomeMessage();
	task.displayCurrentDateTime();
	
	ScheduledEntry newList;

	//load existing entries
	ifstream readFile("FastAddList.txt");
	while (getline(readFile, userInput)){
		Entry newEntry;
		string stringTags;
		vector<string> tags;
		if (userInput != ""){
			entryName = userInput;
			getline(readFile, startDate);
			getline(readFile, startTime);
			getline(readFile, endDate);
			getline(readFile, endTime);
			getline(readFile, entryLocation);
			getline(readFile, stringTags); 

			int inputStartDay = 0; int inputStartMonth = 0; int inputStartYear = 0;
			int inputEndDay = 0; int inputEndMonth = 0; int inputEndYear = 0;
			int inputStartHour = 0; int inputStartMinute = 0;
			int inputEndHour = 0; int inputEndMinute = 0;
			
			EntryAdd parse;
			parse.convertDate(startDate, inputStartDay, inputStartMonth, inputStartYear);
			parse.convertTime(startTime, inputStartHour, inputStartMinute);	
			parse.convertDate(endDate, inputEndDay, inputEndMonth, inputEndYear);
			parse.convertTime(endTime, inputEndHour, inputEndMinute);
			parse.extractTag(stringTags, tags);

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
			initialiseEntry(newEntry, entryName, startDate, endDate, startTime, endTime, entryLocation, tags);
			newList.addEntry(newEntry);
		}
	}
	readFile.close();

	while(running){
		int inputStartDay = 0; int inputStartMonth = 0; int inputStartYear = 0;
		int inputEndDay = 0; int inputEndMonth = 0; int inputEndYear = 0;
		int inputStartHour = 0; int inputStartMinute = 0;
		int inputEndHour = 0; int inputEndMinute = 0;
		cout << COMMAND_PROMPT;
		getline(cin, userInput);

		command = task.findCommand(userInput);
		userInput = task.removeCommand(userInput);
	
		//add command
		if(command == COMMAND_ADD){
			EntryAdd parse;
			vector<string> tags;
			parse.dissectCommand(userInput, entryName, startTime, endTime, startDate, endDate, entryLocation, tags);
			
			//if (startTime != 0){
				//cout << "no date!" << endl;
				parse.convertDate(startDate, inputStartDay, inputStartMonth, inputStartYear);
				parse.convertDate(endDate, inputEndDay, inputEndMonth, inputEndYear);
				parse.convertTime(startTime, inputStartHour, inputStartMinute);
				parse.convertTime(endTime, inputEndHour, inputEndMinute);
			//}
			
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
			initialiseEntry(newEntry, entryName, startDate, endDate, startTime, endTime, entryLocation, tags);
			//add new entry to the list
			newList.addEntry(newEntry);
		}
		
		//edit command
		else if (command == COMMAND_EDIT){ 		
			newList.editEntry(userInput);
		}
		
		//display command
		else if (command == COMMAND_DISPLAY){
			newList.displayScheduled();
		}

		//search command
		else if (command == COMMAND_SEARCH){
			keyword = userInput.substr(1);
			newList.searchTag(keyword);
		}

		//help command
		else if (command == COMMAND_HELP){
			task.displayHelp();
		}

		//delete command
		else if (command == COMMAND_DELETE){
			int indexNumber;
			istringstream convertIndexNumber(userInput);
			if (!(convertIndexNumber >> indexNumber)){
				indexNumber = 0;
			}
			newList.removeEntry(indexNumber);
		}

		//exit command
		else if (command == COMMAND_EXIT){
			newList.exit(running);
		}
		else {
			cout << "Wrong command word. Try again" << endl ;
		}
	cout << endl;
	}
	system("pause");
	return 0;
	}

void initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear){
	int year = inputYear;
	int month = inputMonth;
	int day = inputDay;
	/*try{
		date d(year, month, day);
		throw 20;
	}
	catch(int error){
		cout << "error! date does not exist " << error << endl;
		return;
	}*/
	inputDate.insertDay(inputDay);
	inputDate.insertMonth(inputMonth);
	inputDate.insertYear(inputYear);
}

void initialiseTime(Time& inputTime, int inputHour, int inputMinute){
	inputTime.insertHour(inputHour);
	inputTime.insertMinute(inputMinute);
}

void initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation, vector<string>& tags){
	newEntry.insertName(entryName);
	newEntry.insertStartDate(startDate);
	newEntry.insertEndDate(endDate);
	newEntry.insertStartTime(startTime);
	newEntry.insertEndTime(endTime);
	newEntry.insertLocation(entryLocation);
	newEntry.addTags(tags);
}