/****************************************************************************

 CSE 12, Summer 2017
 August 8, 2017
 cs12xzz
 Assignment Two

 File Name:      main.c
 Description:    This program reads strings and integers from the user,
				 processes them, and prints them back to the user.  Program
				 terminates when user enters ^D.  At termination, program
				 outputs sizes of various types of C/C++ pre defined types.
				
 ****************************************************************************/
/* declare fputc/fgetc */
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "functionsHW1.h"

/* messages */
const char CAUSED_OVERFLOW[] 	= "caused overflow!!\n";
const char DIGIT_STRING[] 		= "digit ";
const char REENTER_NUMBER[] 	= "\nPlease reenter number: ";
const char OUT_OF_RANGE[] 		= " out of range!!!\n";

/* debug messages */
const char DEBUG_GETALINE[] =
		"[*DEBUG:  The length of the string just entered is ";

static long debug_on = FALSE;

/*--------------------------------------------------------------------------
 Function Name:          decin
 Purpose:                This function accepts (non-negative) integer
 	 	 	 	 	 	 input from from the user.

 Description:            This function processes user input in a loop that ends
						 when the user enters either a valid number or EOF.
						 If EOF is entered, EOF is returned.  Otherwise each
						 character entered is checked to verify that it is
						 numeric.  Non-numeric input is identified, the user
						 is notified, reprompted, and the loop begins again.
						 Once the input is verified to be valid, a series
						 of multiplication by 10 and addition can take
						 place to convert the ASCII characters entered into
						 a numeric quantity.

 Input:                  None.
 Result:                 The number entered or EOF.

 --------------------------------------------------------------------------*/
long decin(void) {

	/*variables for buffer */
	char string_buff[MAXLENGTH] = "";
	const char err_msg[] = " is not a valid digit input\n";

	int strlength = 0;				// string length
	int character = 0;				// container for fgetc()



	int this_digit;

	long number = 0;				// return value container
	int  flag_nonvalid_input = 0;	// flag to check input
	long last_number = 0;			// for checking overflow



	/*if valid number haven't be gotten*/
	while (1) {
		/* reset status variables */
		number = 0;					// return value container
		flag_nonvalid_input = 0;	// flag to check input
		last_number = 0;			// for checking overflow

		memset(string_buff,'\0',MAXLENGTH);

		strlength = getaline(string_buff, MAXLENGTH);
		fprintf(stderr,"string entered: %s and strlength is %d\n",
								string_buff, strlength);

		// handle ^D/^Z to exit
		if (strlength == EOF) return EOF;
		if (strlength == 0) {
			fprintf(stderr,"No input ");
			fprintf(stderr,REENTER_NUMBER);
			continue;
		}

		/*loop until got a valid input (digits sequence end with '\0') */
		for(int i=0; i<strlength; i++) {

			character = string_buff[i];

			/*got an valid digit*/
			if (character >= ASCII[0] && character <= ASCII[9]) {

				/*converting ASCII to DECIMAL number*/
				this_digit = character - ASCII[0];
				number = number * DECIMAL + this_digit;
				fprintf(stderr,"\nwe got a digit [%d], "
						"last_number is [%ld], "
						"number now is [%ld]\n",
						this_digit,	last_number, number);

				/*check overflow*/
				if (number/10 == last_number) {
					last_number = number;
				}else{
					flag_nonvalid_input++;
					fprintf(stderr,"%s",CAUSED_OVERFLOW);
					fprintf(stderr,"%s",REENTER_NUMBER);
					break; //break for loop
				}

			}else {

				flag_nonvalid_input++;
				/*handle erroneous user input*/
				digiterror(character, &number, err_msg);
				break; //break for loop
			}


		}// end for loop

		/*input is valid*/
		if (flag_nonvalid_input == 0) {
			fprintf(stderr,"\nwe got a valid number [%ld] and out while loop\n",number);
			break;	// break while loop
		}


	} //end of while(1)
	return number;
}

/*--------------------------------------------------------------------------
 Function Name:          digiterror
 Purpose:                This function handles erroneous user input.
 Description:            This function reinitializes sum, displays and
						 error message to the user, and asks for fresh
						 input.

 Input:                  character:  The character that began the problem.
						 sum:  A pointer to the sum to reinitialize.
						 message:  The message to display to the user.
 Result:                 The message is displayed to the user.  sum is 0.
 --------------------------------------------------------------------------*/
void digiterror(int character, long * sum, const char * message) {

	/* reset sum */
	*sum = 0;

	/* output error message */
	writeline(DIGIT_STRING, stderr);
	fputc(character, stderr);
	writeline(message, stderr);

	writeline(REENTER_NUMBER, stderr);
}

