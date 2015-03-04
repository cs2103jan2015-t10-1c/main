#include "DataStructure.h"

using namespace std;

int main(){
	DataStructure helloworld;
	helloworld.createContent("bisma", helloworld.newDate(2, 3, 1980), 100, 500);
	helloworld.createContent("hawe", helloworld.newDate(3, 4, 1995), 100, 300);
	helloworld.display();
	system("pause");
	return 0;
}