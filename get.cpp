#include <iostream>
using namespace std;

int main() {
	char a = 'A';
	for(int i = 0; i < 26; i++) {
		cout << "\"" << a++ << "_KEY_SMALL\", ";
	}
	return 0;
}
