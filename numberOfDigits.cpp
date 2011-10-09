#ifndef NUMBER_OF_DIGITS_CPP
#define NUMBER_OF_DIGITS_CPP

#include "numberOfDigits.h"

unsigned short numberOfDigits(int number) {
	int i = 0;
	#ifdef DEBUG
	cout << "numberOfDigits(int): variable number (value: " << number << ") has ";
	#endif //DEBUG
	for(; number; i++) number /= 10;
	#ifdef DEBUG
	cout << i << " digits\n";
	#endif //DEBUG
	return i;
}

#endif //NUMBER_OF_DIGITS_CPP
