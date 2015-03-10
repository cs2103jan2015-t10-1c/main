#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "TextUI.H"

using namespace std;

TextUI::TextUI(){
}

TextUI::TextUI(string &inputContent){
	_content=inputContent;
}

string TextUI::findCommand(string &inputContent){
    string commandWord;
    commandWord = inputContent.substr(0,inputContent.find_first_of(' '));
    return commandWord;
}

string TextUI::removeCommand(string &inputContent){
    inputContent=inputContent.erase(0,inputContent.find_first_of(' '));
    return inputContent;
}
    
void TextUI::displayFeedback(const string infoType){
     if(infoType == "ERROR MESSAGE_1"){
        cout << "WARNING: Input command not identified."<< endl;
    }
}


/*int main(){
    const int END = 0;
    const int RUNNING =1;
    string command,userInput;
    int flag = RUNNING;
    
    while(flag){
            cout << "command: ";
            getline(cin, userInput);
            TextUI task(userInput);
			command=task.findCommand(userInput);
			userInput=task.removeCommand(userInput);
			
			/*int number=1;

            if(command == "add"){
                 task.add(userInput);
            }
            else if(command == "delete"){
                 task.del(number);
            }
            else if(command == "display"){
                 task.display();
            }
            else if(command == "clear"){
                 task.clear();
            }
            else if(command == "exit"){
                flag = END;
            }
            else{
                task.displayFeedback("ERROR MESSAGE_1");
            }
   // }

	/*cout<< command<< " " <<userInput<< endl;
    return 0;
}*/

