#include "DataStructure.h"

using namespace std;

int main(){
	DataStructure helloworld;
	helloworld.createContent("bisma", 1, 100, 500);
	helloworld.createContent("hawe", 2, 100, 300);
	helloworld.display();
	system("pause");
	return 0;
}