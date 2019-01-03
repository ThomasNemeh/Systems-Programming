/*Program to read in characters from input and display their ascii values as binary numbers
 * Authors: Lukas Griffin and Thomas Nemeh. 10/18/2018 */

#include "bits.c"
#include "getnum.c"
#include <string.h>


int main(int argc, char** argv) {
	char input;
	//printf("%d\n", argc);
	if (argc == 2) {
		if (strcmp(argv[1], "-b") == 0) {
        		while (EOF != (input = getchar())) {
				print_bits(input);
			}
		}
		else if (strcmp(argv[1], "-h") == 0) {
  			while (EOF != (input = getchar())) {
                        	if (negative > 0) {
                                	printf("-");
                                	tohex(input);
                        	} else {
                               		tohex(input);
                        	}
			}
                		 
        	}
		else if (strcmp(argv[1], "-o") == 0) {
                        while (EOF != (input = getchar())) {
                                if (negative > 0) {
                                        printf("-");
                                        tooctal(input);
                                } else {
                                        tooctal(input);
                                }
                        }
        	}
		else printf("ERROR: command line argument options: -b -h -o");
	}
	else printf("ERROR: command line argument options: -b -h -o");

	return 0;
}

