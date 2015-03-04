#include "DataStructure.h"

using namespace std;

int main(){
	DataStructure helloworld;
	helloworld.createContent("bisma", helloworld.newDate(2, 3, 1980), helloworld.newTime(20, 30));
	helloworld.createContent("hawe", helloworld.newDate(3, 4, 1995), helloworld.newTime(10, 40));
	helloworld.display();
	system("pause");
	return 0;
}