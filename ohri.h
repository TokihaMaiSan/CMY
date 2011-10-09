/*

	ohri.h
	by Setsuna

	Library of many useful functions that just crossed my way while intensive programming sessions... (well some of them aren't that great...)

	Version History:

	Vers. 0.5:
		- inserted:
			- int absolute_value(int);
			- short absolute_value(short);
			- double absolute_value(double);
			- float absolute_value(float);

	Vers. 0.4:
		- inserted the following:
			- UpCase(char)
			- LowCase(char)
			- StrLen(string)
			- WasteSeconds(ushort)
			- trim(char*)
			- mygetch()
		- sure there are those functions in the Standard Library (first three), but I just couldn't resist implementing them myself. Doesn't mean anybody has to use them...
		- WasteSeconds: I'm quite sure I saw something like that somewhere in a tutorial but as it was hard to find the second time I just did my own version. I wonder which is faster? (Doesn't really matter here, does it?)
		- trim: had the need for it a short while ago but that was it. Guess it will wander into a header by itself the next time I use it.
		- mygetch: after years of searching... well actually it is nearly a year... and  havn't been searching all the time... I sure would have found it sooner... Whatever. Finally I got a function that waits for the user to enter ANY key. (Phew... what a great step for mankind that was...)
		- modified menue(): works now with mygetch(). Furthermore I made it dependent on a valid option if user may return instead of choosing from the menu. It now throws an error-message if no valid option has been set. Thus I made it possible to simply add new ways of returning from a function... (as if there were that many)

	Vers. 0.3:
		- took out error() and created error.h with class error

	Vers. 0.2:
		- added Enter()
		- added menue(string[], int, int)
		- added global enum to menue(string[], int, int)
		- added error(string, int)
		- took out StatusBar and made it a single header

	Vers. 0.1:
		- added StatusBar(double)

*/

#ifndef OHRI_H
#define OHRI_H

#define NODEBUG

typedef unsigned short ushort;
typedef unsigned long ulong;

#include <iostream>
#include <string>
#include <time.h>
#include <termios.h>
#include <cstdlib>
#include "define.h"
#include "debug.h"
#include "error.h"
using namespace std;

//Declarations
void Enter(bool);
unsigned short menue(string[], int, int);
char UpCase(char);
char LowCase(char);
ushort StrLen(string);
ushort StrLen(char*);
string StrCpy(string, string);
string StrCpy(char*, string);
void WasteSeconds(ushort);
void trim(char*);
int mygetch();
int absolute_value(int);
short absolute_value(short);
double absolute_value(double);
float absolute_value(float);

/*

	Enter()

	Halts the current Programm and waits for the user to press the enter-button
	(Quite simple, isn't it?) Does anybody need further explanation?

*/
void Enter(bool b = false) {
	if(b) cin.ignore();
	char c;
	cout << "Press ENTER";
	cin.get(c);
}

/*

	menue(string[], int, int)

	takes an array of strings and an integer. the strings are to be displayed as a menue list, and the first integer checks the Size. The second integer is optional. it only knows if you want to add an entry to the list that offers the user a return-option. If you ignore it, it will do nothing

*/
enum MENU {NONE, END, BACK};
#define NOT_USED 6

