#include "Main.h"
#include <windows.h>
#include<stdio.h>


int main(){
	HWND hWnd=GetConsoleWindow();
    MoveWindow(hWnd,400,0,520,750,TRUE);
	Main RunFA;
	RunFA.readPath();
	RunFA.welcomeMessage();
	RunFA.loadScheduledEntries();
	RunFA.loadFloatingEntries();
	RunFA.operateFastAdd();
	system("pause");
	return 0;
}