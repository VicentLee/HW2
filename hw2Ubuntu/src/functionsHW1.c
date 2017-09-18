/****************************************************************************
 
 ****************************************************************************/
#include <stdio.h>
#include "functionsHW1.h"

/* array used for ASCII conversion */
const char ASCII[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char DEBUG_WRITELINE[] =
		"\n[*DEBUG:  The length of the string displayed is ";

/*--------------------------------------------------------------------------
 Function Name:          clrbuf
 Purpose:                When called, this function will clear stdin.
 Description:            This function checks to see if the incoming
			 	 	 	 parameter is already '\n' indicating that stdin
						 is already clear.  If stdin is already clear, this
						 function does nothing.  Otherwise, this function
						 calls "fgetc" in a loop until stdin is clear.
 input:                  character:  the most recent character received from a
						 previous call to fgetc.
 result:                 stdin cleared.  nothing returned.
 --------------------------------------------------------------------------*/
void clrbuf(int character) {

	while (character != '\n') {
		character = fgetc(stdin);
	}
}

/*--------------------------------------------------------------------------
 function name:         baseout.
 purpose:               the baseout function takes the long integer number
						provided by the user, converts it to the base that is
						passed in, and displays it to the filestream stream.

 description:           this requires separating the number into individual
						characters, converting each character into its digit
						value, and then displaying the result.

 input:                 number: number that user wants to check
						base  : user defined base
						stream : filestream to store/display the result

 Result:                nonzero digit count in asked base
 --------------------------------------------------------------------------*/

void baseout(long number, long base, FILE * stream) {

	long rmd;				// remainder
	long quotient = number;	// quotient

	rmd = quotient % base;
	quotient = quotient / base;

	if (quotient != 0) {
		//recursive call until 0 quotient got
		baseout(quotient, base, stream);

	}

	fputc(ASCII[rmd], stdout);
}

/*--------------------------------------------------------------------------
 Function Name:         decout
 Purpose:               The decout function takes the long integer number
						provided by the user and displays it to the filestream
						stream as an integer.
 Description:           separating the number into individual characters,
						converting each character into its digit value,
						and then displaying the result.
 Input:                 number: the number wants to convert
 	 	 	 	 	 	stream: filestream that the converted result will go
 Result:                None
 --------------------------------------------------------------------------*/

void decout(unsigned long number, FILE * stream) {
	baseout(number, DECIMAL, stream);
}

/*--------------------------------------------------------------------------
 Function Name:         hexout
 Purpose:               Prints a number in base 16 to the parameter FILE stream
 Description:           Goal is achieved via delegating to the baseout function
 Input:                 number:  the number to display
 	 	 	 	 	 	stream:  where to display, likely stdout or stderr
 Result:                Number in base 16 is displayed.
 	 	 	 	 	 	No return value.
 --------------------------------------------------------------------------*/
void hexout(unsigned long number, FILE * stream) {

	/* Output "0x" for hexidecimal. */
	writeline("0x", stream);
	int HEX_digit_cnt = 0; 		// check how many digits you need in HEX base
	long tmp = number;			// temporary variable
	int padding_zero_cnt = 0; 	// number of padding zeros

	while (0 != tmp) {
		tmp = tmp / HEX;
		HEX_digit_cnt++;
	}

	padding_zero_cnt = HEX - HEX_digit_cnt;
	// padding zeros
	while (padding_zero_cnt--) {
		fputc(ASCII[0], stream);
	}

	// output nonzero digits
	baseout(number, HEX, stream);

}

/*--------------------------------------------------------------------------
 Function Name:         newline
 Purpose:               Displays a newline character ('\n')
 	 	 	 	 	 	to the filestream stream.

 Input:                 stream: file stream.
 Result:                None.
 --------------------------------------------------------------------------*/
void newline(FILE * stream) {
	fputc('\n', stream);
}

/*--------------------------------------------------------------------------
 Function Name:         writeline.
 Purpose:               Displays the string message to the user via
 	 	 	 	 	 	the filestream stream.
 Description:           Use loop to put each character in the msg via fputc.
 Input:                 message: input string
						stream: file sytem that the input string will go

 Result:                length of the string
 --------------------------------------------------------------------------*/
long writeline(const char * message, FILE * stream) {

	/* for output loop */
	long index = 0;

	while (message[index] != '\0') {

		fputc(message[index], stream);
		index++;
	}
	return index; /*length of the string*/


}

