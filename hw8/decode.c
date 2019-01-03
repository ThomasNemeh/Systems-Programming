/* Program to decode huf files into text. Authors: Thomas Nemeh, Lukas Griffin. December 18, 2018 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
# define LENGTH 257
#define MAX_LEN 30

int firstLine = 0;

//Node element for our huffman tree
struct Node {
  char letter;
  int eof;
  struct Node *left, *right;
};

//prints out given long to console in binary format 
void tobinary(int num, FILE* output){
  
	//The maximum value of a long on our machine has 19 digits. To be safe, we allocate an array with 30 spaces
  	int binaryFormat[CHAR_BIT];
	//Add digits from most significant to least significant to buffer, starting at the end of the buffer 
  	for (int i=CHAR_BIT - 1; i >= 0; i--) {
	       
	  if (num == 0) {
	    binaryFormat[i] = 0;
	  }
	  else {
	    int remainder = num % 2;
	    num = num / 2;
	    binaryFormat[i] = remainder;
  	  }
	}
	
 	//Print digits from least significant to most significant, starting at the point in the buffer where the firs digit is located
  	for (int j=0; j <= CHAR_BIT - 1; j++) {
	  fprintf(output, "%d", binaryFormat[j]);
  	}
}

//Reads in binary digit in input and display corresponding char value when 8 digits have been read
void decode_bits(int ch, struct Node *node){

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

    //printf("%c \n", sum);
    node->letter = sum;
    node->left = NULL;
    node->right = NULL;

    outBptr = outputBuffer;
    count = 0;
  }

}

//Reads the next CHAR_BIT bits of the huf file and converts to char which is letter value of our new node
void createNode(FILE* huf, struct Node *node) {
  int input;
  for (int i = 1; i <= CHAR_BIT; i++) {
    input = fgetc(huf);
    decode_bits(input, node);
  }
}	

//Reads in preorder traversal of huffman tree produced in encode.c and reconstructs the tree
void constructTree(FILE* huf, struct Node *root) {
  
    int input = fgetc(huf);
    //printf("%c", input);
    //If we are at a leaf, create a new node
    if (input == '1') {
      createNode(huf, root);
    }
    else {
      //Otherwise, create a left node and right node and recurse
      struct Node *rightNode = malloc(sizeof(*rightNode));
      rightNode->left = NULL;
      rightNode->right = NULL;
      rightNode->eof = 0;
      rightNode->letter = '0';
      root->right = rightNode;
      struct Node *leftNode = malloc(sizeof(*leftNode));
      leftNode->left = NULL;
      leftNode->right = NULL;
      leftNode->eof = 0;
      leftNode->letter = '0';
      root->left = leftNode;
      constructTree(huf, rightNode);
      constructTree(huf, leftNode);  
    }
  
}

//function for debugging, test accuracy of reconstruction
void preorder(struct Node *node) {
  if (node->left == NULL) {
    //printf("A");
    //printf("%c", node->letter);
  }
  else {
    preorder(node->right);
    preorder(node->left);
  }
}

//function for debugging, test accuracy of reconstruction
void freeHuff(struct Node *node) {
  if (node->left == NULL) {
    free(node);
  }
  else {
    freeHuff(node->right);
    freeHuff(node->left);
    free(node);
  }
}

//Mark the EOF node after constructing the huffman tree
void markEOF(FILE *huf, struct Node *node) {
  int input;
  while (EOF != (input = fgetc(huf))) {
    //printf("%c", input);
    if (input == '1') {
      node = node->left;
      if (node->letter != '0') break;
    }
    else {
      node = node->right;
      if (node->letter != '0') break;
    }
  }
  //printf("%d", (node->letter == '\0'));
  node->eof = 1;
}


//print out each char by iterating through huffman tree.
void decodeFile(FILE* huf, FILE* text, struct Node *node) {
  struct Node *root = node;
  int input;
  while (EOF != (input = fgetc(huf))) {
    //printf("%c", input);
    if (input == '1') {
      node = node->left;
      if (node->left == NULL) {
	//stop decoding if we at the eof node
	if (node->eof > 0) break;
	fprintf(text,"%c", node->letter);
	//printf("%c", node->letter);
	node = root;
      }
    }
    else {
      node = node->right;
      if (node->left == NULL) {
	//stop decoding if we are at the eof node
	if (node->eof > 0) break;
        fprintf(text,"%c", node->letter);
	//printf("%c", node->letter);
	node = root;
      }
    }
  }  
}

//convert huf file to bit and input in intermediate file
void tobits(FILE* huf, FILE* intermediate) {
  int input;
  while (EOF != (input = fgetc(huf))) {
    tobinary(input, intermediate);
  }
}

int main(int argc, char* argv[]) {
  //create files
  FILE* huf = fopen(argv[1], "r");
  FILE* intermediate2 = fopen("intermediate.txt", "w+");
  FILE* text = fopen(argv[2], "w");

  //decode huf to bits in intermediate file
  tobits(huf, intermediate2);

  //reconstruct huffman tree
  struct Node *root = malloc(sizeof(*root));
  root->eof = 0;
  root->letter = '0';
  root->left = NULL;
  root->right = NULL;
  rewind(intermediate2);
  constructTree(intermediate2, root);
 
  //preorder(root);

  //printf("\n");
  //printf("%d", isspace('\n'));

  //mark the eof node
  markEOF(intermediate2, root);

  //printf("\n");
  //decode to text
  decodeFile(intermediate2, text, root);
  
  fclose(huf);
  fclose(intermediate2);
  remove("intermediate.txt");
  fclose(text);

  freeHuff(root);
  
  return 0;
}
