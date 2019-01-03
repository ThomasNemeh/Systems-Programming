/* Program which recieves text input from a file. Counts the number of times each letter occurs in a file and return this number as it is and as a percent. 
 * Also returns letter(s) with the highest and lowest frequencies.
 * Authors: Lukas Griffin and Thomas Nemeh. 10/18/2018 */
#include <stdio.h>
# define LENGTH 26

int main( ) {
  // creates an array of letter frequencies
  int input;
  int freq[LENGTH] ={0};
  float sum = 0;
  while (EOF != (input = getchar())) {
    //printf("This is the ascii num: %d\n", (int)input);
    if ((int)input >= 97 && (int)input <= 122) {
      freq[(int)input - 97]++;
      sum++;
    }

  }

  float percent;

  //Formats the frequencies
  printf("char\t\tFrequencies\t\tPercentage\n\n");

  char max[26] = {" "};
  char min[26] = {" "};
  int minFreq = 101;
  int maxFreq = 0;
  int counter = 0;
  int mincount = 0;
  int zeroFloat = 0;
  // prints out each letters frequency and percent
  for (int i=0; i < LENGTH; i++){
    int c;
    c = i + 97;
    percent = (float)freq[i]/sum;
    printf("%c:\t\t%d\t\t\t%f\n", (char)c, freq[i], percent);

    //deals with max character
    if (freq[i] > maxFreq){
      counter = 0;
      max[counter] = c;
      maxFreq = freq[i];
      //  counter++;
    }
    if ((freq[i] == maxFreq) && (max[counter] != c)){
      counter++;
      max[counter] = c;
      //counter++;
    }

    //deals with min character
    if ((freq[i] < minFreq) && (freq[i] != zeroFloat)){
      min[mincount] = c;
      minFreq = freq[i];
    }
    if ((freq[i] == minFreq) && (min[mincount] != c)){
      mincount++;
      min[mincount] = c;
    }

  }
  // prints out max  char(s)
  printf("Maximum character(s): ");
  for (int m=0; m <= counter; m++){
    if (m == counter)
      printf("%c ", (int)max[m]-32);
    else
      printf("%c, ", (int)max[m]-32);
  }
     

  printf("\n");
  // prints out min char(s)
  printf("Minimum character(s): ");
  for (int l=0; l <= mincount; l++){
    if (l == mincount){
      printf("%c ", (int)min[l]-32);
    } else {
      printf("%c, ", (int)min[l]-32);
    }
  }
     
  printf("\n");
  return 0;
}     
  
