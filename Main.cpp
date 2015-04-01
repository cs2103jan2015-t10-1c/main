#include <sstream>
#include "ScheduledEntry.h"
#include "EntryAdd.h"
#include "TextUI.h"
#include "EntryEdit.h"
#include "DateTimeInspector.h"

#include <assert.h>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string COMMAND_PROMPT = "command: ";

//commands
const string COMMAND_ADD = "add";
const string COMMAND_EDIT = "edit";
const string COMMAND_DISPLAY_SCHEDULED = "displaysch";
const string COMMAND_DISPLAY_FLOATING = "displayflo";
const string COMMAND_DELETE = "delete";
const string COMMAND_EXIT = "exit";
const string COMMAND_SEARCH = "search";
const string COMMAND_HELP = "help";

void initialiseDate (Date &inputDate, int inputDay, int inputMonth, int inputYear);
void initialiseTime (Time &inputTime, int inputHour, int inputMinute);
void initialiseEntry(Entry& newEntry, string entryName, Date startDate, Date endDate, Time startTime, Time endTime, string entryLocation, vector<string>& tags);

int main (){
    bool running = true;
    string command = "";
	string userInput = "";
	string entryName = "";
	string stringStartDate = "";
	string stringStartTime = "";
	string stringEndDate = "";
	string stringEndTime = "";
	string entryLocation = "";
	string keyword = "";

	TextUI task(userInput);
	task.displayWelcomeMessage();
	task.displayCurrentDateTime();
	
	ScheduledEntry newList;

	//load existing entries
	cout << "Loading existing entries..." << endl << endl;
	ifstream readFile("FastAddList.txt");
	while (getline(readFile, userInput)){
		Entry newEntry;
		string stringTags;
		vector<string> tags;
		if (userInput != ""){
			entryName = userInput;
			getline(readFile, stringStartDate);
			getline(readFile, stringStartTime);
			getline(readFile, stringEndDate);
			getline(readFile, stringEndTime);
			getline(readFile, entryLocation);
			getline(readFile, stringTags);

			int intStartDay = 0; int intStartMonth = 0; int intStartYear = 0;
			int intEndDay = 0; int intEndMonth = 0; int intEndYear = 0;
			int intStartHour = 0; int intStartMinute = 0;
			int intEndHour = 0; int intEndMinute = 0;
			
			EntryAdd parse;
			parse.convertDate(stringStartDate, intStartDay, intStartMonth, intStartYear);
			parse.convertTime(stringStartTime, intStartHour, intStartMinute);	
			parse.convertDate(stringEndDate, intEndDay, intEndMonth, intEndYear);
			parse.convertTime(stringEndTime, intEndHour, intEndMinute);
			parse.extractTag(stringTags, tags);

			//initialise start and end dates
			Date startDate;
			Date endDate;
			
			initialiseDate(startDate, intStartDay, intStartMonth, intStartYear);
			initialiseDate(endDate, intEndDay, intEndMonth, intEndYear);

			//initialise start and end times
			Time startTime;
			Time endTime;
			initialiseTime(startTime, intStartHour, intStartMinute);
			initialiseTime(endTime, intEndHour, intEndMinute);
						
			//initialise entry
			initialiseEntry(newEntry, entryName, startDate, endDate, startTime, endTime, entryLocation, tags);
			newList.addEntry(newEntry);
		}
	}
	readFile.close();
	cout << endl << "Loading done..." << endl << endl;

	command = "";
	userInput = "";
	entryName = "";
	stringStartDate = "";
	stringStartTime = "";
	stringEndDate = "";
	stringEndTime = "";
	entryLocation = "";
	keyword = "";

	while(running){
		int intStartDay = 0; int intStartMonth = 0; int intStartYear = 0;
		int intEndDay = 0; int intEndMonth = 0; int intEndYear = 0;
		int intStartHour = 0; int intStartMinute = 0;
		int intEndHour = 0; int intEndMinute = 0;
		cout << COMMAND_PROMPT;
		getline(cin, userInput);

		command = task.findCommand(userInput);
		userInput = task.removeCommand(userInput);
	
		//add command
		if(command == COMMAND_ADD){
			EntryAdd parse;
			vector<string> tags;
			bool dateIsOkay = true;
			bool timeIsOkay = true;
			Date startDate;
			Date endDate;
			Time startTime;
			Time endTime;
			parse.dissectCommand(userInput, entryName, stringStartDate, stringStartTime, stringEndDate, stringEndTime, entryLocation, tags);
			
			if (stringStartDate != ""){
				parse.convertDate(stringStartDate, intStartDay, intStartMonth, intStartYear);
				parse.convertDate(stringEndDate, intEndDay, intEndMonth, intEndYear);
				parse.convertTime(stringStartTime, intStartHour, intStartMinute);
				parse.convertTime(stringEndTime, intEndHour, intEndMinute);
			}
			
			assert(intStartDay >= 0);
			assert(intStartMonth >= 0);
			assert(intEndDay >= 0);
			assert(intEndMonth >= 0);

			//initialise start and end dates
			DateTimeInspector DateInspector;
			if(!DateInspector.dateIsValid(intStartDay, intStartMonth, intStartYear)){
				cout << "Start Date is invalid!" << endl << endl;
				dateIsOkay = false;
			}
			else{
				initialiseDate(startDate, intStartDay, intStartMonth, intStartYear);
			}
			if(!DateInspector.dateIsValid(intEndDay, intEndMonth, intEndYear)){
				cout << "End Date is invalid!" << endl << endl;
				dateIsOkay = false;
			}
			else{
				initialiseDate(endDate, intEndDay, intEndMonth, intEndYear);
			}
			//only when date is ok
			if(dateIsOkay){
			//initialise start and end times
				DateTimeInspector TimeInspector;
				if(!TimeInspector.timeIsValid(intStartHour, intStartMinute)){
					cout << "Start Time is invalid!" << endl << endl;
					timeIsOkay = false;
				}
				else{
					initialiseTime(startTime, intStartHour, intStartMinute);
				}
				if(!DateInspector.timeIsValid(intEndHour, intEndMinute)){
					cout << "End Time is invalid!" << endl << endl;
					timeIsOkay = false;
				}
				else{
					initialiseTime(endTime, intEndHour, intEndMinute);
				}
			}
			//only when time is okay
			if(timeIsOkay){
			//initialise entry
				Entry newEntry;
				initialiseEntry(newEntry, entryName, startDate, endDate, startTime, endTime, entryLocation, tags);

				//add new entry to the list
				newList.addEntry(newEntry);
			}
		}
		
		//edit command
		else if (command == COMMAND_EDIT){ 		
			newList.editEntry(userInput);
		}
		
		//display scheduled command
		else if (command == COMMAND_DISPLAY_SCHEDULED){
			newList.displayScheduled();
		}

		//display floating command
		else if (command == COMMAND_DISPLAY_FLOATING){
			newList.displayFloating();
		}

		//search command
		else if (command == COMMAND_SEARCH){
			keyword = userInput.substr(1);
			if (keyword[0] == '#'){
				newList.searchTag(keyword);
			}
			else {
				newList.searchEntry(keyword);
			}
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

