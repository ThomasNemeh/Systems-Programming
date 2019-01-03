/* Program to read in English text and translate to Pig Latin.
 * Authors: Thomas Nemeh and Lucas Griffin. November 1st, 2018. */

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char input; //store chars read from stdin

/* Brings input to beginning of the next word
 * Encountering an alphanumeric character is considered reaching the next word. */
void nextWord() { 
        while (EOF != (input = getchar()) && !isalpha(input) && !isdigit(input)) {
		printf("%c", input);	//print out intermediary punctuation
        }

	//exit if end of file is reached
        if (input == EOF) {	
                exit(0);
        }
}

/* returns 1 if param is a vowel('Y' and 'y'  not included), 0 otherwise */
int isVowel(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		return 1;
	} else {
		return 0;
	}
}

/* returns 1 if param is 'Y' or 'y', 0 otherwise */
int isY(char c) {
	if (c == 'y' || c == 'Y') {
		return 1;
	}
	else {
		return 0;
	}	
}

/* Converts string of English to Pig Latin and outputs result */
void pig(char word[], int nullPos) {
	// if word begins in vowel, append yay to end of word
	if (isVowel(word[0])) {
		word[nullPos] = 'y';
		word[nullPos + 1] = 'a';
		word[nullPos + 2] = 'y';
		word[nullPos + 3] = '\0';
		printf("%s", word);
	}
	// if word begins with consonant, move all letter before first vowel to the end of word and append ay to the end of it 
	else {
		if (nullPos > 1) {
			int capital = 0;
                	if (isupper(word[0])) {
                        	capital = 1;
                                word[0] = tolower(word[0]);
                        }
			char c = word[0];
			int pos = 0;
			int originalNullPos = nullPos;
                	while (!isVowel(c) && !isY(c) && !(c == '\0')) {
                        	word[nullPos] = c;
				word[nullPos + 1] = '\0';
				nullPos++;
				pos++;
				c = word[pos];
                	}

			if (capital) {
				word[pos] = toupper(word[pos]);
			}

			if (isVowel(word[pos])) {
				word[nullPos] = 'a';
				word[nullPos + 1] = 'y';
				word[nullPos + 2] = '\0';
				printf("%s", word + pos);
			}
			else {
				word[originalNullPos] = '\0';
				printf("%s", word);
			}
			
		}
	} 
}

/* Stores next word into an array and passes it to unpig() */
void readWord() {
	char word[150];	
	int pos = 0;	
	ungetc(input, stdin);
	
	//fill array with next word
	while (EOF != (input = getchar()) && (isalpha(input) || isdigit(input))) {
		word[pos++] = input; 
        }
	ungetc(input, stdin);
	word[pos] = '\0';

	pig(word, pos);
}

/* Print usage insutrctions */
void printUsage() {
    printf("%s\n", "USAGE:");
    printf("%s\n", "	./pig < inputfile [> outputfile]");
    printf("%s\n", "	echo [text] | ./pig [> outputfile]");
    printf("%s\n", "NOTE: [...] denotes optional parameter");
}

int main(int argc, char* argv[]) {
	// If flag is supplied as argument, pring out usage instructions 
	if (argc > 1) {
	    if (argv[1][0] == '-') {
		printUsage();
		exit(1);
	    }
	}

	//While end of file has not been reached, read Pig Latin words and output them as English
	while (input != EOF) {
		nextWord();
		readWord();
	}
	
	return 0;
}

