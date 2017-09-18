/*
 * functionsHW1.h
 *	contain functions of HW1 and relative global variables
 *  	Created on: Sep 12, 2017
 *      Author: lizhi
 */

#ifndef FUNCTIONSHW1_H_
#define FUNCTIONSHW1_H_

#include <stdio.h>  // for type FILE

/*global MACROS*/
#define COUNT 16    /* number of hex digits to display */
#define DECIMAL 10  /* to indicate base 10 */
#define HEX 16      /* to indicate base 16 */

#define MAXLENGTH 80
#define OFFSET ('a' - 'A')
#define SPACE ' '
#define TRUE 1
#define ASCII_ZERO '0'

#define ERROR -1
#define FALSE 0


/*GLOBAL variables */
extern const char ASCII[];
extern const char DEBUG_WRITELINE[];


/*--------------------------------------------------------------------------
 Function Declaration
 --------------------------------------------------------------------------*/

void baseout(long number, long base, FILE * stream);
void decout(unsigned long number, FILE * stream);
void newline(FILE * stream);
long writeline(const char * message, FILE * stream);
void clrbuf(int character);
long decin (void);
void digiterror (int, long *, const char *);
long getaline (char *, long);
void hexout(unsigned long number, FILE * stream);



#endif /* FUNCTIONSHW1_H_ */



