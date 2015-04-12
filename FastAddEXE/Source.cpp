#include "Main.h"
#include <windows.h>
#include<stdio.h>

//@author A0116660L
int main(){
	HWND hWnd=GetConsoleWindow();
    MoveWindow(hWnd,400,50,500,700,TRUE); //set a fixed position and size for the command prompt window
	Main RunFA;
	RunFA.readPath();
	RunFA.welcomeMessage();
	RunFA.readPath();
	RunFA.loadScheduledEntries();
	RunFA.loadFloatingEntries();
	RunFA.operateFastAdd();
	system("pause");
	return 0;
}