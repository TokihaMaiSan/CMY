#ifndef CURSOR_CPP
#define CURSOR_CPP

#include "cursor.h"

extern int UP_KEY, DOWN_KEY, RIGHT_KEY, LEFT_KEY, OPEN_FIELD, MARK_FIELD, QUIT_KEY;

cursor::cursor(): initiated(false) {
	focus = NULL;
// 	board = NULL;
	if(Load()) {
		initiated = true;
	}
	else {
	}
}

cursor::~cursor() {
	focus = NULL;
// 	board = NULL;
	Save();
}

void cursor::MoveUp() {
#ifdef DEBUG
	D.Debug("cursor::MoveUp()", ENTER);
#endif //DEBUG
	SetCursor(focus->GetUpper());
// 	if(xpos > 0) {
// 		xpos--;
// 	}
// 	else xpos = MAX_X - 1;
#ifdef DEBUG
	D.Debug("cursor::MoveUp()", EXIT);
#endif //DEBUG
}

void cursor::MoveDown() {
#ifdef DEBUG
	D.Debug("cursor::MoveDown()", ENTER);
#endif //DEBUG
	SetCursor(focus->GetLower());
// 	xpos = (xpos + 1) % MAX_X;
#ifdef DEBUG
	D.Debug("cursor::MoveDown()", EXIT);
#endif //DEBUG
}

void cursor::MoveRight() {
#ifdef DEBUG
	D.Debug("cursor::MoveRight()", ENTER);
#endif //DEBUG
	SetCursor(focus->GetRight());
// 	ypos = (ypos + 1) % MAX_Y;
#ifdef DEBUG
	D.Debug("cursor::MoveRight()", EXIT);
#endif //DEBUG
}

void cursor::MoveLeft() {
#ifdef DEBUG
	D.Debug("cursor::MoveLeft()", ENTER);
#endif //DEBUG
	SetCursor(focus->GetLeft());
// 	if(ypos > 0) {
// 		ypos--;
// 	}
// 	else ypos = MAX_Y - 1;
#ifdef DEBUG
	D.Debug("cursor::MoveLeft()", EXIT);
#endif //DEBUG
}

bool cursor::SetCursor(tile *T) {
	if(!T) {
		return false;
	}
	focus = T;
	return true;
}

// void cursor::SetMAX(int max_x, int max_y) {
// 	MAX_X = max_x;
// 	MAX_Y = max_y;
// }

int cursor::GetXPos() const {
	return focus->GetXPos();
}

int cursor::GetYPos() const {
	return focus->GetYPos();
}

// void cursor::Reset() {
// 	xpos = 0;
// 	ypos = 0;
// }

tile* cursor::GetField() const {
	return focus;
}

bool cursor::Save() const {
	bool success = false;
	error E;
	ofstream oFile;
	oFile.open(CURSOR_SAVE_DIR);
	if(oFile.is_open()) {
		oFile << UP_KEY << '$' << DOWN_KEY << '$' << LEFT_KEY << '$' << RIGHT_KEY << "$\n"
			<< OPEN_FIELD << '$' << MARK_FIELD << '$' << QUIT_KEY << '$';
		oFile.close();
		success = true;
	}
	else {
		string null = "";
// 		E.Error(null.append("couldn\'t open file ").append(CURSOR_SAVE_DIR));
		#ifdef DEBUG
		D.Debug(null.append("couldn\'t open file ").append(CURSOR_SAVE_DIR));
		#endif //DEBUG
		success = false;
	}
	
	return success;
}

bool cursor::Load() {
	bool success = false;
	error E;
	ifstream iFile;
	iFile.open(CURSOR_SAVE_DIR);
	string line = "";
	unsigned int i = 0;
	UP_KEY = 0, DOWN_KEY = 0, LEFT_KEY = 0, RIGHT_KEY = 0, OPEN_FIELD = 0, MARK_FIELD = 0, QUIT_KEY = 0;
	if(iFile.is_open()) {
		for(int j = 0; j < 2; j++) {
			getline(iFile, line);
			switch(j) {
				case 0:
					i = 0;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						UP_KEY *= 10;
						UP_KEY += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("UP_KEY", IS, UP_KEY);
					#endif //DEBUG
					i++;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						DOWN_KEY *= 10;
						DOWN_KEY += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("DOWN_KEY", IS, DOWN_KEY);
					#endif //DEBUG
					i++;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						LEFT_KEY *= 10;
						LEFT_KEY += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("LEFT_KEY", IS, LEFT_KEY);
					#endif //DEBUG
					i++;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						RIGHT_KEY *= 10;
						RIGHT_KEY += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("RIGHT_KEY", IS, RIGHT_KEY);
					#endif //DEBUG
					break;
				case 1:
					i = 0;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						OPEN_FIELD *= 10;
						OPEN_FIELD += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("OPEN_FIELD", IS, OPEN_FIELD);
					#endif //DEBUG
					i++;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						MARK_FIELD *= 10;
						MARK_FIELD += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("MARK_FIELD", IS, MARK_FIELD);
					#endif //DEBUG
					i++;
					for(; line[i] != '$' && line[i] != '\0'; i++) {
						QUIT_KEY *= 10;
						QUIT_KEY += int(line[i]) - 48;
					}
					#ifdef DEBUG
					D.Debug("QUIT_KEY", IS, QUIT_KEY);
					#endif //DEBUG
					break;
				default:
// 					E.Error(NEVER);
					#ifdef DEBUG
					D.Debug("You should never reach this line");
					#endif //DEBUG
					break;
			}
		}
		iFile.close();
		success = true;
	}
	else {
		string null = "";
// 		E.Error(null.append("couldn\'t open file ").append(CURSOR_SAVE_DIR));
		#ifdef DEBUG
		D.Debug((null.append("couldn\'t open file ").append(CURSOR_SAVE_DIR)););
		#endif //DEBUG
		success = false;
	}
	
	return success;
}

// void cursor::ChangeKeys() {
// 	bool ok = false;
// 	while(!ok) {
// 		cout << "Press ENTER to change key\n";
// 		cout << "UP_KEY [" << getKeyName(UP_KEY) << "]\n";
// 		cout << "DOWN_KEY [" << getKeyName(DOWN_KEY) << "]\n";
// 		cout << "LEFT_KEY [" << getKeyName(LEFT_KEY) << "]\n";
// 		cout << "RIGHT_KEY [" << getKeyName(RIGHT_KEY) << "]\n";
// 		cout << "OPEN_FIELD [" << getKeyName(OPEN_FIELD) << "]\n";
// 		cout << "MARK_FIELD [" << getKeyName(MARK_FIELD) << "]\n";
// 		cout << "QUIT_KEY [" << getKeyName(QUIT_KEY) << "]\n";
// 		break;	//TODO: for now
// 	}
// }

// string cursor::getKeyName(unsigned short key) const {
// 	return keyNames[key];
// }

#endif //CURSOR_CPP