unsigned short menue(string str[], int Size, int End = NONE) {
	ushort InPut;
	ushort Max = 7;
	getch G;

	//Amount of entries
// 	ushort Size = sizeof(str) / sizeof(string);
#ifdef DEBUG
	cout << "-- DEBUG: menue(): Size = " << Size << " --\n";
	cout << "-- DEBUG: str[0] = " << str[0] << " --\n";
	cout << "-- DEBUG: str[1] = " << str[1] << " --\n";
#endif

	//length of each entry
	ushort Sizes[Size];

	//check for the longest string
	for(int i = 0; i < Size; i++) {
		int j = 0;

		//increment j as long as the end of the current string hasn't been reached
		for(; str[i][j] != '\0'; j++);

		//record the sizes of every strings
		Sizes[i] = j;

		//if current string is longer than any previous, set Max to length of current string
		if(Sizes[i] > Max) Max = Sizes[i];
	}

#ifdef DEBUG
	cout << "Sizes:\n";
	for(int i = 0; i < Size; i++) {
		cout << '[' << i << "] " << Sizes[i] << endl;
	}
	cout << "Max: " << Max << endl;
#endif

	//print the first line of the menue-box
	cout << '*';
	for(int i = 0; i < Max + NOT_USED; i++) {
		cout << '*';
	}
	cout << '*' << endl << '*';

	//print the second line of the menue-box
	for(int i = 0; i < Max + NOT_USED; i++) {
		cout << spc;
	}
	cout << '*' << endl;

	//as long as there are still strings in the array, continue
	for(int i = 0; i < Size; i++) {

		//displays each string in a formatted kind
		cout << "* [" << i + 1 << "] " << str[i];

		//as long as current string is shorter than max, print spaces
		for(; Max - Sizes[i]; Sizes[i]++) cout << spc;
		cout << " *\n";
	}

	//if programmer chose to add a return-option, enter
	if(End) {

		//add an extra free line before the return option
		cout << '*';
		for(int i = 0; i < Max + NOT_USED; i++) {
			cout << spc;
		}
		cout << '*' << endl;

		//if return-option END has been chosen display the appropriate message
		if(End == END) {
			cout << "* [0] Beenden";
			for(int i = 0; Max - NOT_USED - i; i++) cout << spc;
			cout << "*\n";
		}

		//if any other option has been chosen display the appropriate message
		else if(End == BACK) {
			cout << "* [0] zurueck ";
			for(int i = 0; Max - NOT_USED - i; i++) cout << spc;
			cout << "*\n";
		}

		else {
			error("unvalid return option");
		}
	}

	//print line before last
	cout << '*';
	for(int i = 0; i < Max + NOT_USED; i++) {
		cout << spc;
	}

	//print last line
	cout << '*' << endl << '*';
	for(int i = 0; i < Max + NOT_USED; i++) {
		cout << '*';
	}
	cout << '*' << endl;

	cout << "\n>>> ";

	//check the users choice
	InPut = G.GetKey() - 48;
// 	cin >> InPut;		//Old version were user had to press enter

	//return his choice to the calling function
	return InPut; //New version, use only if getchar() works without trouble

}

//returns the upper case of a character
char UpCase(char letter) {
	for(char ch = 'a', CH = 'A'; ch <= 'z' && CH <= 'Z'; ch++, CH++) {
		if(letter == ch || letter == CH) return CH;
	}
}

//returns the lower case of a character
char LowCase(char letter) {
	for(char ch = 'a', CH = 'A'; ch <= 'z' && CH <= 'Z'; ch++, CH++) {
		if(letter == ch || letter == CH) return ch;
	}
}

//returns the length of a given string
ushort StrLen(string str) {
	ushort i = 0;
	for(; str[i] != '\0'; i++);
	return i;
}

ushort StrLen(char* str) {
	ushort i = 0;
	for(; str[i] != '\0'; i++);
	return i;
}

// string StrCpy(string strSource, string strGoal) {
// 	string tempStr(StrLen(strSource));
// 	for(int i = 0; strSource[i] != NULC && strGoal[i] != NULC; i++) {
// 		strGoal[i] = strSource[i];
// 	}
// 	return strGoal;
// }
//
// string StrCpy(char* strSource, string strGoal) {
// 	string tempStr(StrLen(strSource));
// 	for(int i = 0; strSource[i] != NULC && strGoal[i] != NULC; i++) {
// 		strGoal[i] = strSource[i];
// 	}
// 	return strGoal;
// }

/*

	WasteSeconds(ushort)

	This takes an unsigned short integer and counts down the amount in seconds. then it will end and the calling function resumes

*/

void WasteSeconds(ushort seconds) {
	time_t now = time(NULL);
	for(; seconds;) {
		if(now != time(NULL)) {
			seconds--;
			now = time(NULL);
		}
	}
}

void trim(char* str) {
	char *first = str, *second = str;
	for(int i = 0; str[i] == ' ' || str[i] == '\0' || str[i] == '\t' || str[i] == '\n'; i++, (*second)++);
	for(; *second != '\0' && *first != *second; (*first)++, (*second)++) {
		*first = *second;
	}
	for(; *second == '\0' || *second == ' ' || *second == '\t' || *second == '\n'; (*second)--);
	++(*second) = '\0';
}

//Gets a single character from the keyboard without waitin for the enter-key and returns its value
//TODO: figure out what EXACTLY this one does
// int mygetch() {
// #ifdef DEBUG
// 	D.Debug("mygetch()", ENTER);
// #endif
// 	struct termios oldt, newt;
// 	int ch;
// 	tcgetattr(STDIN_FILENO, &oldt);
// 	newt = oldt;
// 	newt.c_lflag &= ~(ICANON | ECHO);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
// 	ch = getchar();
// 	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
// #ifdef DEBUG
// 	D.Debug("mygetch()", EXIT, ch);
// #endif
// 	return ch;
// }

int absolute_value(int V) {
	if(V < 0) return -V;
	else return V;
}

short absolute_value(short V) {
	if(V < 0) return -V;
	else return V;
}

double absolute_value(double V) {
	if(V < 0) return -V;
	else return V;
}

float absolute_value(float V) {
	if(V < 0) return -V;
	else return V;
}

#endif //OHRI_H
