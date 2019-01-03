//Author Thomas Nemeh. September 14, 2018.
//Description: encrpys file or user input using rot128 encryption algorithm.

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#define RANGE ((UCHAR_MAX + 1) / 2)

int main() {
   int input;

    while (EOF != (input = getchar())) {
	putchar(((char) input) + RANGE);
     }
}


