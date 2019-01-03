/* Program to read in Pig Latin text and translate to English text nondeterministically.
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
                printf("%c", input);    //print out intermediary punctuation
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

/* Converts string of Pig Latin to English and outputs result
 * If string supplied is not Pig Latin, do not change the word. */
void unpig(char word[], int nullPos) {
        // if Pig Latin word ends with 'yay', remove last 3 letters
        if (strcmp(word + (nullPos - 3), "yay") == 0 && isVowel(word[1])) {
                word[nullPos - 3] = '\0';
                printf("%s", word+1);
        }
        // if Pig Latin word ends with 'ay', remove last 2 letters and move one consonant before 'ay' to the front of the word 
        else if (strcmp(word + (nullPos - 2), "ay") == 0 && (isVowel(word[1]) || isY(word[1])) && !isVowel(word[nullPos - 3])) {
                word[0] = word[nullPos - 3];
                if (isupper(word[1])) {
                        word[1] = tolower(word[1]);
                        word[0] = toupper(word[0]);
                }
                word[nullPos - 3] = '\0';
                printf("%s", word);
        }
        //print out word as it is if it is not in Pig Latin
        else printf("%s", word+1);
}

/* Stores next word into an array and passes it to unpig() */
void readWord() {
        char word[110];
        int pos = 1;    //Start filling array at index 1 since we might need to move a letter to index 0 in unpig()     
        ungetc(input, stdin);

        //fill array with next word
        while (EOF != (input = getchar()) && (isalpha(input) || isdigit(input))) {
                word[pos++] = input;
        }
        ungetc(input, stdin);
        word[pos] = '\0';

        unpig(word, pos);
}

/* Print usage insutrctions */
void printUsage() {
    printf("%s\n", "USAGE:");
    printf("%s\n", "    ./unpig < inputfile [> outputfile]");
    printf("%s\n", "    echo [text] | ./unpig [> outputfile]");
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

                                                                                                                                                                                                                 

