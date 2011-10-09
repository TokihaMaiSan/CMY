#include <iostream>
#include "Menu.cpp"
using namespace std;

int main() {
	Menu M;
	string mainString[] = {"Test1", "Test2", "Test3", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest", "NochnTest"};
	M.Set(mainString, sizeof(mainString) / sizeof(string), END);
	int choice = M.GetChoice();
	cout << choice << endl;
	return 0;
}