/*--------------------------------------------------------------------------
 Function Name:          getaline
 Purpose:                This function will read a string from the user.
 Description:            This function gets input from the user via
						 calls to fgetc up to some maximum number of
						 characters.  Input is terminated when either the
						 maximum number of characters are entered, or
						 a newline character is detected.  If the user
						 enters more characters than the maximum, clrbuf
						 is called to remove extra characters which are
						 ignored.  Since this is routine accepts input,
						 if EOF is detected EOF is passed back to the main
						 program.

 Input:                  message:  the destination array where input is stored.
						 maxlength:  the maximum number of non-NULL characters
						 allowed in the string + 1 for the NULL char.
 Result:                 User input is stored in message.
						 EOF is returned when the user enters ^D.
						 Otherwise, the length of the message is returned.
 --------------------------------------------------------------------------*/

long getaline(char * message, long maxlength) {
	/* YOUR CODE GOES HERE */
	int index = 0;
	int character;
	/*get input message  */
	while (1) {

		character = fgetc(stdin);

		/*check ctrl-D in Unix/Linux or ctrl-Z in windows*/
		if (character == EOF) return EOF;

		/* when input size is less than MAXLENGTH */
		if (index < MAXLENGTH) {
			if (character == '\n') {

				message[index] = '\0';
				//fprintf(stderr,"%s %d]\n",DEBUG_GETALINE,index);
				return index;
			} else {
				/*put character in when range 0 ~ MAXLENGTH-2*/
				if( index < MAXLENGTH -1){
					message[index] = character;
				}else{
					//fprintf(stderr,"throw character [%d] away\n",character);
				}


				index++;
			}
		/*input size is larger than MAXLENGTH */
		} else {

			//fprintf(stderr,"input is too long!\n");
			clrbuf(character);
			message[MAXLENGTH - 1] = '\0';
			//fprintf(stderr,"output message is [%s]\n",message);
			return (MAXLENGTH - 1);
		}
	}

}
/*--------------------------------------------------------------------------
 Function Name:          main
 Description:            This function asks for input and displays output
 Purpose:                This program asks the user to enter a string
						 and a number.  Computations are performed on the
						 strings and numbers, and the results are displayed.
 Description:            This function asks for input and displays output
						 in an infinite loop until EOF is detected.  Once EOF
						 is detected, the lengths of the types are displayed.
 Input:                  None.
 --------------------------------------------------------------------------*/
