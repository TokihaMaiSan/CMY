#ifndef TILE_H
#define TILE_H

#include <iostream>
#ifndef USHRT_MAX
#include "limits.h"
#endif //USHRT_MAX
using namespace std;

enum STATE{NOT_DEFINED = 0, COVERED, MARKED, UNCOVERED, MARKED_RIGHT, MARKED_FALSE, EXPLODED, PROTECTED};

class tile {
	bool bomb;	//is this tile a bomb?
	unsigned short state, xpos, ypos, value; //Value contains the number of bombs that are set in the neighbouring tiles
	tile *UpperLeft, *Upper, *UpperRight, *Left, *Right, *LowerLeft, *Lower, *LowerRight;

	void Init(bool);

	public:
		tile();
		~tile();
		void SetBomb();	//Sets tile to bomb
		void UnSetBomb();	//Unsets any bomb on this tile
		void SetState(STATE);	//sets state
		void IncrBombs();	//increase number of bombs that are lying on neighbouring tiles
		void Reset();
		bool GetBomb() const;
		unsigned short GetState() const;
		unsigned short GetValue() const;
		tile& operator++();
		tile operator++(int);
		bool operator==(const tile) const;
		bool operator!=(const tile) const;
		void SetUpperLeft(tile*);
		void SetUpper(tile*);
		void SetUpperRight(tile*);
		void SetLeft(tile*);
		void SetRight(tile*);
		void SetLowerLeft(tile*);
		void SetLower(tile*);
		void SetLowerRight(tile*);
		tile* GetUpperLeft() const;
		tile* GetUpper() const;
		tile* GetUpperRight() const;
		tile* GetLeft() const;
		tile* GetRight() const;
		tile* GetLowerLeft() const;
		tile* GetLower() const;
		tile* GetLowerRight() const;
		void SetXPos(unsigned short);
		void SetYPos(unsigned short);
		unsigned short GetXPos() const;
		unsigned short GetYPos() const;
};

#endif //TILE_H
