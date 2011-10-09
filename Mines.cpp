#ifndef MINES_CPP
#define MINES_CPP

#include "Mines.h"

extern int UP_KEY, DOWN_KEY, RIGHT_KEY, LEFT_KEY, OPEN_FIELD, MARK_FIELD, QUIT_KEY;

//---------- Constructor and Destructor ----------
//---------- Constructor ----------
Mines::Mines(): covered_tiles(0), height(0), width(0), bombs(0), bombs_checked(0), wins(0), losses(0), game_state(CONTINUE), initiated(false), first_time(true) {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Constructor Mines::Mines() --\n";
#endif
	board = NULL;
	if (!Load()) {
		wins = 0;
		losses = 0;
	} else {
		initiated = true;
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Constructor Mines::Mines() --\n";
#endif
}
//---------- END Constructor----------

//---------- Destructor ----------
Mines::~Mines() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Destructor Mines::~Mines() --\n";
#endif
	Save();
	Destroy();
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Destructor Mines::~Mines() --\n";
#endif
}
//---------- END Destructor ----------
//---------- END Constructor and Destructor ----------

//---------- Methods ----------
//---------- Create ----------
void Mines::Create() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::Create() --\n";
#endif
// 	Init(height, width, 0);
// 	if(board) {
// 		Destroy();
// 	}
	board = new tile*[height];
	for (int i = 0; i < height; i++) {
		board[i] = new tile[width];
	}
// 	focus.Reset();
	focus.SetCursor(&board[0][0]);
// 	focus.SetMAX(height, width);
// 	focus.SetBoard(this);
	covered_tiles = height * width;
	bombs_checked = 0;
	ConnectTiles();
	CoverUp();
	SetGameState(CONTINUE);
	first_time = true;
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::Create() --\n";
#endif
}
//---------- END Create ----------

//---------- Destroy ----------
void Mines::Destroy() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::Destroy() --\n";
#endif
	if (board) {
		for (int i = 0; i < height; i++) {
			if (board[i]) {
				delete [] board[i];
				board[i] = NULL;
			}
		}
		delete [] board;
		board = NULL;
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::Destroy() --\n";
#endif
}
//---------- END Destroy ----------

//---------- Init ----------
void Mines::Init(unsigned int Height = STD_HEIGHT, unsigned int Width = 0, unsigned int Bombs = 0) {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::Init(unsigned, unsigned, unsigned) --\n";
	cout << "-- DEBUG: with Height: " << Height << ",\n\t\tWidth: " << Width << ",\n\t\tBombs: " << Bombs << " --\n";
#endif
	Destroy();

	if (!Width) {
		Width = Height;
	}
	if (!Bombs) {
		Bombs = (Height * Width) / BOMB_DIVISOR;
	}
	height = Height;
	width = Width;
	bombs = Bombs;
	initiated = true;
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::Init(unsigned, unsigned, unsigned) --\n";
#endif
}
//---------- END Init----------

//---------- SetMines----------
void Mines::SetMines() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::SetMines() --\n";
#endif
	if (!bombs) {
		bombs = (height * width) / BOMB_DIVISOR;
	}
#ifdef DEBUG
	D.Debug("bombs", IS, bombs);
#endif //DEBUG
	for (int i = 0; i < bombs; i++) {
		int posX = -1, posY = -1;
		srand(time(0));
		do {
			posX = rand() % height;
			posY = rand() % width;
		} while (board[posX][posY].GetBomb() || board[posX][posY].GetState() == PROTECTED);
		board[posX][posY].SetBomb();
	}
	CalcValues();
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::SetMines() --\n";
#endif
}
//---------- END SetMines ----------

//---------- CoverUp ----------
void Mines::CoverUp() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::CoverUp() --\n";
#endif
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j].SetState(COVERED);
		}
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::CoverUp() --\n";
#endif
}
//---------- END CoverUp----------

//---------- SetGameState ----------
void Mines::SetGameState(unsigned short M) {
#ifdef DEBUG
	D.Debug("void SetGameState(unsigned short)", ENTER, M);
#endif //DEBUG
	game_state = M;
#ifdef DEBUG
	D.Debug("void SetGameState(unsigned short)", EXIT);
#endif //DEBUG
}
//---------- END SetGameState ----------

