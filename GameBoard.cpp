GameBoard(int, int);
GameBoard(const GameBoard&);
~GameBoard();

//---------- Draw ----------
void Mines::Draw() const {
	#ifdef DEBUG
	cout << "-- DEBUG: ENTER: Mines::Draw() --\n";
	#endif
	#ifndef DEBUG
	#ifdef __UNIX__
	system("clear");
	#endif //__UNIX__
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