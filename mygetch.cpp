#ifndef MYGETCH_CPP
#define MYGETCH_CPP

#include "mygetch.h"

int UP_KEY, DOWN_KEY, RIGHT_KEY, LEFT_KEY, OPEN_FIELD, MARK_FIELD, QUIT_KEY;

getch::getch() {
	ifstream iFile;
	iFile.open(DEFAULT_KEY_SAVE_LOCATION);
	if(iFile.is_open()) {
#ifdef DEBUG
		string null = "";
		D.Debug(null.append("Opened File ").append(DEFAULT_KEY_SAVE_LOCATION), IF);
#endif //DEBUG
		iFile.close();
	}
	else {
#ifdef DEBUG
		string null = "";
		D.Debug(null.append("Could not open File ").append(DEFAULT_KEY_SAVE_LOCATION).append(" using default keys"), IF);
#endif //DEBUG
		UP_KEY = UP_ARROW;
		DOWN_KEY = DOWN_ARROW;
		RIGHT_KEY = RIGHT_ARROW;
		LEFT_KEY = LEFT_ARROW;
		OPEN_FIELD = ENTER_KEY;
		MARK_FIELD = B_KEY_SMALL;
		QUIT_KEY = Q_KEY_SMALL;
	}
}

getch::~getch() {
}

int getch::mygetch() const {
#ifdef DEBUG
	D.Debug("getch::mygetch()", ENTER);
#endif
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#ifdef DEBUG
	D.Debug("getch::mygetch()", EXIT, ch);
#endif
	return ch;
}

int getch::GetKey() const {
#ifdef DEBUG
	D.Debug("getch::GetKey()", ENTER);
#endif
	int temp = 0;
	do{
		temp = mygetch();
	} while(temp == 27 || temp == 91);
#ifdef DEBUG
	D.Debug("temp", IS, temp);
	D.Debug("int(temp)", IS, int(temp));
#endif
#ifdef DEBUG
	D.Debug("getch::GetKey()", EXIT, temp);
#endif
	return temp;
}

// string getch::GetKeyName(unsigned short key) const {
// 	return keyNames[key];
// }

#endif //MYGETCH_CPP
