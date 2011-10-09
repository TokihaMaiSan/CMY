#include "Mines.h"

#ifdef __UNIX__
#include <termios.h>
#endif //__UNIX__
#include <cstdlib>

#define ARG_HELP "-h"
#define ARG_HELP2 "--help"
#define ARG_VERSION "-v"
#define ARG_VERSION2 "--version"
// #define ARG_DEBUG "-d"
// #define ARG_DEBUG2 "--debug"
using namespace std;

string helpstring = "NAME\n\tMines - yet another Minesweeper-clone\n\tMines [-hvd] <rows> <columns> <mines>\n\n\tif no mines or columns are given the board will be a square and the mines will take about a 5th of all space\n\nSYNOPSIS\n\tThis helppage describes the commands, that are supported by Mines\n\n\t-h\t--help\n\t\tdisplays this helppage and exits\n\n\t-v\t--version\n\t\tdisplays the current installed version of Mines and exits\n\n\t-d\t--debug\n\t\tstarts Mines with Debug-Messages (buggy, type \"make debug;make\" instead)\n\nAUTHOR\n\tWritten by Stefan Ohri\n\nREPORTING BUGS\n\tReport bugs to spam@spam.com\n\nCOPYRIGHT\n\tWell, nothing as of today\n\n";
// string helpstring = "Usage: .MINES [-opt] <X-Size> <Y-Size> <Bombs>\n\nUseful commands:\n\n\t-h --help\tShows this help and exits\n\n\t-v --version\tShows the current version of MINES and exits\n\t-d --debug\tShows debugging output";
string version = "MINES v. 0.6\t\t\t16th February 2010";

int main(int argc, char** argv) {
	unsigned int XSize = 10, YSize = 10, Bombs = 0;
	string arg = "";
// 	cout << "argc: " << argc << endl;
// 	cout << "argv[0]: " << argv[0] << endl;
// 	if(argc >= 2) cout << "argv[1]: " << argv[1] << endl;
	if(argc > 1) {
		arg = argv[1];
// 		trim(argv[1]);
		if(arg == ARG_HELP || arg == ARG_HELP2) {
			#ifdef __UNIX__
			system("clear");
			#endif //__UNIX__
			#ifdef __WINDOWS__
			system("cls");
			#endif // __WINDOWS__
			cout << helpstring << version << endl << endl;
			return 0;
		}
		else if(arg == ARG_VERSION || arg == ARG_VERSION2) {
			cout << endl << version << endl << endl;
			return 0;
		}
// 		else if(arg == ARG_DEBUG || arg == ARG_DEBUG2) {
// #define DEBUG
// 		}
		else {
			try {
#ifdef DEBUG
				cout << "-- DEBUG: try-block --\n";
#endif
				if(argc >= 2) {
#ifdef DEBUG
					cout << "-- DEBUG: XSize = " << XSize << " --\n";
#endif
					XSize = atoi(argv[1]);
#ifdef DEBUG
					cout << "-- DEBUG: XSize = " << XSize << " --\n";
#endif
				}
				if(argc >= 3) {
#ifdef DEBUG
					cout << "-- DEBUG: YSize = " << YSize << " --\n";
#endif
					YSize = atoi(argv[2]);
#ifdef DEBUG
					cout << "-- DEBUG: YSize = " << YSize << " --\n";
#endif
				}
				else {
#ifdef DEBUG
					cout << "-- DEBUG: else --> YSize = XSize --\n";
#endif
					YSize = XSize;
				}
				if(argc >= 4) {
#ifdef DEBUG
					cout << "-- DEBUG: Bombs = " << Bombs << " --\n";
#endif
					Bombs = atoi(argv[3]);
#ifdef DEBUG
					cout << "-- DEBUG: Bombs = " << Bombs << " --\n";
#endif
				}
			}
			catch(int i) {
				cout << "Usage: ./MINES <X-Size:int> <Y-Size:int>\n\t:int = Integer\n";
				return 0;
			}
		}
	}
	if(XSize < MIN_SIZE) XSize = MIN_SIZE;
	if(YSize < MIN_SIZE) YSize = MIN_SIZE;
	if(Bombs < 0) Bombs = 0;
	Mines minefield;
// 	minefield.Init(XSize, YSize, Bombs);

	//Change Konsole colors to white
#ifdef ENABLE_COLOR
	printf(F_WHITE);
#endif
// 	printf(B_DARK_GRAY);
	return minefield.GameCore();
}
