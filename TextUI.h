#ifndef TEXTUI_H
#define TEXTUI_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class TextUI{
	private:
		string _commandWord;
		string _content;

	public:
		TextUI();
		TextUI(string &inputContent);	
		string findCommand(string &inputContent);
        string removeCommand(string &inputContent);
        void displayFeedback(const string infoType);
		/*string add(string);*/
		/*void display();
		void clear();*/
		};
#endif
		
		

