/**
 *
 * Codes taken from
 * http://wiki.ubuntuusers.de/Bash/Prompt
 *
 *	This header defines understandable terms for complex shell-commands
 *	which switch the colors of standard output
 *	These are only compatible with Linux (and possibly only with Bash, csh, sh and zsh; these were tested)
 *	I'm working on a header that will do the same for the Windows-Prompt
 *
 *	v0.2:
 *		- Merge with second colorcodes.h (v0.1), filtered out duplicates
 */


#ifndef COLORCODES_H
#define COLORCODES_H

//FONT COLORS

#define F_BLACK "\033[0;30m"
#define F_DARK_GRAY "\033[1;30m"
#define F_RED "\033[0;31m"
#define F_LIGHT_RED "\033[1;31m"
#define F_GREEN "\033[0;32m"
#define F_LIGHT_GREEN "\033[1;32m"
#define F_BROWN "\033[0;33m"
#define F_YELLOW "\033[1;33m"
#define F_BLUE "\033[0;34m"
#define F_LIGHT_BLUE "\033[1;34m"
#define F_VIOLET "\033[0;35m"
#define F_LIGHT_VIOLET "\033[1;35m"
#define F_DARK_CYAN "\033[0;36m"
#define F_CYAN "\033[1;36m"
#define F_GRAY "\033[0;37m"
#define F_WHITE "\033[0m"

//BACKGROUND COLORS

#define B_COLORLESS "\033[XXm"
#define B_BLACK "\033[40;XXm"
#define B_LIGHT_RED "\033[01;31m"
#define B_RED "\033[41;XXm"
#define B_LIGHT_GREEN "\033[01;32m"
#define B_GREEN "\033[42;XXm"
#define B_YELLOW "\033[01;33m"
#define B_BROWN "\033[43;XXm"
#define B_LIGHT_BLUE "\033[01;34m"
#define B_BLUE "\033[44;XXm"
#define B_LIGHT_MAGENTA "\033[01;35m"
#define B_VIOLET "\033[45;XXm"
#define B_LIGHT_CYAN "\033[01;36m"
#define B_CYAN "\033[46;XXm"
#define B_WHITE "\033[01;37m"
#define B_LIGHT_GRAY "\033[47;XXm"
#define B_DARK_GRAY "\033[01;30m"

#endif //COLORCODES_H
