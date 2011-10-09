#ifndef TILE_CPP
#define TILE_CPP

#include "tile.h"

tile::tile() {
#ifdef DEBUG
	D.Debug("Constructor tile::tile()", ENTER);
#endif //DEBUG
	Init(false);
	UpperLeft = NULL;
	Upper = NULL;
	UpperRight = NULL;
	Left = NULL;
	Right = NULL;
	LowerLeft = NULL;
	Lower = NULL;
	LowerRight = NULL;
#ifdef DEBUG
	D.Debug("Constructor tile::tile()", EXIT);
#endif //DEBUG
}

tile::~tile() {
#ifdef DEBUG
	D.Debug("Destructor tile::~tile()", ENTER);
#endif //DEBUG
	UpperLeft = NULL;
	Upper = NULL;
	UpperRight = NULL;
	Left = NULL;
	Right = NULL;
	LowerLeft = NULL;
	Lower = NULL;
	LowerRight = NULL;
#ifdef DEBUG
	D.Debug("Destructor tile::~tile()", EXIT);
#endif //DEBUG
}

void tile::Init(bool B) {
#ifdef DEBUG
	D.Debug("void tile::Init(bool)", ENTER);
#endif //DEBUG
	bomb = B;
	state = COVERED;
	value = 0;
#ifdef DEBUG
	D.Debug("void tile::Init(bool)", EXIT);
#endif //DEBUG
}

void tile::SetBomb() {
#ifdef DEBUG
	D.Debug("void tile::SetBomb()", ENTER);
#endif //DEBUG
	bomb = true;
#ifdef DEBUG
	D.Debug("Set bomb to true");
#endif //DEBUG
#ifdef DEBUG
	D.Debug("void tile::SetBomb()", EXIT);
#endif //DEBUG
}

void tile::UnSetBomb() {
#ifdef DEBUG
	D.Debug("void tile::UnSetBomb()", ENTER);
#endif //DEBUG
	bomb = false;
#ifdef DEBUG
	D.Debug("Set bomb to false");
#endif //DEBUG
#ifdef DEBUG
	D.Debug("void tile::UnSetBomb()", EXIT);
#endif //DEBUG
}

void tile::SetState(STATE S) {
#ifdef DEBUG
	D.Debug("void tile::SetState(STATE)", ENTER, S);
#endif //DEBUG
	state = S;
#ifdef DEBUG
	D.Debug("void tile::SetState(STATE)", EXIT);
#endif //DEBUG
}

void tile::IncrBombs() {
#ifdef DEBUG
	D.Debug("void tile::IncrBombs()", ENTER);
#endif //DEBUG
	if(value < USHRT_MAX) {
		value++;
#ifdef DEBUG
		D.Debug("value increased to", NOSTAT, value);
#endif //DEBUG
	}
#ifdef DEBUG
	D.Debug("void tile::IncrBombs()", EXIT);
#endif //DEBUG
}

void tile::Reset() {
#ifdef DEBUG
	D.Debug("void tile::Reset()", ENTER);
#endif //DEBUG
	Init(false);
#ifdef DEBUG
	D.Debug("void tile::Reset()", EXIT);
#endif //DEBUG
}

bool tile::GetBomb() const {
#ifdef DEBUG
	D.Debug("bool tile::GetBomb()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("bool tile::GetBomb()", EXIT);
#endif //DEBUG
	return bomb;
}

unsigned short tile::GetState() const {
#ifdef DEBUG
	D.Debug("unsigned short tile::GetState()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("unsigned short tile::GetState()", EXIT);
#endif //DEBUG
	return state;
}

unsigned short tile::GetValue() const {
#ifdef DEBUG
	D.Debug("unsigned short tile::GetValue()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("unsigned short tile::GetValue()", EXIT);
#endif //DEBUG
	return value;
}

tile& tile::operator++() {
#ifdef DEBUG
	D.Debug("tile& tile::operator++()", ENTER);
#endif //DEBUG
	IncrBombs();
#ifdef DEBUG
	D.Debug("tile& tile::operator++()", EXIT);
#endif //DEBUG
	return *this;
}

tile tile::operator++(int) {
#ifdef DEBUG
	D.Debug("tile tile::operator++(int)", ENTER);
#endif //DEBUG
	tile oldtile = *this;
	IncrBombs();
#ifdef DEBUG
	D.Debug("tile tile::operator++(int)", EXIT);
#endif //DEBUG
	return oldtile;
}

bool tile::operator==(const tile T) const {
	bool same = true;
	if(T.GetBomb() != bomb) same = false;
	else if(T.GetValue() != value) same = false;
	else if(T.GetState() != state) same = false;
	return same;
}

bool tile::operator!=(const tile T) const {
	return !(*this == T);
}

void tile::SetUpperLeft(tile *T) {
	UpperLeft = T;
}

void tile::SetUpper(tile *T) {
	Upper = T;
}

void tile::SetUpperRight(tile *T) {
	UpperRight = T;
}

void tile::SetLeft(tile *T) {
	Left = T;
}

void tile::SetRight(tile *T) {
	Right = T;
}

void tile::SetLowerLeft(tile *T) {
	LowerLeft = T;
}

void tile::SetLower(tile *T) {
	Lower = T;
}

void tile::SetLowerRight(tile *T) {
	LowerRight = T;
}

tile* tile::GetUpperLeft() const {
#ifdef DEBUG
	D.Debug("tile::GetUpperLeft()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetUpperLeft()", EXIT);
#endif //DEBUG
	return UpperLeft;
}

tile* tile::GetUpper() const {
#ifdef DEBUG
	D.Debug("tile::GetUpper()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetUpper()", EXIT);
#endif //DEBUG
	return Upper;
}

tile* tile::GetUpperRight() const {
#ifdef DEBUG
	D.Debug("tile::GetUpperRight()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetUpperRight()", EXIT);
#endif //DEBUG
	return UpperRight;
}

tile* tile::GetLeft() const {
#ifdef DEBUG
	D.Debug("tile::GetLeft()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetLeft()", EXIT);
#endif //DEBUG
	return Left;
}

tile* tile::GetRight() const {
#ifdef DEBUG
	D.Debug("tile::GetRight()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetRight()", EXIT);
#endif //DEBUG
	return Right;
}

tile* tile::GetLowerLeft() const {
#ifdef DEBUG
	D.Debug("tile::GetLowerLeft()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetLowerLeft()", EXIT);
#endif //DEBUG
	return LowerLeft;
}

tile* tile::GetLower() const {
#ifdef DEBUG
	D.Debug("tile::GetLower()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetLower()", EXIT);
#endif //DEBUG
	return Lower;
}

tile* tile::GetLowerRight() const {
#ifdef DEBUG
	D.Debug("tile::GetLowerRight()", ENTER);
#endif //DEBUG
#ifdef DEBUG
	D.Debug("tile::GetLowerRight()", EXIT);
#endif //DEBUG
	return LowerRight;
}

void tile::SetXPos(unsigned short X) {
	xpos = X;
}

void tile::SetYPos(unsigned short Y) {
	ypos = Y;
}

unsigned short tile::GetXPos() const {
	return xpos;
}

unsigned short tile::GetYPos() const {
	return ypos;
}

#endif //TILE_CPP