//---------- CalcValues ----------
void Mines::CalcValues() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::CalcValues() --\n";
#endif
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//if current field is a mine, then increment all fields around it
			if (board[i][j].GetBomb()) {

				//This increments the line above the mine (only upperright, upper and upperleft)

				//if the upper line exists (if this is still the top line, then there's no line above)
				if (i > 0) {
					//if this isn't the most left row
					if (j > 0) {
						//Increments upperleft
						board[i - 1][j - 1]++;
					}
					//This increments upper
					board[i - 1][j]++;
					//if there's still a row to the right
					if (j < width - 1) {
						//Increments upperright
						board[i - 1][j + 1]++;
					}
				}

				//This increments right and left
				if (j > 0) {
					//Increments left
					board[i][j - 1]++;
				}
				if (j < width - 1) {
					//Increments right
					board[i][j + 1]++;
				}

				//This increments the lower line

				//if there's still a line below
				if (i < height - 1) {
					//if it isn't the most left row
					if (j > 0) {
						//Increments lowerleft
						board[i + 1][j - 1]++;
					}
					//Increments lower
					board[i + 1][j]++;
					//if it isn't the most right row
					if (j < width - 1) {
						//Increments lowerright
						board[i + 1][j + 1]++;
					}
				}
			}
		}
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::CalcValues() --\n";
#endif
}
//---------- END CalcValues ----------

//---------- GameCore ----------
int Mines::GameCore() {
// 	int game_end = 0;
// 	string InPut = "";
// 	unsigned int xpos = 0, ypos = 0;
	getch InPut;
	int key = 0;
	if (!initiated) Init(STD_HEIGHT, STD_WIDTH, 0);
	while (MinesMenu()) {
		Create();
		SetGameState(CONTINUE);
		while (game_state == CONTINUE) {
			Draw();
			key = InPut.GetKey();
			if (key == UP_KEY) {
				focus.MoveUp();
			} else if (key == DOWN_KEY) {
				focus.MoveDown();
			} else if (key == RIGHT_KEY) {
				focus.MoveRight();
			} else if (key == LEFT_KEY) {
				focus.MoveLeft();
			} else if (key == OPEN_FIELD) {
				if (first_time) {
					focus.GetField()->SetState(PROTECTED);
					SetMines();
					focus.GetField()->SetState(COVERED);
					first_time = false;
				}
				UnCover(focus.GetField());
			} else if (key == MARK_FIELD) {
				MarkBomb(focus.GetField());
			} else if (key == QUIT_KEY) {
				SetGameState(MANUAL_END);
			} else {
// 				E.Error("There's no such option");
#ifdef DEBUG
				D.Debug("There's no such option");
#endif //DEBUG
			}
			CheckGameState();
		}
		if (game_state == FAIL) {
			RevealMines();
		}
		Draw();
		if (game_state == FAIL) {
			losses++;
			cout << "You've lost\n";
			Enter();
		} else if (game_state == WIN) {
			wins++;
			cout << "You've won!\n";
			Enter();
		} else if (game_state == MANUAL_END);
		else {
			cout << "Why the f*** has the game ended??\n";
			Enter();
		}
	}
	#ifdef __UNIX__
	system("clear");
	#endif //__UNIX__
	#ifdef __WINDOWS__
	system("cls");
	#endif //__WINDOWS__
	return 0;
}
//---------- END GameCore ----------

