/* Program that reads numbers from input and  displays them in binary format, starting with '0b'
 * Authors: Thomas Nemeh and Lukas Griffin. 10/18/2018. */

#include "getnum.c" 
#define MAX_LEN 30

//prints out given long to console in binary format (starting with '0b')
void tobinary(long num){
	
	//The maximum value of a long on our machine has 19 digits. To be safe, we allocate an array with 30 spaces
  	char binaryFormat[MAX_LEN];
  	int count = 0;

	//Add digits from most significant to least significant to buffer, starting at the end of the buffer 
  	for (int i=MAX_LEN; i >= 0; i--) {

    		int remainder = num % 2;
		num = num / 2;
		binaryFormat[i] = remainder + '0';

    		if (num != 0) {
			count++;
		} else {
			break;
		}
  	}

	//print binary signifier
  	printf("0b");

	//Print digits from least significant to most significant, starting at the point in the buffer where the firs digit is located
  	for (int j=MAX_LEN - count; j <= MAX_LEN; j++) {
    		printf("%c", binaryFormat[j]);
  	}

  	printf("\n");

}


int main() {
        while (input != EOF) {
		//get next number in input
                long num = getNum();
                if (!(error > 0)) {
                        if (negative > 0) {
				//print '-' first if negative flag is set to '1'
                                printf("%c", '-');
                                tobinary(num);
                        } else {
                                tobinary(num);
                        }
                } else {
			//Indicate that there is an error if number does not follow any specified format
                        printf("%s\n", "ERROR");
                }
        }
}

