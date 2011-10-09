/*

	Mines v0.5:
	Look in TODOlist for a changelog and a list of upcoming functions

*/

#ifndef MINES_H
#define MINES_H

#include "operating_system"

#ifdef __UNIX__
#include <termios.h>
#define ENABLE_COLOR
#endif //__UNIX__

#include "tile.h"
#include "cursor.h"
#include "Enter.h"
#include "Menu.h"

#define NOTHING 0
#define BOMB_DIVISOR 5
#define MIN_SIZE 3
#define STD_HEIGHT 10
#define STD_WIDTH 10

#define DATA_SAVE_DIR "$HOME/.mines/gamedata"

using namespace std;

typedef unsigned int usint;
enum GAMESTATE {CONTINUE = 0, WIN, FAIL, MANUAL_END};

class Mines {
	private:
		tile **board;
		cursor focus;
		unsigned int covered_tiles;
		unsigned short height, width, bombs, bombs_checked, wins, losses;
		signed short game_state;
		bool initiated, first_time;

		void Create();
		void Destroy();
		void CalcValues();
		void SetMines();
		void CoverUp();
		void SetGameState(unsigned short);
		void Draw() const;
		void UnCover(tile*);
		void MarkBomb(tile*);
		void CheckGameState();
		int MinesMenu();
		void ConnectTiles();
		void RevealMines();
		bool Save() const;
		bool Load();
	public:
		Mines();
		~Mines();
		void Init(unsigned int, unsigned int, unsigned int);
		int GameCore();
// 		unsigned short GetHeight() const;
// 		unsigned short GetWidth() const;
};

#endif //MINES_H
