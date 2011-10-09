#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"

extern int UP_KEY, DOWN_KEY, RIGHT_KEY, LEFT_KEY, OPEN_FIELD, MARK_FIELD, QUIT_KEY;

Menu::Menu(): count(0), current(0), MAX(7), LENGTH(0), NUMBERING_SPACE(0) {
	str = NULL;
}

Menu::~Menu() {
	if(str) {
		str = NULL;
	}
}

void Menu::Set(string *S, unsigned int C, unsigned short _End = NONE) {
	#ifdef DEBUG
	D.Debug("Menu::Set(string*, unsigned int)", ENTER, C);
	#endif //DEBUG
	str = S;
	count = C;
	End = _End;
	MAX = 7;

	//Calulating the maximum length of the longest string
	for(unsigned int i = 0; i < count; i++) {
		if(str[i].length() > MAX) {
			MAX = str[i].length();
		}
	}

	NUMBERING_SPACE = numberOfDigits(count) + 3;

	LENGTH = DECO_BEFORE_SIZE + NUMBERING_SPACE + MAX + DECO_AFTER_SIZE;
	#ifdef DEBUG
	D.Debug("MAX", IS, MAX);
	D.Debug("count", IS, count);
	D.Debug("LENGTH", IS, LENGTH);
	#endif //DEBUG
	#ifdef DEBUG
	D.Debug("Menu::Set(string*, unsigned int)", EXIT);
	#endif //DEBUG
}

bool Menu::Print() const {
	unsigned short difference = 0;
	if(!MAX) {
// 		E.Error("MAX ist null!");
		#ifdef DEBUG
		D.Debug("MAX ist null!");
		#endif //DEBUG
		return false;
	}
	else {
		#ifdef __UNIX__
		system("clear");
		#endif //__UNIX__
		#ifdef __WINDOWS__
		system("cls");
		#endif //__WINDOWS__
		//Printing the first deco line
		for(int i = 0; i < LENGTH; i++) {
			cout << '*';
		}
		cout << endl;

		//Printing second deco line
		cout << DECO_BEFORE;
		for(int i = 0; i < MAX + NUMBERING_SPACE; i++) {
			cout << ' ';
		}
		cout << DECO_AFTER << endl;

		//Printing menu entries
		for(unsigned int i = 0; i < count; i++) {
			cout << DECO_BEFORE;

			if(i == current) {
				printf(F_LIGHT_RED);
			}

			cout << '[' << i + 1 << "] " << str[i];

			//Printing fillers for the shorter entries
			difference = MAX - str[i].length() + numberOfDigits(count) - numberOfDigits(i + 1);
			for(int j = 0; j < difference; j++) cout << ' ';

			if(i == current) {
				printf(F_WHITE);
			}

			cout << DECO_AFTER << endl;
		}

		//Checking if the menu should have a return entry
		if(End) {
			//Printing an extra empty line
			cout << DECO_BEFORE;
			for(int i = 0; i < MAX + NUMBERING_SPACE; i++) {
				cout << ' ';
			}
			cout << DECO_AFTER << endl;

			//Printing the return entry
			cout << DECO_BEFORE;

			if(current == count + 1) {
				printf(F_LIGHT_RED);
			}

			cout << "[0] " << (End == END ? "Beenden" : "Zurueck");

			//Printing fillers for the shorter entries
			difference = MAX - 7 + numberOfDigits(count) - numberOfDigits(1);
			for(int j = 0; j < difference; j++) cout << ' ';

			if(current == count + 1) {
				printf(F_WHITE);
			}

			cout << DECO_AFTER << endl;
		}

		//Printing second to last deco line
		cout << DECO_BEFORE;
		for(int i = 0; i < MAX + NUMBERING_SPACE; i++) {
			cout << ' ';
		}
		cout << DECO_AFTER << endl;

		//Printing the last deco line
		for(int i = 0; i < LENGTH; i++) {
			cout << '*';
		}
		cout << endl;
	}
	return true;
}

unsigned int Menu::GetChoice() {
	unsigned int choice = 0;
	bool chosen = false;
	unsigned short K = 0;
	do {
		Print();
		K = key.GetKey();
		if(K == ENTER_KEY) {
			#ifdef DEBUG
			cout << "Chosing " << current << endl;
			#endif //DEBUG
			if(current == count + 1) {
				choice = 0;
			}
			else {
				choice = current + 1;
			}
			chosen = true;
		} else if(K == UP_ARROW || K == LEFT_ARROW) {
			#ifdef DEBUG
			cout << "Moving up\n";
			#endif //DEBUG
			if(!current) {
				if(End) {
					current = count + 1;
				}
				else {
					current = count - 1;
				}
			}
			else {
				if(current == count + 1) {
					current = count - 1;
				}
				else {
					current--;
				}
			}
		} else if(K == DOWN_ARROW || K == RIGHT_ARROW) {
			#ifdef DEBUG
			cout << "Moving down\n";
			#endif //DEBUG
			if(current == count - 1) {
				if(End) {
					current = count + 1;
				}
				else {
					current = 0;
				}
			}
			else {
				if(current == count + 1) {
					current = 0;
				}
				else {
					current++;
				}
			}
		} else if(K >= 48 && K <= 57) {	// 48 == 0, 57 == 9, guess what's between
			#ifdef DEBUG
			cout << "Chosing " << K - 48 << endl;
			#endif //DEBUG
			if(K == 48) {
				current = count + 1;
			}
			else {
				current = K - 48 - 1;
			}
			#ifdef DEBUG
			cout << "K = " << K << endl;
			cout << "current = " << current << endl;
			#endif //DEBUG
			choice = (current == count + 1 ? 0 : current + 1);
			chosen = true;
			Print();
			usleep(100);
		} else {
			string null = "";
// 			error(null.append("Key ").append(C.getKeyName(K)).append(" not assigned to any action"));
// 			E.Error(INV_OPT);
			#ifdef DEBUG
			D.Debug("invalid option");
			#endif //DEBUG
		}
	} while(!chosen);
	return choice;
}

#endif //MENU_CPP
