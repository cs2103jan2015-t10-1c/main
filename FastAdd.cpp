#include "Main.h"

int main(){
	Main RunFA;
	RunFA.welcomeMessage();
	RunFA.readPath();
	RunFA.loadScheduledEntries();
	RunFA.loadFloatingEntries();
	RunFA.operateFastAdd();
	system("pause");
	return 0;
}