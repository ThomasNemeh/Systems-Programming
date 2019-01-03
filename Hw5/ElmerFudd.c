/* Program to read in English text and translate to Elmer Fudd speak nondeterministically.
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

/* Shifts each element of the array down 1 index so the first element is removed */
void removeFirstElement(char *array) {
        int pos = 0;
        while (array[pos] != '\0') {
                array[pos] = array[pos + 1];
                pos++;
        }
}

/* Converts string in English to ElmerFuddish and outputs result */
void toElmer(char word[], int len) {
        if (len > 1) {
                int startPos = 0;
                //Convert 'Th' to 'D'
                if (word[0] == 'T' && word[1] == 'h') {
                        word[1] = 'D';
                        startPos = 1;
                }
                for (int i = startPos; i < len; i++) {
                        //Convert 'r' and 'l' to 'w'
                        if (word[i] == 'r' || word[i]== 'l') {
                                word[i] = 'w';
                        }
                        //Convert 'R' and 'L' to 'W'
                        else if (word[i] == 'R' || word[i] == 'L') {
                                word[i] = 'W';
                        }
                        //Convert 'ith' to 'if'
                        else if (i <= len - 3 && (word[i] == 'i' || word[i] == 'I') && word[i + 1] == 't' && word[i + 2] == 'h') {
                                word[i + 1] = 'f';
                                removeFirstElement(word + i + 2);
                                len -= 1;
                        }
                        //Convert 'qu' to 'qw'
                        else if (i <= len - 2 && (word[i] == 'q'|| word[i] == 'Q') && word[i + 1] == 'u') {
                                word[i + 1] = 'w';
                        }
                }
                printf("%s", word + startPos);
        }
        else {
                if (word[0] == 'r' || word[0]== 'l') {
                        word[0] = 'w';
                }
                else if (word[0] == 'R' || word[0] == 'L') {
                        word[0] = 'W';
                }
                printf("%s", word);
        }

}

/* Stores next word into an array and passes it to toElmer() */
void readWord() {
        char word[110];
        int pos = 0;
        ungetc(input, stdin);

        //fill array with next word
        while (EOF != (input = getchar()) && (isalpha(input) || isdigit(input))) {
                word[pos++] = input;
        }
        ungetc(input, stdin);
        word[pos] = '\0';

        toElmer(word, pos);
}

/* Print usage insutrctions */
void printUsage() {
    printf("%s\n", "USAGE:");
    printf("%s\n", "    ./ElmerFudd < inputfile [> outputfile]");
    printf("%s\n", "    echo [text] | ./ElmerFudd [> outputfile]");
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

        //While end of file has not been reached, read English words and output them in Elmer
        while (input != EOF) {
                nextWord();
                readWord();
        }

        return 0;
}

                                                                                                                                                                                                                             


