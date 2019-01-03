/* Program that defines getnum() function, which reads the next binary, octal, hexadecimal, or decimal number
 * from standard input and converts it to a long.
 * Authors: Thomas Nemeh and Lucas Griffin. */

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#define ERROR LONG_MAX
#define MAX_LEN 30
#include "getnum.h"

int negative = 0;
int error = 0;
int input;
char type;
long num;

/* Brings input to beginning of the next string */
void skipWhiteSpace() {
	while (EOF != (input = getchar()) && isspace(input) ) {
		//do nothing
	}
	if (input == EOF) {
                exit(0);
        }
}

/* Skips current word.
   Called when there is an error in the number format */
void nextWord() {
	while (EOF != (input = getchar()) && !isspace(input) ) {
		//do nothing
	}

}

void checkNegative() {
	if (input == '-') {
		negative = 1;
	}
	else {
		ungetc(input, stdin);
	}
}

long readDecimal() {
	long sum = 0;

	//update value each time we read a char
	while (EOF != (input = getchar()) && !isspace(input) ) {
                if (!(input <= '9' && input >= '0')) {
			//return ERROR if char is not a digit
			error = 1;
			return ERROR;
		}
		else {
			sum = (sum * 10) + (input - '0');	
		} 
	}

	return sum; 
}

long readBinary() {
	input = getchar();
	if (input == EOF || isspace(input)) {
		//return ERROR if '0b' is followed by ' ' or EOF
		error = 1;
		return ERROR;
	}
	else {
		input = ungetc(input, stdin);   
		int sum = 0;

		//update value each time we read a char
		while (EOF != (input = getchar()) && !isspace(input)) {
			if (input == '1') {
				sum = sum * 2 + 1;
			}
			else if (input == '0') {
				sum = sum * 2;
			}
			else {
				//return ERROR if char is not '0' or '1'
				error = 1;
                                return ERROR;
			}
        	}

		return sum;
	}
}

long readHexadecimal() {
	input = getchar();
        if (input == EOF || isspace(input)) {
		//return ERROR if '0x' is followed by ' ' or EOF
		error = 1;
                return ERROR;
        }
        else {
                input = ungetc(input, stdin);
                int sum = 0;

		//update value each time we read a char
                while (EOF != (input = getchar()) && !isspace(input)) {
                        if (input >= '0' && input <= '9') {
                                sum = sum * 16 + (input - '0');
                        }
                        else if (input >= 'A' && input <= 'F') {
                                sum = sum * 16 + (input - 55); //ASCII value of 'A' is 65
                        }
                        else {
				//return ERROR if char is not '0' - '9' or 'A' - 'F'
				error = 1;
                                return ERROR;
                        }
                }

                return sum;
        }

}

long readOctal() {
        int sum = 0;

	//update value each time we read a char
        while (EOF != (input = getchar()) && !isspace(input)) {
        	if (input >= '0' && input <= '7') {
                	sum = (sum * 8) + (input - '0');
                }
                else {
			//return ERROR if char is not '0' - '7'
			error = 1;
                	return ERROR;
                }
	}
               
	 return sum;
}

/* brings program to beginning of the number(after type identifier) and calls
   function to read the correct type */
long checkTypeAndGetNum() {
	input = getchar();
	if (input != EOF) {
		//string must begin with a digit 
		if (input <= '9' && input >= '0') {
			if (input == '0') {
				input = getchar(); 
				if (input != 'b' && input != 'x' && !(input <= '7' && input >= '0')) {
					if (input == EOF || isspace(input)) {
						if (negative > 0) {
							//return ERROR if string is a '-' followed by '0'
							error = 1;
							return ERROR;
						}
						else {
							//return 0 if string is a single 0
							return 0;
						}
					
					}
					else {
						//return ERROR if second char does not follow any acceptable format
						error = 1;
						return ERROR;
					}
				}
				else {
					if (input == 'b') {
						//read binary if string start with '0b'
						return readBinary();
					}
					else if (input == 'x') {
						//read hexadecimal if string starts with '0x'
						return readHexadecimal();
					}
					else {
						//read octal if string starts with '0' followed by  '0' - '7'
						ungetc(input, stdin);
						return readOctal();
					}
				}
				
			}
			else {
				//read decimal if string starts with '1' - '9'
				ungetc(input, stdin);
				return readDecimal();
			}
		} else {
			//return ERROR if string does not start with a digit 
			error = 1;
			return ERROR;
		}
	}
	else {
		//program ends with '-' so we must indicate that there is an error. 
		error = 1;
		return ERROR;		
	}

}

//takes next number and converts it to a long, if it is in one of the given formats
long getNum() {
	negative = 0;
	error = 0;	

	skipWhiteSpace();

	checkNegative();

	long num = checkTypeAndGetNum();

	if (error > 0) {
		if (input == EOF) {
			printf("%s", "ERROR");
                	exit(0);
		}
		else {
			nextWord();
		}
	}

	return num;

}


//prints out given long in octal format (starting with '0') 
void tooctal(long num){
        // The maximum value of a long on our machine has 19 digits. To be safe, we allocate an array with 30 spaces
        char octalFormat[MAX_LEN];
        int count = 0;

        //Add digits to buffer from most significant to least significant digit, starting at the end of the buffer
        for (int i=MAX_LEN - 1; i >= 0; i--) {
                int remainder = num % 8;
                num = num / 8;
                octalFormat[i] = remainder;

                if (num == 0) {
                        break;
                }
                else {
                        count++;
                }
        }

        //print digits from least significant to most significant, starting at the point in the buffer where the first digit is located
        for(int k=MAX_LEN - count - 1; k < MAX_LEN; k++){
                printf("%d", octalFormat[k]);

        }

        printf("\n");

}

//prints out given long in hexadecimal format (starting with '0x')
void tohex(long num){

        char hexFormat[MAX_LEN];
        long count = 0;

        //add digits to buffer from most significant to least significant, starting at the end of the buffer
        for (int i=MAX_LEN - 1; i >= 0; i--) {

                int remainder = num % 16;
                num = num / 16;
                hexFormat[i] = remainder;

                if (num != 0) {
                        count++;
                } else {
                        break;
                }
        }

        //print hexadecimal number from least significant digit to most significant, starting at the point in the buffer where the first digit is located
        for(int k=MAX_LEN - count - 1; k < MAX_LEN; k++){

                printf("%X", hexFormat[k]);

        }
	printf("\n");
}

