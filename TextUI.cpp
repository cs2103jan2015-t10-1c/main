#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "TextUI.h"
#include <Windows.h>

const string TextUI::WELCOME_TO_FASTADD = "Welcome to FastAdd";
const string TextUI::CURRENT_VERSION = "version v0.4";
const string TextUI::KEY_IN_COMMANDS = "Please key in your commands";
const string TextUI::HELP_FOR_INFORMATION = "Type 'help' for information on how to use FastAdd";

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
		<< KEY_IN_COMMANDS << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
	cout << HELP_FOR_INFORMATION << endl
		<< endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
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
	cout << "Functions supported in v0.2:" << endl
		<< "1. Add" << endl
		<< "2. Display" << endl
		<< "3. Delete" << endl
		<< "4. Edit"  << endl
		<< "5. Search" << endl
		<< "0. Exit help" << endl;
	cout << "Please key in your choice" << endl;
	cout << "help ";
	getline(cin, helpInput);
	istringstream convertHelpChoice(helpInput);
	if (!(convertHelpChoice >> helpChoice)) {
		helpChoice = 0;  
	}
	
	switch (helpChoice){
	case 0:
		break;
	case 1:
		cout << "1. Add - add <event name>. from <DD Month YYYY> <HH.MM> to <DD Month YYYY> "<< endl
			<< "<HH.MM> at <location> #<tag>" << endl
			<< "or - add <even name>. on <DD Month YYYY> <HH.MM> to <HH.MM>  at <location> #<tag>" << endl
			<< "or - add <even name>. by <DD Month YYYY> <HH.MM> at <location> #<tag>" << endl
			<< "or - add <even name>. at <location> #<tag>" << endl;
		break;
	case 2:
		cout << "2. Display - display scheduled" << endl
			<< "or - display floating" << endl;
		break;
	case 3:
		cout << "3. Delete - delete <entry number>" << endl;
		break;
	case 4:
		cout << "4. Edit - these edit functions are enabled: " << endl
			<< "edit <entry number> name <new name> " << endl
			<< "edit <entry number> time <HH.MM> <HH.MM> " << endl
			<< "edit <entry number> date <DD Month YYYY>" << endl
			<< "edit <entry number> place <new location>" << endl
			<< "edit <entry number> status <done/undone> " << endl
			<< "edit <entry number> add <# new tag> " << endl
			<< "edit <entry number> remove <# the tag to be removed>" << endl
			<< "editing multiple parts is also possible, in any orders" <<endl;

		break;
	case 5:
		cout << "5. Search - these search functions are enabled "
			<< "search name <name of event>" << endl
			<< "search place <location> " << endl
			<< "search status <done>" << endl
			<< "search status <undone>" << endl
			<< "search date <DD Month YYYY>" << endl
			<< "search time <HH.MM>" << endl;
						
		break;
	default:
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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


