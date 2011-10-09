#include <iostream>
#include <string>
using namespace std;

int main() {
	string InPut;
	cout << "Bitte 2 Zahlen und ein B eingeben: ";
	getline(cin, InPut, '\n');
	cout << "|" << InPut[0] << '\v' << "test";
}
