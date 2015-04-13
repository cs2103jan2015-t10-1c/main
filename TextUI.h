#ifndef TEXTUI_H
#define TEXTUI_H
#include <boost\date_time\gregorian\gregorian.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>

#include<iostream>
#include<string>
#include<vector>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class TextUI{
	private:
		string _commandWord;
		string _content;

		static const string WELCOME_TO_FASTADD;
		static const string CURRENT_VERSION;
		static const string KEY_IN_COMMANDS;
		static const string HELP_FOR_INFORMATION;
		static const string BORDER; 
		static const string WRONG_INPUT;
		static const string DATE_TODAY;
		static const string TIME_STARTED;
		static const string INPUT_COMMAND_NOT_IDENTIFIED;
		static const string CHOOSE_RESIZE_OPTIONS;
		static const string SIZE_SMALL;
		static const string SIZE_LARGE;
		static const string SIZE_DEFAULT;
		static const string YOUR_CHOICE;

	public:
		//@author A0100750Y
		TextUI();
		void displayWelcomeMessage();
		void displayCurrentDateTime();
		void displayHelp();
		void displayResizeOptions();
		TextUI(string&);	
		string findCommand(string&);
        string removeCommand(string&);
        void displayErrorFeedback();
		};
#endif
		
		

