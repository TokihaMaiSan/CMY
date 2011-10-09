#include <iostream>
using namespace std;
#include "mygetch.h"

int main() {
	bool ok = true;
	int key = 0;
	getch G;
	while(ok) {
		key = G.GetKey();
		if(char(key) == 'q') {
			ok = false;
		}
		cout << key << " = " << char(key) << endl;
	}
	return 0;
}
