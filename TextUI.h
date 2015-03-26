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

	public:
		TextUI();
		void displayWelcomeMessage();
		void displayCurrentDateTime();
		void displayHelp();
		TextUI(string &inputContent);	
		string findCommand(string &inputContent);
        string removeCommand(string &inputContent);
        void displayFeedback(const string infoType);
		};
#endif
		
		