//---------- Draw ----------
void Mines::Draw() const {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::Draw() --\n";
#endif
#ifndef DEBUG
#ifdef __UNIX__
system("clear");
#endif //__UNIX__
#ifdef __WINDOWS__
system("cls");
#endif //__WINDOWS__
#endif //DEBUG
	bool focused = false;
	tile *foc = NULL;
	cout << "BOMBS in this game: " << bombs
	<< "\nBOMBS checked:\t" << bombs_checked << endl;
// 	for(int i = 0; i < width; i++) {
// 		cout << ' ';
// 		if(i < 10) cout << ' ';
// 		cout << i + 1;
// 		if(i < 100) cout << ' ';
// 	}
// 	cout << tab;
	for (int i = 0; i < width; i++) {
		cout << "+---";
	}
	cout << "+\n";
	for (int i = 0; i < height; i++) {
// 		cout <</* i + 1 << */"\t";
		cout << '|';
		for (int j = 0; j < width; j++) {
			foc = &board[i][j];
			if (focus.GetXPos() == i && focus.GetYPos() == j) {
				focused = true;
			}
			if (focused) {
#ifdef ENABLE_COLOR
				printf(F_LIGHT_RED);
#endif
				cout << '*';
#ifdef ENABLE_COLOR
				printf(F_WHITE);
#endif
			} else {
				cout << ' ';
			}
			switch (foc->GetState()) {
				case COVERED:
					cout << ' ';
					break;
				case MARKED:
#ifdef ENABLE_COLOR
					printf(F_CYAN);
#endif
					cout << 'B';
#ifdef ENABLE_COLOR
					printf(F_WHITE);
#endif
					break;
				case MARKED_RIGHT:
#ifdef ENABLE_COLOR
					printf(F_GREEN);
#endif
					cout << '+';
#ifdef ENABLE_COLOR
					printf(F_WHITE);
#endif
					break;
				case MARKED_FALSE:
#ifdef ENABLE_COLOR
					printf(F_CYAN);
#endif
					cout << '-';
#ifdef ENABLE_COLOR
					printf(F_WHITE);
#endif
					break;
				case EXPLODED:
#ifdef ENABLE_COLOR
					printf(F_RED);
#endif
					cout << 'X';
#ifdef ENABLE_COLOR
					printf(F_WHITE);
#endif
					break;
				default:
#ifdef ENABLE_COLOR
					switch (foc->GetValue()) {
						case 0:
							break;
						case 1:
							printf(F_LIGHT_BLUE);
							break;
						case 2:
							printf(F_LIGHT_GREEN);
							break;
						case 3:
							printf(F_YELLOW);
							break;
						case 4:
							printf(F_LIGHT_RED);
							break;
						case 5:
							printf(F_VIOLET);
							break;
						case 6:
							printf(F_BLUE);
							break;
						case 7:
							printf(F_DARK_CYAN);
							break;
						case 8:
							printf(F_BROWN);
							break;
					}
#endif
					cout << foc->GetValue();
#ifdef ENABLE_COLOR
					printf(F_WHITE);
#endif
					break;
			}
			if (focused) {
#ifdef ENABLE_COLOR
				printf(F_LIGHT_RED);
#endif
				cout << '*';
#ifdef ENABLE_COLOR
				printf(F_WHITE);
#endif
			} else {
				cout << ' ';
			}
			cout << '|';
			focused = false;
		}
		cout << "\n";
		for (int j = 0; j < width; j++) {
			cout << "+---";
		}
		cout << "+\n";
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::Draw() --\n";
#endif
}
//---------- END Draw----------

//---------- UnCover ----------
void Mines::UnCover(tile *T) {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::UnCover(unsigned int posX, unsigned int posY, bool check) with (" << T->GetXPos() << ", " << T->GetYPos() << " --\n";
#endif
	if (T->GetState() == MARKED) {	//If field is marked as a bomb do nothing
		return;
	}

	if (T->GetState() == COVERED) {
		covered_tiles--;
		T->SetState(UNCOVERED);
	}
	if (!T->GetBomb()) {	//if the current field is not a mine
		if (T->GetValue() == 0) {	//If the current field has no value, uncover those around as well
			if (T->GetXPos() > 0 && T->GetUpper()->GetState() == COVERED) {
				//Uncovers the field above the current
				UnCover(T->GetUpper());
			}
			if (T->GetXPos() < height - 1 && T->GetLower()->GetState() == COVERED) {
				//Uncovers the field below the current
				UnCover(T->GetLower());
			}
			if (T->GetYPos() > 0 && T->GetLeft()->GetState() == COVERED) {
				//Uncovers the field left from the current
				UnCover(T->GetLeft());
			}
			if (T->GetYPos() < width - 1 && T->GetRight()->GetState() == COVERED) {
				//Uncovers the field right from the current
				UnCover(T->GetRight());
			}
			if (T->GetXPos() > 0 && T->GetYPos() > 0 && T->GetUpperLeft()->GetState() == COVERED) {
				//Uncovers the upperleft field
				UnCover(T->GetUpperLeft());
			}
			if (T->GetXPos() > 0 && T->GetYPos() < width - 1 && T->GetUpperRight()->GetState() == COVERED) {
				//Uncovers the upperright field
				UnCover(T->GetUpperRight());
			}
			if (T->GetXPos() < height - 1 && T->GetYPos() > 0 && T->GetLowerLeft()->GetState() == COVERED) {
				//Uncovers the lowerleft field
				UnCover(T->GetLowerLeft());
			}
			if (T->GetXPos() < height - 1 && T->GetYPos() < width - 1 && T->GetLowerRight()->GetState() == COVERED) {
				//UnCovers the lowerright field
				UnCover(T->GetLowerRight());
			}
		}
// 		else {
// 			T->SetState(UNCOVERED);
// 		}
	} else {
		SetGameState(FAIL);
	}
// #ifdef DEBUG
// 	else cout << "-- DEBUG: Board[" << posX << "][" << posY << "] has Value " << board[posX][posY].GetValue() << " --\n";
// #endif
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::UnCover(unsigned int posX, unsigned int posY, bool check) --\n";
#endif
}
//---------- END UnCover ----------

//---------- MarkBomb ----------
void Mines::MarkBomb(tile *T) {
	if (T->GetState() == MARKED) {
		T->SetState(COVERED);
		bombs_checked--;
	} else {
		T->SetState(MARKED);
		bombs_checked++;
	}
}
//---------- END MarkBomb ----------

//---------- CheckGameState ----------
void Mines::CheckGameState() {
#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::CheckGameState() --\n";
#endif
	if (covered_tiles > bombs) {
		return;
	} else if (covered_tiles == bombs) {
		bool ok = true;
		for (int i = 0; i < height && ok; i++) {
			for (int j = 0; j < width && ok; j++) {
				tile *foc = &board[i][j];
				if ((foc->GetState() == MARKED || foc->GetState() == COVERED) && !foc->GetBomb()) {
					ok = false;
					break;
				}
			}
			if (!ok) {
				break;
			}
		}
		if (ok) {
			SetGameState(WIN);
		}
#ifdef DEBUG
		else {
			D.Debug("covered_tiles", IS, covered_tiles);
			D.Debug("bombs", IS, bombs);
			for (int i = 0; i < height && ok; i++) {
				for (int j = 0; j < width && ok; j++) {
					tile *foc = &board[i][j];
					cout << "DEBUG: board[" << i << "][" << j << "] is";
					if (!foc->GetBomb()) {
#ifdef ENABLE_COLOR
						printf(F_RED);
#endif //ENABLE_COLOR
						cout << "NOT";
#ifdef ENABLE_COLOR
						printf(F_WHITE);
#endif //ENABLE_COLOR
					}
					cout << " a bomb ";
					if (foc->GetState() == MARKED) {
						if (foc->GetBomb()) {
							cout << "AND";
						} else {
							cout << "BUT";
						}
						cout << "IS marked as such";
					} else {
						if (foc->GetBomb()) {
							cout << "BUT";
						} else {
							cout << "AND";
						}
						cout << " IS NOT marked as such";
					}
					cout << " --\n";
				}
			}
		}
#endif //DEBUG
	}
#ifdef DEBUG
	cout << "-- DEBUG: EXIT:  Mines::CheckGameState() --\n";
#endif
	return;
}
//---------- END CheckGameState ----------

//---------- MinesMenu ----------
int Mines::MinesMenu() {
	Menu MainMenu, Options;
	string menu_string[] = {"Start Game", "New Player", "Change Player", "Options", "Statistics"};
	string options_string[] = {"New values", "Change Keys", "Reset"};
	MainMenu.Set(menu_string, sizeof(menu_string) / sizeof(string), END);
	Options.Set(options_string, sizeof(options_string) / sizeof(string), BACK);

	int status = 0, Height = 0, Width = 0, Bombs = 0, key = 0;
	getch G;
	bool end = false;
	while (!end) {
		switch (MainMenu.GetChoice()) {	//Main Menu
			case 0:
				status = 0;
				end = true;
				break;
			case 1:
				status = 1;
				end = true;
				break;
			case 2:
				//TODO
				cout << "FUNCTION \"New Player\" not yet available\n";
				break;
			case 3:
				//TODO
				cout << "FUNCTION \"Change Player\" not yet available\n";
				break;
			case 4:
				while (!end) {
					cout << endl << endl;
					switch (Options.GetChoice()) {	//Options Menu
						case 0:
							end = true;
							break;
						case 1:
							cout << endl << endl;
							while (!end) {
								cout << "Lines (current: " << height << "; 0 for default): ";
								cin >> Height;
								if (Height < 3 && Height != 0) {
									cout << "Must be at least 3" << endl;
								} else {
									if (!Height) {
										Height = STD_HEIGHT;
									}
									end = true;
								}
							}
							end = false;
							while (!end) {
								cout << "Columns (current: " << width << "; 0 for default): ";
								cin >> Width;
								if (Width < 3 && Width != 0) {
									cout << "Must be at least 3" << endl;
								} else {
									if (!Width) {
										Width = STD_WIDTH;
									}
									end = true;
								}
							}
							end = false;
							while (!end) {
								cout << "Bombs (current: " << bombs << "; 0 for default): ";
								cin >> Bombs;
								if (Bombs < 0) {
									cout << "Must be more than 0" << endl;
								} else {
									end = true;
								}
							}
							end = false;
							Destroy();
							Init(Height, Width, Bombs);
							cout << "Set to " << height << 'x' << width << " B:" << bombs << endl;
							break;
						case 2:
// 							focus.ChangeKeys();
							break;
						case 3:
							Destroy();
							Init();
							cout << "Reset to " << height << 'x' << width << " B:" << bombs << endl;
							break;
					}
				}
				end = false;
				break;
			case 5:
				cout << "STATISTICS" << endl << endl;
				cout << "You have won " << wins << " games so far\n";
				cout << "You have lost " << losses << " games so far\n";
				cout << endl << "Press \'r\' if you want to reset\n"
				<< "Press any other key to go back to the menu\n";
				key = G.GetKey();
				if (char(key) == 'r' || char(key) == 'R') {
					wins = 0;
					losses = 0;
					cout << "Statistics have been set back\n";
				}
				break;
			default:
// 				E.Error(INV_OPT);
#ifdef DEBUG
				D.Debug("invalid option");
#endif //DEBUG
				break;
		}
	}
	return status;
}
//---------- END Menu ----------

//---------- ConnectTiles ----------
/**
	We assume that the starting point, where everything begins is (0,0). This would be the upper most left tile on the board. Based on that assumption the neighbouring tiles are found in the following way. To make things easier for the user we connect the upper tiles to the lowest tiles as if the latter where still one level above. Likewise for all other tiles that are on one side of the board. This creates the ability to cycle through the board

	Upper is height - 1, therefor we decrease the current height by one to get the upper tile

	Lower is height + 1, therefor we increase the current height by one to get the lower tile

	Right ---> is width + 1, therefor we increase the current width by one to get the right tile

	Left <--- is width - 1, therefor we decrease the current width by one to get the left tile

	UpperLeft/-Right and LowerLeft/-Right are only combinations of what is shown above
*/
void Mines::ConnectTiles() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j].SetUpperLeft(&board[(i > 0 ? i - 1 : height - 1)][(j > 0 ? j - 1 : width - 1)]);
			board[i][j].SetUpper(&board[(i > 0 ? i - 1 : height - 1)][j]);
			board[i][j].SetUpperRight(&board[(i > 0 ? i - 1 : height - 1)][(j < width - 1 ? j + 1 : 0)]);
			board[i][j].SetLeft(&board[i][(j > 0 ? j - 1 : width - 1)]);
			board[i][j].SetRight(&board[i][(j < width - 1 ? j + 1 : 0)]);
			board[i][j].SetLowerLeft(&board[(i < height - 1 ? i + 1 : 0)][(j > 0 ? j - 1 : width - 1)]);
			board[i][j].SetLower(&board[(i < height - 1 ? i + 1 : 0)][j]);
			board[i][j].SetLowerRight(&board[(i < height - 1 ? i + 1 : 0)][(j < width - 1 ? j + 1 : 0)]);
			board[i][j].SetXPos(i);
			board[i][j].SetYPos(j);
		}
	}
}
//---------- END ConnectTiles ----------

