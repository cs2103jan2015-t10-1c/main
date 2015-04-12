#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "TextUI.h"
#include <Windows.h>

const string TextUI::WELCOME_TO_FASTADD = "Welcome to FastAdd";
const string TextUI::CURRENT_VERSION = "version v0.5";
const string TextUI::KEY_IN_COMMANDS = "Please key in your commands";
const string TextUI::HELP_FOR_INFORMATION = "Type 'help' for information on how to use FastAdd";
const string TextUI::BORDER = "_________________________________________________________";

//@author A0100750Y
TextUI::TextUI(){
}

TextUI::TextUI(string& inputContent){
	_content = inputContent;
}

void TextUI::displayWelcomeMessage(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << WELCOME_TO_FASTADD << endl
		<< CURRENT_VERSION << endl
		<< KEY_IN_COMMANDS << endl << endl;
	displayCurrentDateTime();
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
	cout << HELP_FOR_INFORMATION << endl
		<< endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
}

void TextUI::displayCurrentDateTime(){
	date d(day_clock::local_day());
	ptime t(second_clock::local_time());
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
	cout << "The date today is " << t.date() << endl
		<< "and the time when FastAdd starts was " << t.time_of_day() << endl
		<< endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void TextUI::displayHelp(){
	int helpChoice;
	string helpInput;
	cout << BORDER << endl
		<<"Functions supported in v0.5:" << endl
		<< "1. Add" << endl
		<< "2. Display" << endl
		<< "3. Delete" << endl
		<< "4. Edit"  << endl
		<< "5. Search" << endl
		<< "0. Exit help" << endl;
	cout << "Please key in your choice" << endl
		<< BORDER << endl;
	cout << "help ";
	getline(cin, helpInput);
	cout << BORDER << endl << endl;
	istringstream convertHelpChoice(helpInput);
	if (!(convertHelpChoice >> helpChoice)) {
		helpChoice = 0;  
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (helpChoice){
	case 0:
		break;
	case 1:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "1. Add - " << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "Scheduled entry with <start date and time> and <end date and time>:" << endl
			<< "add holiday. from 2 jun 15 10.30 to 27 Jun 2015 "<< endl 
			<< "20.30 at Europe #holiday" << endl << endl
			<< "Scheduled entry on <one date> with <start time> and <end time>:" << endl
			<< "add career fair. on 14 Mar 2015 9.30 to 20.30  at NUS #careerfair #NUS" << endl << endl
			<< "Deadline on <one date> and <one time>:" << endl
			<< "add UPC2209 essay deadline. by 19 may 15 23.59 #deadline" << endl << endl
			<< "Floating entry without <date> or <time> " << endl
			<< "add return John's thumbdrive. at Cinnamon #friendship #lend" << endl;
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "2. Display - " << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "To display the scheduled entries: display scheduled" << endl << endl
			<< "To display the floating entries: display floating" << endl << endl
			<< "To display clashes between scheduled entries: display clashes" << endl << endl
			<< "To display past events: display past" << endl 
			<< "To navigate through the list: display next or display prev" << endl
			<< "To display a specific entry: display <entry number>" << endl
			<< "To display a specific page: display page <page number>" << endl;
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "3. Delete - " << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "delete <entry number>" << endl;
		break;
	case 4:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "4. Edit - " << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "Edit entry name: edit <entry number> name <new name> " << endl
			<< "e.g. edit 10 name dinner with John" << endl << endl
			<< "Edit entry time. editing both one or two timings are enabled" << endl
			<< "edit <entry number> time <new time> <new time> " << endl
			<< "e.g. edit 2 time 10.30 or edit 2 time 10.30 11.30" << endl 
			<< "Editing the time of a floating entry will move it to the scheduled entry" << endl << endl
			<< "Edit entry date. editing both one or two dates are enabled" << endl
			<< "edit <entry number> date <new date> <new date>" << endl
			<< "e.g. edit 30 date 13 mar 16 or edit 30 date 13 mar 16 17 mar 16" << endl
			<< "Editing the date of a floating entry will move it to the scheduled entry" << endl << endl
			<< "Edit entry location - edit <entry number> place <new location>" << endl
			<< "e.g. edit 41 place NUS" << endl << endl
			<< "Edit entry status (done/undone)" << endl
			<< "edit <entry number> status <done/undone> " << endl
			<< "e.g. edit 5 status done or edit 5 status undone" << endl << endl
			<< "Edit entry tags. both adding and removing tags are enabled" << endl
			<< "<entry number> add <# new tag> or remove <# new tag>" << endl
			<< "e.g. edit 21 add #girlfriend remove #friend" << endl << endl
			<< "Editing multiple parts is also possible, in any orders." << endl
			<< "Each part is separated by full stop" << endl
			<< "e.g. edit 18 name Case Competition Deadline. date 18 feb 15. time 2359." << endl
			<< "place school. add #casecompetition #deadline" << endl;

		break;
	case 5:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "5. Search -" << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "search name <name of event>" << endl
			<< "search place <location> " << endl
			<< "search status \"done\"" << endl
			<< "search status \"undone\"" << endl
			<< "search date <DD Month YYYY>" << endl
			<< "search time <HH.MM>" << endl;
						
		break;
	default:
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Wrong input. Try again";
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		break;
	}
}

string TextUI::findCommand(string& inputContent){
    string commandWord;
    commandWord = inputContent.substr(0,inputContent.find_first_of(' '));
    return commandWord;
}

string TextUI::removeCommand(string& inputContent){
    inputContent = inputContent.erase(0,inputContent.find_first_of(' '));
    return inputContent;
}
    
void TextUI::displayErrorFeedback(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
	cout << "Input command not identified. Please try again."<< endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

void TextUI::displayResizeOptions(){
	int resizeChoice;
	string resizeChoiceInput;
	HWND hWnd=GetConsoleWindow();
	cout << "Please choose one of the resize options below by entering the number" << endl;
	cout << "1. Small" << endl;
	cout << "2. Large" << endl;
	cout << "3. Back to default" << endl;
	cout << BORDER << endl;
	cout << "Your choice is ";
	getline(cin, resizeChoiceInput);
	cout << BORDER << endl << endl;
	istringstream convertResizeChoice(resizeChoiceInput);
	if (!(convertResizeChoice >> resizeChoice)) {
		resizeChoice = 0;  
	}

	switch (resizeChoice){
	case 0:
		break;
	case 1:
		MoveWindow(hWnd,400,0,520,400, TRUE);
		break;
	case 2:
		MoveWindow(hWnd,300,0,1020,720, TRUE);
		break;
	case 3:
		MoveWindow(hWnd,400,0,520,730, TRUE);
		break;
	default:
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
		cout << "Wrong input. Try again";
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		break;
	}
}