int main(int argc, char * const * argv) {
	//char *const* argv = char *const argv[]  ---- an array of const p

	/*turn off buffer for eclipse on windows*/
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	long base; 						/* to hold output base */
	char buffer[MAXLENGTH]; 		/* to hold string */
	long number; 					/* to hold number entered */
	int  strlength; 				/* length of string */

	long array[10] = { 0 };   /* to show user where memory is allocated */
	long * ap = array; 		  /* to show user about addresses in memory */
	long ** app = &ap; 		  /* to show user about addresses in memory */
	long * apx = &array[0];   /* to show user about addresses in memory */
	char option; 			  /* the command line option */

	debug_on = FALSE;

	/* check command line options for debug display */
	/* initialize debug states */
	while ((option = getopt(argc, argv, "x")) != EOF) {
		switch (option) {
		case 'x':
			debug_on = TRUE;
			break;
		}
		printf("DEBUG STATUS %ld\n",debug_on);
	}


	/* infinite loop until user enters ^D */
	while (1) {

		writeline("\nPlease enter a string:", stdout);
		strlength = getaline(buffer, MAXLENGTH);
		printf("\nreturn value form getaline is %d", strlength);
		newline(stdout);

		/* check for end of input */
		if (strlength == EOF) {
			printf("EOF return value is get in main\n");
			break;
		}

		writeline("\nThe string is:  ", stdout);
		writeline(buffer, stdout);

		writeline("\nIts length is ", stdout);
		decout(strlength, stdout);
		newline(stdout);

		writeline("\nPlease enter a decimal number:  ", stdout);
		if ((number = decin()) == EOF)
			break;

		writeline("\nPlease enter an output base (2-36):  ", stdout);
		if ((base = decin()) == EOF)
			break;

		writeline("\nNumber entered is:  ", stdout);
		decout(number, stdout);

		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout(number, stdout);

		writeline("\nAnd in base ", stdout);
		decout(base, stdout);
		writeline(" is:  ", stdout);
		baseout(number, base, stdout);

		writeline("\nNumber entered multiplied by 8 is:  ", stdout);
		decout(number << 3, stdout);
		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout(number << 3, stdout);

		newline(stdout);
	}// end while
	if (debug_on) {
		writeline("\nThe value of ap is:  ", stdout);
		decout((long) ap, stdout);
		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout((long) ap, stdout);
		newline(stdout);

		writeline("The value of app is:  ", stdout);
		decout((long) app, stdout);
		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout((long) app, stdout);
		newline(stdout);

		writeline("The value of apx is:  ", stdout);
		decout((long) apx, stdout);
		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout((long) apx, stdout);
		newline(stdout);

		writeline("The value of ap + 1 is:  ", stdout);
		decout((long) (ap + 1), stdout);
		writeline("\nAnd in hexidecimal is:  ", stdout);
		hexout((long) (ap + 1), stdout);
		newline(stdout);

		writeline("The address of array[0] is:  ", stdout);
		decout((long) &array[0], stdout);
		newline(stdout);

		writeline("The address of array[1] is:  ", stdout);
		decout((long) &array[1], stdout);
		newline(stdout);

		writeline("The size of a float is:  ", stdout);
		decout(sizeof(float), stdout);
		newline(stdout);

		writeline("The size of a double is:  ", stdout);
		decout(sizeof(double), stdout);
		newline(stdout);

		writeline("The size of a long double is:  ", stdout);
		decout(sizeof(long double), stdout);
		newline(stdout);

		writeline("The size of a char is:  ", stdout);
		decout(sizeof(char), stdout);
		newline(stdout);

		writeline("The size of an int is:  ", stdout);
		decout(sizeof(int), stdout);
		newline(stdout);

		writeline("The size of a short is:  ", stdout);
		decout(sizeof(short), stdout);
		newline(stdout);

		writeline("The size of a short int is:  ", stdout);
		decout(sizeof(short int), stdout);
		newline(stdout);

		writeline("The size of a long is:  ", stdout);
		decout(sizeof(long), stdout);
		newline(stdout);

		writeline("The size of a long int is:  ", stdout);
		decout(sizeof(long int), stdout);
		newline(stdout);

		writeline("The size of a long long is:  ", stdout);
		decout(sizeof(long long), stdout);
		newline(stdout);

		writeline("The size of a signed is:  ", stdout);
		decout(sizeof(signed), stdout);
		newline(stdout);

		writeline("The size of a signed char is:  ", stdout);
		decout(sizeof(signed char), stdout);
		newline(stdout);

		writeline("The size of a signed short is:  ", stdout);
		decout(sizeof(signed short), stdout);
		newline(stdout);

		writeline("The size of a signed short int is:  ", stdout);
		decout(sizeof(signed short int), stdout);
		newline(stdout);

		writeline("The size of a signed int is:  ", stdout);
		decout(sizeof(signed int), stdout);
		newline(stdout);

		writeline("The size of a signed long is:  ", stdout);
		decout(sizeof(signed long), stdout);
		newline(stdout);

		writeline("The size of a signed long int is:  ", stdout);
		decout(sizeof(signed long int), stdout);
		newline(stdout);

		writeline("The size of a signed long long is:  ", stdout);
		decout(sizeof(signed long long), stdout);
		newline(stdout);

		writeline("The size of an unsigned is:  ", stdout);
		decout(sizeof(unsigned), stdout);
		newline(stdout);

		writeline("The size of an unsigned char is:  ", stdout);
		decout(sizeof(unsigned char), stdout);
		newline(stdout);

		writeline("The size of an unsigned short is:  ", stdout);
		decout(sizeof(unsigned short), stdout);
		newline(stdout);

		writeline("The size of an unsigned short int is:  ", stdout);
		decout(sizeof(unsigned short int), stdout);
		newline(stdout);

		writeline("The size of an unsigned int is:  ", stdout);
		decout(sizeof(unsigned int), stdout);
		newline(stdout);

		writeline("The size of an unsigned long is:  ", stdout);
		decout(sizeof(unsigned long), stdout);
		newline(stdout);

		writeline("The size of an unsigned long int is:  ", stdout);
		decout(sizeof(unsigned long int), stdout);
		newline(stdout);

		writeline("The size of an unsigned long long is:  ", stdout);
		decout(sizeof(unsigned long long), stdout);
		newline(stdout);

		writeline("The size of a void pointer is:  ", stdout);
		decout(sizeof(void *), stdout);
		newline(stdout);

		writeline("The size of a character pointer is:  ", stdout);
		decout(sizeof(char *), stdout);
		newline(stdout);

		writeline("The size of an int pointer is:  ", stdout);
		decout(sizeof(int *), stdout);
		newline(stdout);

		writeline("The size of a long pointer is:  ", stdout);
		decout(sizeof(long *), stdout);
		newline(stdout);

		writeline("The size of a float pointer is:  ", stdout);
		decout(sizeof(float *), stdout);
		newline(stdout);

		writeline("The size of a double pointer is:  ", stdout);
		decout(sizeof(double *), stdout);
		newline(stdout);

		writeline("The size of a long double pointer is:  ", stdout);
		decout(sizeof(long double *), stdout);
		newline(stdout);
		newline(stdout);

	}

	return 0;
}
