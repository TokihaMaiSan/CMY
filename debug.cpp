#ifndef __DEBUG_CPP__
#define __DEBUG_CPP__

#include "debug.h"

debug::debug() {
}

debug::~debug() {
}

void debug::Debug(string msg) const {
	cerr << "-- DEBUG: " << msg << " --\n";
}

#endif //__DEBUG_CPP__
