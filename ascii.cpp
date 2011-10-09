#include <iostream>
using namespace std;

int main() {
	wchar_t *c = L"0";
	for(int i = 0; !i || c; i++, c++) {
		cout << i << ": " << c << endl;
	}
	return 0;
}
