#ifndef ENTER_CPP
#define ENTER_CPP

#include "Enter.h"

/*

	Enter()

	Halts the current Programm and waits for the user to press the enter-button
	(Quite simple, isn't it?) Does anybody need further explanation?

*/
void Enter(bool b) {
	if(b) cin.ignore();
	char c;
	cout << "Press ENTER";
	cin.get(c);
}

#endif //ENTER_CPP