//---------- RevealMines ----------
/**
	This function is called when the player failed to avoid the mines on the field. It goes through the field and marks all hidden mines accordingly. The mines that where marked right by the player are marked as such as are the mines that where not marked at all. Then of course the player could have marked any other field that is not a mine, those are also marked as false.
*/
void Mines::RevealMines() {
	tile *foc = NULL;
	for (int i = 0; i < height; i++) {	//Uncovers every mine on the field
		for (int j = 0; j < width; j++) {
			foc = &board[i][j];
			if (foc->GetBomb()) {
				if (foc->GetState() == MARKED) {
					foc->SetState(MARKED_RIGHT);
				} else {
					foc->SetState(EXPLODED);
				}
			} else {
				if (foc->GetState() == MARKED) {
					foc->SetState(MARKED_FALSE);
				}
			}
		}
	}
	foc = NULL;
}
//---------- END RevealMines ----------

//---------- Save ----------
/**
	This saves the current state of some variables.
	If this fails an error is shown.
*/
bool Mines::Save() const {
	ofstream oFile;
	oFile.open(DATA_SAVE_DIR);
	if (oFile.is_open()) {
		oFile << wins << '$' << losses << '$' << height << '$' << width << '$' << bombs << '$';
		oFile.close();
		return true;
	} else {
		string null = "";
// 		E.Error(null.append("couldn\'t create file ").append(DATA_SAVE_DIR));
#ifdef DEBUG
		D.Debug(null.append("couldn\'t create file ").append(DATA_SAVE_DIR));
#endif //DEBUG
		return false;
	}
}
//---------- END Save ----------

