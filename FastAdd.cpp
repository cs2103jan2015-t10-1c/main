#include "Main.h"

int main(){
	Main RunFA;
	RunFA.welcomeMessage();
	RunFA.loadScheduledEntries();
	RunFA.loadFloatingEntries();
	RunFA.operateFastAdd();
	return 0;
}