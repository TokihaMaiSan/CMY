#include "tile.h"

class GameBoard {
	unsigned int height, width;
	tile *focus;
	cursor focus;
	
	public:
		GameBoard(int, int);
		GameBoard(const GameBoard&);
		~GameBoard();
		
		void Draw() const;
		void UnCover(tile*);
		void MarkBomb(tile*);
		void ConnectTiles();
}