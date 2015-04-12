#include "Main.h"
#include <windows.h>
#include<stdio.h>


int main(){
	HWND hWnd=GetConsoleWindow();
    MoveWindow(hWnd,400,50,500,700,TRUE);
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