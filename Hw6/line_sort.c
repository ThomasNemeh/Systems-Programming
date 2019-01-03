/* Program to read in lines of text on sort it alphabetically using strcmp(). 
 * -n flag: numberic sorting. -f flag: ignore case. -r flag: reverse order
 * Authors: Thomas Nemeh and Lucas Griffin. November 12, 2018. */

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_LINES (1024 * 1024)
#define LINE_LEN 1024

//value for flags initially set to false
int fold = 0;
int leadingNum = 0;
int reverse = 0;

//store chars from stdin
char input; 

//prints out given 2-D array
void printArray(char ** arr, int numLines) {
        for (int i = 0; i < numLines; i++) {
                printf("%s\n", arr[i]); 
        }

}

/* Brings input to beginning of the next word */
void skipLeadingSpace() {
        while (EOF != (input = getchar()) && isspace(input)) {
                //do nothing
        }

	ungetc(input, stdin);
}

/* Reads line and inputs it as a string in our 2-D array */
void readLine(char* line) {
        skipLeadingSpace();

        int pos = 0;    

        while (EOF != (input = getchar()) && (input != '\n')) {
                line[pos] = input;
                pos++;
        }

        line[pos] = '\0';
}

/* Swaps 2 lines in our array */
void swap(char** arr1, char** arr2) {
	char *placeholder = *arr1;
	*arr1 = *arr2;
	*arr2 = placeholder;
}

/* Returns long value corresponding to leading number in given the given string "start". 
 * If "start" does not begin with number, return 0.
 * "char**" rest is a pointer to the first character after the leading number. We pass this value by reference. */
long mystrtol(char* start, char** rest) {
    int negative = 0;
    int pos = 0;

    //test if leading num is negative
    if (start[0] == '-') {
	negative = 1;
	pos = 1;
    }
    long num = 0;
	
    //convert leading num from string to long
    while (start[pos] != '\0' && isdigit(start[pos])) {
	num = (num * 10) + (start[pos] - '0');
	pos++;
    } 

    //position of first char after leading digit
    *rest = start + pos;

    if (negative == 1) {
	return -1 * num;
    }
    else {
	return num;
    }
}

/* Our comparison function used in MergeSort, which takes our different flags into account. 
 * returns negative value if current is less than pivot, positive if current is greater than pivot,
 * and zero if they are the same */
int compare(char* current, char* pivot) {
	int compVal = 0;
	
	if (leadingNum == 0) {
	    if (fold == 0) {
			//If fold flag is 0, evaluate according to strcmp
                        compVal = strcmp(current, pivot);
                }
                else {
			//If fold flag is 1, ignore case
                        compVal = strcasecmp(current, pivot);
                }

	} else {
	    char* current_str = NULL;
	    char* pivot_str = NULL;
	    long current_num = mystrtol(current, &current_str);
	    long pivot_num = mystrtol(pivot, &pivot_str);
	    
            //If the leading nums are different, compare according to their values
	    if (current_num - pivot_num != 0) {
		compVal = current_num - pivot_num;
	    }
	    //If leading nums are the same, compare according to their subsequent strings
	    else {
		if (pivot_str[0] == '0' && current_str[0] == '0') {
			compVal =  0;
		} 
		else if (current_str[0] == '0') {
			compVal = -1;
		}
		else if (pivot_str[0] == '0') {
			compVal =  1;
		} 
		else if (fold == 0) {
			compVal =  strcmp(current_str, pivot_str); 
	    	}
		else {
			compVal =  strcasecmp(current_str, pivot_str);
		}
	    }
	}
	
	//If reverse flag is set to 1, return -1 * our value
	if (reverse != 0) {
		return -1 * compVal;
	}
	else {
		return compVal;
	}
}

/* Partition function for quicksort. Iterates through array and swaps every element less than to pivot
 * with the element to the right of the wall */
int partition(char** arr, int low, int high) {
	char* pivot = arr[high];
	int wall = low - 1;
	for (int i = low; i < high; i++) {
		if (compare(arr[i], pivot) <= 0) {
			wall++;
			swap(&arr[wall], &arr[i]);
		}		
	}
	
	wall++;
	swap(&arr[wall], &arr[high]);

	return wall;
}

/* Our implementation of MergeSort. */
void sort(char** arr, int low, int high) {
	if (low < high) {
		int wall = partition(arr, low, high);
		sort(arr, low, wall-1);
		sort(arr, wall+1, high);
	}
}

/* frees our array */ 
void freeArray(char** arr, int numLines) {
	for (int i = 0; i < numLines; i++) {
		free(arr[i]);
	}

	free(arr);
}

/* print usage instruction when incorrect flags are entered */
void printUsage() {
	printf("%s\n", "USAGE:");
    	printf("%s\n", "    ./line_sort < inputfile [> outputfile]");
    	printf("%s\n", "    echo [text] | ./line_sort [> outputfile]");
    	printf("%s\n", "NOTE: [...] denotes optional parameter");
	printf("%s\n", "OPTIONAL FLAGS:");
    	printf("%s\n", "    -f: ignore case");
    	printf("%s\n", "    -n: sort numerically according to leading number, from lowest to highest");
    	printf("%s\n", "    -r: reverse the order of the sort");
}

int main(int argc, char* argv[]) {
        char **arr = (char **)malloc(MAX_LINES * sizeof(char *));
        int numLines = 0;

	//Process command line input
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0 && fold == 0) {
			fold = 1;
		}
		else if (strcmp(argv[i],"-n") == 0 && leadingNum == 0) {
			leadingNum = 1;
		}
		else if (strcmp(argv[i], "-r") == 0 && reverse == 0) {
			reverse = 1;
		}
		else {
			printUsage();
			exit(1);
		}
	}        
	
	//fill a 2-D array with each line of input
        for (int i=0; i<MAX_LINES; i++) {
                if (input == EOF) {
                        break;
                }
                else {
                        arr[i] = (char *)malloc(LINE_LEN * sizeof(char)); 
                        readLine(arr[i]);
                        numLines++; 
                }
        }
	
	//Remove excess empty line
	free(arr[numLines - 1]);
	numLines -= 1;	
	
	//sort our array
	sort(arr, 0, numLines-1);

	//print the sorted array
	printArray(arr, numLines);

	//clean up
	freeArray(arr, numLines);
}

