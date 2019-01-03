/*program to encode text files to huf files. Authors: Thomas Nemeh, Lukas Griffin. December 8, 2018*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
# define LENGTH 257
#define MAX_LEN 30

int gPath[LENGTH] = {[0 ... (LENGTH - 1)] = -1};
int bits = 0;

// linked lists element
struct Node {
  int freq;
  char letter;
  struct Node *prev, *next;
  struct Node *left, *right;
};

//finds the bitpath of a character and adds it to the gloal path
void nodePaths(struct Node *node, int path[], int pathPos){
  //if node equals nothing
  if (node == NULL)
    return;
  pathPos++;
  
  //if the node is a leaf 
  if (node->left == NULL && node->right == NULL){
    if (node->letter != '\0') {
      gPath[(int) node->letter] = 0;
      for (int i=0; i < pathPos; i++){
	if (path[i] == 0) {
	  gPath[(int) node->letter] = gPath[(int) node->letter] * 10;
	}
	else {
	  gPath[(int) node->letter] = gPath[(int) node->letter] * 10 + 1;
	}
      }
    }
    else {
      gPath[LENGTH - 1] = 0;
      for (int i=0; i < pathPos; i++){
	if (path[i] == 0) {
	  gPath[LENGTH - 1] = gPath[LENGTH-1] * 10;
	}
	else {
	  gPath[LENGTH - 1] = gPath[LENGTH - 1] * 10 + 1;
	}
      }
    }
  } else {
  // go left
    path[pathPos] = 1;
    nodePaths(node->left, path, pathPos);
 
      // go right
    path[pathPos] = 0;
    nodePaths(node->right, path, pathPos);
  }
 
}

//Print linked list for debugging purposes
void printNewNode (struct Node *head){
  while (head != NULL) {
    if (head->letter == '\n')
      printf("\\n: %d\n", head->freq);
    else
      printf("%c: %d\n", head->letter, head->freq);
    head = head->prev;
  }
  printf("\n");
}

//insert node into linked list
void insertNode(struct Node *head, struct Node *huffNode){
  while(huffNode->freq >= head->freq) { 
    // if there is one element in the list break otherwise traverse
    if (head->prev == NULL)
      break;
    else
      head = head->prev;
  }
  if (head->next != NULL) {
    huffNode->next = head->next;
    huffNode->prev = head;
    head->next->prev = huffNode;
    head->next = huffNode;
    //printNewNode(huffNode);
  }
  else {
    //change so that it moves node to right before head
    head->prev = huffNode;
    huffNode->next = head; 
  }
}

//Reads in binary digit in input and display corresponding char value when 8 digits have been read
void decode_bits(int ch, FILE* output){

  //buffer to store each binary digit we read
  static char outputBuffer[CHAR_BIT];
  static char* outBptr = outputBuffer;
  static int count = 0;

  //exit program when non-binary digit is read
  if (!isspace(ch) && !(ch == '0' || ch == '1')){

    printf("%s\n", "You entered a non-binary digit. Shutting down...");

    exit(1);

  } else if (!isspace(ch)){ //else add digit to buffer

    *outBptr = ch;

    outBptr++;
    count++;

  }


  //if CHAR_BIT digits are in the buffer, print out char
  if (count == CHAR_BIT) {

    int sum = 0;

    int digitVal = 1;

    for (int i = CHAR_BIT - 1; i >= 0; i--){

      if (outputBuffer[i] == '1') {
	sum += digitVal;
      }

      digitVal = digitVal*2;

    }

    fprintf(output, "%c", sum);

    outBptr = outputBuffer;
    count = 0;
  }

}

//prints out given long to console in binary format (starting with '0b')
void tobinary(int num, FILE* output){
  
	//The maximum value of a long on our machine has 19 digits. To be safe, we allocate an array with 30 spaces
  	int binaryFormat[CHAR_BIT];
	//Add digits from most significant to least significant to buffer, starting at the end of the buffer 
  	for (int i=CHAR_BIT - 1; i >= 0; i--) {
	       
	  if (num == 0) {
	    binaryFormat[i] = 0;
	    //bits++;
	  }
	  else {
	    int remainder = num % 2;
	    num = num / 2;
	    binaryFormat[i] = remainder;
	    //bits++;
  	  }
	}
	
 	//Print digits from least significant to most significant, starting at the point in the buffer where the firs digit is located
  	for (int j=0; j <= CHAR_BIT - 1; j++) {
	  fprintf(output, "%d", binaryFormat[j]);
	  bits++;
  	}
	//fprintf(output, "%s", " ");
}

//preorder traversal of tree, outputting 1 for tree node and 0 for leaf node
void preorder(struct Node *node, FILE* output) {
  if (node->left == NULL) {
    fprintf(output, "%d", 1);
    bits++;
    tobinary((int) node->letter, output);
  }
  else {
    fprintf(output, "%d", 0);
    bits++;
    preorder(node->right, output);
    preorder(node->left, output);
  }
}

//returns the number of digits in a number
int length(const unsigned n) {
    if (n < 10) return 1;
    return 1 + length(n / 10);
}

//prints contents of file as bitpaths in our huffman tree
void printFileContents(FILE* input, FILE* output) {
  int next;
  while (EOF != (next = fgetc(input))) {
    fprintf(output, "%d", gPath[next]);
    bits += length(gPath[next]);
  }
  fprintf(output, "%d", gPath[LENGTH - 1]);
  bits += length(gPath[LENGTH - 1]);
}

//padding to make number of bits in file a multiple of CHAR_BITS
void padding(FILE* output) {
  //int remaining = bits % CHAR_BIT;
  //fprintf(output, "%d\n", CHAR_BIT);
  while (bits % CHAR_BIT != 0) {
    bits++;
    fprintf(output, "%d", 0);
  }
}

//convert binary to chars
void encodeFile(FILE* intermediate, FILE* finalOutput) {
  int input;
  while (EOF != (input = fgetc(intermediate))) {
    decode_bits(input, finalOutput);
  }
}

int main(int argc, char* argv[]) {
  // creates an array of letter frequencies
  int input;
  int freq[LENGTH] ={0};

  //If you have time, add usage
  FILE* inputFile = fopen(argv[1], "r");
  FILE* outputFile = fopen("intermediate", "w+");
  FILE* finalOutput = fopen(argv[2], "w");
  
  while (EOF != (input = fgetc(inputFile))) {
    //    printf("This is the ascii num: %d\n", (int)input);
    freq[(int)input]++;
  }
  // checks if freq array works
  /*for (int m=0; m <= LENGTH; m++) {
    if (freq[m] != 0)
      printf("%d\n", freq[m]);
  }
  */
  // sorts array of letter frequencies and array of characters based off of this
  char letters[LENGTH];
  letters[256] = '\0';      // EOF char
  freq[256] = 1; // EOF freq
  for (int n=0; n <= LENGTH; n++)
    letters[n] = n;
  int marker = 1;
  for (int i=1; i < LENGTH; i++){    // loops through elements of freq
    for (int j = 0; j < marker; j++) {   // loops through sorted section of freq
      if (freq[i] > freq[j]) {      // switches letter frequencies if one is less than the other
	int freq_temp = freq[i];
	freq[i] = freq[j];
	freq[j] = freq_temp;

	int letter_temp = letters[i];         // switches letters within letter array
	letters[i] = letters[j];
	letters[j] = letter_temp;
      }
    }
    marker++;
  }
  struct Node *oldNode = NULL; //previous node we read in
  struct Node *newNode = NULL; //node we are currently reading in
  int nodeCount = 0;
  //creates LL
  for (int k=0; k < LENGTH; k++){
    if (freq[k] != 0) {
      newNode = malloc(sizeof(*newNode));
      if (newNode == NULL) {
	printf("%s\n", "Malloc Failed");
	exit(3);
      }
      // assign letter and its freq to a node in the LL
      newNode->freq = freq[k];
      newNode->letter = letters[k];
      // set the node's prev as the old node and its next as NULL
      newNode->prev = oldNode;
      newNode->next = NULL;
      // if the oldNode doesn't equal Null set the oldnode's next equal to newNode and then set oldNode equal newNode
      if (oldNode != NULL)
	oldNode->next = newNode;
      oldNode = newNode;
      nodeCount++;
      //  print output to check if list is sorted
      /* if (letters[k] == '\n')
      	printf("\\n: %d\n", freq[k]);
      else       
	printf("%c: %d\n", letters[k], freq[k]);
      */
    } 
  }
  // while there are more than 2 elements create a node of the elements with the lowest freq and then insert it into the linked list
  //nodeCount--; //temp line just to handle case w/o EOF!!!!!!!!
  //printf("nodecount: %d\n", nodeCount);
  //printf("Pass: \n");
  //printNewNode(newNode);
  struct Node *huffNode = NULL;
  while (nodeCount > 2) {
    huffNode = malloc(sizeof(*newNode));
    huffNode->freq = newNode->freq + newNode->prev->freq;
    huffNode->letter = '?';
    huffNode->left = newNode;
    huffNode->right = newNode->prev;
    
    //printNewNode(newNode);
    //printf("huffNode: %c = %d\n", huffNode->letter, huffNode->freq);
    //printf("newNode: %c = %d\n", newNode->letter, newNode->freq);
    // remove two children nodes
    newNode = newNode->prev->prev;
    newNode->next = NULL;
    //printf("newnewNode:  %c = %d\n", newNode->letter, newNode->freq);
    //    printf("nodecount: %d\n", nodeCount);
    nodeCount--;
    //printf("Pass:\n");
    insertNode(newNode, huffNode);
    //printNewNode(newNode);
    //free(huffNode);   
    }
  //free(huffNode);
  
  //printNewNode(newNode);
  struct Node *treeRootNode = NULL;
  treeRootNode = malloc(sizeof(*newNode));
  treeRootNode->freq = newNode->freq + newNode->prev->freq;
  treeRootNode->letter = '?';
  treeRootNode->right = newNode;
  treeRootNode->left = newNode->prev;
  newNode = treeRootNode;
  

  // create an array to hold the path's string
  int path[1000] = {0};
  // call the nodePath function
  nodePaths(newNode, path, -1);

  // we can now iterate through the node with gPath
  preorder(newNode, outputFile);
  //fprintf(outputFile, "%d\n", bits);
  
  //Now for the preorder traversal 
  
  fprintf(outputFile, "%d", gPath[256]);
  bits += length(gPath[256]);
  //fprintf(outputFile, "%d\n", bits);

  rewind(inputFile);
  printFileContents(inputFile, outputFile);

  //fprintf(outputFile, "\n");

  //fprintf(outputFile, "%d\n", bits);

  padding(outputFile);

  rewind(outputFile);
  encodeFile(outputFile, finalOutput);

    
  // free Node so we don't get any seg errors
  struct Node *next = NULL;
  while (newNode != NULL) {
    next = newNode->next;
    free(newNode);
    newNode = next;
  }

  
  
  fclose(inputFile);
  fclose(outputFile);
  fclose(finalOutput);
  remove("intermediate");
  
  return 0;
}
