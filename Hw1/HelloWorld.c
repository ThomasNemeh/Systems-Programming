//Author: Thomas Nemeh. 
//Description: program that prints various sentences using printf.

#include <stdio.h>

int main() {
	printf("%s %d %s\n", "The diameter of the earth is", 7917, "miles");
	printf("%s %4d %s\n", "There are", 3000, "people in Oberlin, OH");
	printf("%s %f %s\n", "The earth's diameter is more precisely", 7917.5, "miles");
        printf("%s %1.3f %s\n", "The diameter of the moon is", 2.159, "thousand miles");
	printf("%.3f %s\n", .666, "is the devil's number, as a decimal point");
}