//---------- Load ----------
/**
	This loads state information from a file. The file is specified as a macro in the header-file.
	Right now it just reads the file and initialises certain variables with the found values. The values are separated by '$'.
	TODO: This has to be transformed so that it doesn't look like written by a newbie but performs its task more efficiently in both space and time (meaning fewer and more efficient lines).
*/
bool Mines::Load() {
	ifstream iFile;
	string line = "";
	iFile.open(DATA_SAVE_DIR);
	if (iFile.is_open()) {
		getline(iFile, line);
		iFile.close();
		int i = 0;
		wins = 0;
		losses = 0;
		for (; line[i] != '$' && line[i] != '\0'; i++) {
			wins *= 10;
			wins += int(line[i]) - 48;
		}
		i++;
		for (; line[i] != '$' && line[i] != '\0'; i++) {
			losses *= 10;
			losses += int(line[i]) - 48;
		}
		i++;
		for (; line[i] != '$' && line[i] != '\0'; i++) {
			height *= 10;
			height += int(line[i]) - 48;
		}
		i++;
		for (; line[i] != '$' && line[i] != '\0'; i++) {
			width *= 10;
			width += int(line[i]) - 48;
		}
		i++;
		for (; line[i] != '$' && line[i] != '\0'; i++) {
			bombs *= 10;
			bombs += int(line[i]) - 48;
		}
		return true;
	} else {
		string null = "";
// 		E.Error(null.append("couldn\'t open file ").append(DATA_SAVE_DIR));
#ifdef DEBUG
		D.Debug(null.append("couldn\'t open file ").append(DATA_SAVE_DIR));
#endif //DEBUG
		return false;
	}
}
//---------- END Load ----------

//---------- END Methods----------

#endif //MINES_CPP
