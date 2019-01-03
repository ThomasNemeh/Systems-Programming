/* Program that prints out input numbers in hexadecimal format, starting with '0x'
 * Author: Lukas Griffin and Thomas Nemeh. 10/18/2018. */

#include "getnum.c"

int main() {
        while (input != EOF) {
                //get next number in input
                long num = getNum();
                if (!(error > 0)) {
                        if (negative > 0) {
                        	//print '-' first if negative flag is set to '1'
                                printf("%c", '-');
                                //print out hexadecimal signifier
                                printf("0x");
                                tohex(num);
                        } else {
                                printf("0x");
                                tohex(num);
                        }
                } else {
                        //indicate that there is an error if given string does not follow any specified format
                        printf("%s\n", "ERROR");
                }
        }

	return 0;

}

