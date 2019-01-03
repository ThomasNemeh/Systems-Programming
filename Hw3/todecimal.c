/* Program that reads number from input and displays them in decimal format.
 * Authors: Thomas Nemeh and Lukas Griffin. 10/18/2018. */

#include "getnum.c"

//print out number in decimal format
int main() {
	while (input != EOF) {
		//get next number in input
		long num = getNum();
		if (!(error > 0)) {
			if (negative > 0) {
				//if negative flag is set to '1', print '-' first
				printf("%c%lu\n",'-', num);
			} else {
				printf("%lu\n", num);
			}
		} else {
			//indicate that there is an error if given number does not follow any specified format
			printf("%s\n", "ERROR");
		}
	}
}
