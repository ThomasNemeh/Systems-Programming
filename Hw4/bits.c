/*File that defines function to read in chars and display their ascii value in binary, as well as a function to read binary numbers and display their corresponding char
 * Authors: Thomas Nemeh and Lukas Griffin. 10/18/2018 */

#include "bits.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

//Reads in chars in input and displays their ascii value in binary
void print_bits(int ch){

  //array to store binary value of char
  char binaryFormat[CHAR_BIT+1];


  //fill array of binary digits
  for (int i=CHAR_BIT; i >= 0; i--) {

    int remainder = ch % 2;

    ch = ch / 2;

    binaryFormat[i] = remainder + '0';

  }


  //print binary number
  printf("%s\n", binaryFormat);

}

//Reads in binary digit in input and display corresponding char value when 8 digits have been read
void decode_bits(int ch){
  
  //buffer to store each binary digit we read
  static char outputBuffer[CHAR_BIT];
  static char* outBptr = outputBuffer;
  static int count = 0;

  //exit program when non-binary digit is read
  if (!isspace(ch) && !(ch == '0' || ch == '1')){

    printf("%s\n", "You entered a non-binary digit. Shutting down...");

    exit(1);

  } else if (!isspace(ch)){ //else add digit to buffer
	
    *outBptr = ch;

    outBptr++;
    count++;

  }


  //if CHAR_BIT digits are in the buffer, print out char
  if (count == CHAR_BIT) {

    int sum = 0;

    int digitVal = 1;

    for (int i = CHAR_BIT - 1; i >= 0; i--){

      if (outputBuffer[i] == '1') {
        sum += digitVal;
      }

      digitVal = digitVal*2;

    }

    printf("%c\n", sum);

    outBptr = outputBuffer;
    count = 0;
  }

}
