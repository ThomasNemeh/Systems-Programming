/* Program to read in binary digits from input and display their correponding char once 8 digits have been read.
 * Authors: Thomas Nemeh and Lukas Griffin. 10/18/2018 */

#include "bits.c"

int main() {
	char input;
         while (EOF != (input = getchar())) {
                 decode_bits(input);
        }
}

