#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>
using namespace std;

#define ALARM '\a'
#define INV_OPT "invalid option"
#define NEVER "you should never reach this line"
#define NONEW true
typedef unsigned short ushort;

class error {
	public:
		error();
		~error();
		void Error(string, string, bool) const;
		void Error(const char*, const char*, bool) const;
};
#endif //ERROR_H
