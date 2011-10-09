#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "colorcodes.h"
#include "mygetch.h"
// #include "cursor.h"
#include "error.h"
#include "numberOfDigits.h"

#define NODEBUG
#ifdef DEBUG
#include "debug.h"
#endif

#define DECO_BEFORE "* "
#define DECO_AFTER " *"
#define DECO_BEFORE_SIZE 2
#define DECO_AFTER_SIZE 2
using namespace std;

enum RETURN_STATE {NONE = 0, BACK, END};

class Menu {
	string *str;
	unsigned int count, current;
	unsigned short MAX, LENGTH, NUMBERING_SPACE, End;
	getch key;

	bool Print() const;

	public:
		Menu();
		~Menu();
		void Set(string*, unsigned int, unsigned short);
		unsigned int GetChoice();
};

#endif //MENU_H
