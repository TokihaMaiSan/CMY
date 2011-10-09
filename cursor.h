#ifndef CURSOR_H
#define CURSOR_H

// #include "objects.h"
#include <iostream>
#include <string>
using namespace std;

#include "tile.h"
#include "mygetch.h"
#include "error.h"

#define CURSOR_SAVE_DIR "keys"

// class tile;
// class Mines;

class cursor {
	tile *focus;
	bool initiated;

	public:
		cursor();
		~cursor();
		void MoveUp();
		void MoveDown();
		void MoveRight();
		void MoveLeft();
		bool SetCursor(tile*);
		int GetXPos() const;
		int GetYPos() const;
		tile* GetField() const;
		bool Save() const;
		bool Load();
// 		void ChangeKeys();
// 		string getKeyName(short unsigned) const;
};

#endif //CURSOR_H
