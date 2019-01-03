//Author: Thomas Nemeh. September 14, 2018.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

// takes in user input and returns first digit of input. Returns -1 if EOF is encountered.
int getdigit() {
	int input = -1;

	while (EOF != (input = getchar()) && !isdigit( (char) input) ) {
		//do nothing
	}

	if (input == EOF) {
		return -1;
	} else {
		return input - '0';
	}

}

// Uses getdigit() to get value between 0-9 from user input and print out diamond of that height to the console.
int main() {
	printf("%s", "I will print a diamond for you, enter a size between 1-9: ");
	printf("%s", "\n");
	int height = getdigit();
	for (int i = 1; i <= height; i++) {

		for (int x = 1; x <= (height - i); x++) {
			printf("%s", " ");
		}

		for (int y = 1; y <= i * 2 - 1; y++) {
			printf("%s", "*");
		}

		printf("%s", "\n");
	}

	for (int i = height - 1; i >= 1; i--) {

		for (int x = 1; x <= (height - i); x++) {
					printf("%s", " ");
				}

				for (int y = 1; y <= i * 2 - 1; y++) {
					printf("%s", "*");
				}

				printf("%s", "\n");
		}


	return 0;
}





