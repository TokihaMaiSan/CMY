#include <iostream>
#include "colorcodes2.h"
using namespace std;

int main() {
	printf("\033[22;39mHello, world!");

	printf(F_BLACK); cout << "BLACK\n";
	printf(F_DARK_GRAY); cout << "DARK_GRAY\n";
	printf(F_RED); cout << "RED\n";
	printf(F_LIGHT_RED); cout << "LIGHT_RED\n";
	printf(F_GREEN); cout << "GREEN\n";
	printf(F_LIGHT_GREEN); cout << "LIGHT_GREEN\n";
	printf(F_BROWN); cout << "BROWN\n";
	printf(F_YELLOW); cout << "YELLOW\n";
	printf(F_BLUE); cout << "BLUE\n";
	printf(F_LIGHT_BLUE); cout << "LIGHT_BLUE\n";
	printf(F_VIOLET); cout << "VIOLET\n";
	printf(F_LIGHT_VIOLET); cout << "LIGHT_VIOLET\n";
	printf(F_DARK_CYAN); cout << "DARK_CYAN\n";
	printf(F_CYAN); cout << "CYAN\n";
	printf(F_WHITE); cout << "WHITE\n";
	printf(F_GRAY); cout << "GRAY\n";
	printf(F_WHITE); cout << "WHITE\n";
	return 0;
}
