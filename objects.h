#ifndef OBJECTS_H
#define OBJECTS_H

// Required system headers

#include <iostream>
#include <termios.h>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include <fstream>

//Comment this one if you don't want to use any colors in the output
#define ENABLE_COLOR

// Required individual headers

#include "limits.h"
#include "debug.h"
#include "DEBUGDEF"
#include "error.h"
#include "define.h"
#include "mygetch.h"
#include "mygetch.cpp"
// #include "ohri.h"
#include "Enter.cpp"
#include "Menu.h"
#include "Menu.cpp"

#ifdef ENABLE_COLOR
#include "colorcodes.h"
#endif //ENABLE_COLOR

// Programm headers

#include "cursor.h"
#include "tile.h"
#include "Mines.h"

// Programm sources

#include "cursor.cpp"
#include "tile.cpp"
#include "Mines.cpp"
using namespace std;

#endif //OBJECTS_H
