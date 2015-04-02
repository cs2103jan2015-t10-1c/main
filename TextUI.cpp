//3.34am

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "TextUI.h"

const string TextUI::WELCOME_TO_FASTADD = "Welcome to FastAdd";
const string TextUI::CURRENT_VERSION = "version v0.2";
const string TextUI::KEY_IN_COMMANDS = "Please key in your commands";
const string TextUI::HELP_FOR_INFORMATION = "Type 'help' for information on how to use FastAdd";

TextUI::TextUI(){
}

TextUI::TextUI(string& inputContent){
	_content = inputContent;
}

void TextUI::displayWelcomeMessage(){
	cout << WELCOME_TO_FASTADD << endl
		<< CURRENT_VERSION << endl
		<< KEY_IN_COMMANDS << endl
		<< HELP_FOR_INFORMATION << endl
		<< endl;
}

void TextUI::displayCurrentDateTime(){
	date d(day_clock::local_day());
	ptime t(second_clock::local_time());
	cout << "The date today is " << t.date() << endl
		<< "and the time when FastAdd starts was " << t.time_of_day() << endl
		<< endl;
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
			<< "or - add <even name>. <HH.MM> <HH.MM> on <DD Month YYYY> at <location> #<tag>" << endl;
		break;
	case 2:
		cout << "2. Display - display" << endl;
		break;
	case 3:
		cout << "3. Delete - delete <entry number>" << endl;
		break;
	case 4:
		cout << "4. Edit - edit <entry number> -n <new name> or -t <HH.MM> <HH.MM> or -d <DD Month YYYY> or -l <new location>" << endl;
		break;
	case 5:
		cout << "5. Search - search <keyword>" << endl;
		break;
	default:
		cout << "Wrong input. Try again";
		break;
	}
}

string TextUI::findCommand(string& inputContent){
    string commandWord;
    commandWord = inputContent.substr(0,inputContent.find_first_of(' '));
    return commandWord;
}

string TextUI::removeCommand(string& inputContent){
    inputContent=inputContent.erase(0,inputContent.find_first_of(' '));
    return inputContent;
}
    
void TextUI::displayErrorFeedback(){
	cout << "Input command not identified. Please try again."<< endl;
}


