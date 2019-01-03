/* Program that converts numbers in input to octal format, starting with '0'
 * Authors: Lukas Griffin and Thomas Nemeh. 10/18/2018 */ 

#include "getnum.c"

int main() {
        while (input != EOF) {
                //get next number in input
                long num = getNum();
                if (!(error > 0)) {
                        if (negative > 0) {
                                //if negative, print '-' first
                                printf("%c", '-');
                                printf("%c", '0');
                                tooctal(num);
                        } else {
                                printf("%c", '0');
                                tooctal(num);
                        }
                } else {
                        //signal to the user that there was a number that does not comply with any specified format
                        printf("%s\n", "ERROR");
                }
        }
}
