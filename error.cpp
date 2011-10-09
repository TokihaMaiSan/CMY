#ifndef ERROR_CPP
#define ERROR_CPP

#include "error.h"

error::error() {
}

error::~error() {
}

void error::Error(string str, string cont = "", bool nonewline = false) const {
	cout << ALARM << "\n-- ERROR" << ": " << str << " " << cont << " --";
	if(!nonewline) cout << endl;
}

void error::Error(const char* str, const char* cont = "", bool nonewline = false) const {
	cout << ALARM << "\n-- ERROR" << ": " << str << " " << cont << " --";
	if(!nonewline) cout << endl;
}

#endif //ERROR_CPP
