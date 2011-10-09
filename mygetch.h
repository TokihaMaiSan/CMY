#ifndef MYGETCH_H
#define MYGETCH_H

// #include "objects.h"

#define __UNIX__
#define __NO_WINDOWS__

#ifdef __UNIX__
#include <termios.h>
#endif //__UNIX__
#include <fstream>
using namespace std;

#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ENTER_KEY 10
#define SPACE_KEY 32
// #define A_KEY
#define B_KEY_SMALL 98
#define Q_KEY_SMALL 113

#define DEFAULT_KEY_SAVE_LOCATION "keys"

class getch {
// 	static string keyNames[] = {"^0", "^1", "^2", "^3", "^4", "^5", "^6", "^7", "^8", "TABULATOR", "ENTER", "^11", "^12", "^13", "^14", "^15", "^16", "^17", "^18", "^19", "^20", "^21", "^22", "^23", "^24", "^25", "^26", "ESCAPE", "^28", "^29", "^30", "^31", "SPACE", "EXCLAMATION_MARK", "DOUBLE_QUOTATION_MARK", "#_KEY", "DOLLAR_SIGN", "PERCENTAGE_SIGN", "AMPERSAND", "SINGLE_QUOTATION_MARK", "OPENING_ROUND_BRACE", "CLOSING_ROUND_BRACE", "*_KEY", "PLUS", "COMMA", "MINUS", "DOT", "SLASH", "ZERO_KEY", "ONE_KEY", "TWO_KEY", "THREE_KEY", "FOUR_KEY", "FIVE_KEY", "SIX_KEY", "SEVEN_KEY", "EIGHT_KEY", "NINE_KEY", "COLON", "SEMICOLON", "LESSER_THEN", "EQUALS", "BIGGER_THEN", "QUESTION_MARK", "@_KEY", "A_KEY_BIG", "B_KEY_BIG", "C_KEY_BIG", "D_KEY_BIG", "E_KEY_BIG", "F_KEY_BIG", "G_KEY_BIG", "H_KEY_BIG", "I_KEY_BIG", "J_KEY_BIG", "K_KEY_BIG", "L_KEY_BIG", "M_KEY_BIG", "N_KEY_BIG", "O_KEY_BIG", "P_KEY_BIG", "Q_KEY_BIG", "R_KEY_BIG", "S_KEY_BIG", "T_KEY_BIG", "U_KEY_BIG", "V_KEY_BIG", "W_KEY_BIG", "X_KEY_BIG", "Y_KEY_BIG", "Z_KEY_BIG", "OPENING_SQUARE_BRACE", "BACK_SLASH", "CLOSING_SQUARE_BRACE", "^_KEY", "UNDERSCORE", "^96", "A_KEY_SMALL", "B_KEY_SMALL", "C_KEY_SMALL", "D_KEY_SMALL", "E_KEY_SMALL", "F_KEY_SMALL", "G_KEY_SMALL", "H_KEY_SMALL", "I_KEY_SMALL", "J_KEY_SMALL", "K_KEY_SMALL", "L_KEY_SMALL", "M_KEY_SMALL", "N_KEY_SMALL", "O_KEY_SMALL", "P_KEY_SMALL", "Q_KEY_SMALL", "R_KEY_SMALL", "S_KEY_SMALL", "T_KEY_SMALL", "U_KEY_SMALL", "V_KEY_SMALL", "W_KEY_SMALL", "X_KEY_SMALL", "Y_KEY_SMALL", "Z_KEY_SMALL", "OPENING_CURLY_BRACE","PIPE", "CLOSING_CURLY_BRACE", "TILDE", "BACK_SPACE", "^128", "^129", "^130", "^131", "^132", "^133", "^134", "^135", "^136", "^137", "^138", "^139", "^140", "^141", "^142", "^143", "^144", "^145", "^146", "^147", "^148", "^149", "^150", "^151", "^152", "^153", "^154", "^155", "^156", "^157", "^158", "^159", "^160", "^161", "^162", "^163", "^164", "^165", "^166", "^167", "^168", "^169", "^170", "^171", "^172", "^173", "^174", "^175", "^176", "^177", "^178", "^179", "^180", "^181", "^182", "^183", "^184", "^185", "^186", "^187", "^188", "^189", "^190", "^191", "^192", "^193", "^194", "^195", "^196","^197", "^198", "^199", "^200", "^201", "^202", "^203", "^204", "^205", "^206", "^207", "^208", "^209", "^210", "^211", "^212", "^213", "^214", "^215", "^216", "^217", "^218", "^219", "^220", "^221", "^222", "^223", "^224", "^225", "^226", "^227", "^228", "^229", "^230", "^231", "^232", "^233", "^234", "^235", "^236", "^237", "^238", "^239", "^240", "^241", "^242", "^243", "^244", "^245", "^246", "^247", "^248", "^249", "^250", "^251", "^252", "^253", "^254", "^255", "^256"};
	int mygetch() const;
	public:
		getch();
		~getch();
		int GetKey() const;
// 		string GetKeyName(unsigned short) const;
};

#endif //MYGETCH_H
