/* Program to take in numberrs of any given length from stdin and display their sum. 
 * Authors: Thomas Nemeh and Lucas Griffin. 11/22/2018 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input; // stores chars read from stdin/file
int nextLine = 0; //signal to skip line when there is text after a number

//doubly linked list to hold numbers
struct BigInt {
  int digit;
  struct BigInt *next, *prev;
};

//print out the total in the accumulator
struct BigInt *printAcc(struct BigInt *acc) {
   printf("%s", "Total: ");
   while (acc->next != NULL) {
     printf("%d", acc->digit);
     acc = acc->next; 
   }
   printf("%d", acc->digit);
   printf("\n");

   return acc;
}

//Function called to free the data for each number we read in, starting from the front of the list
void freeBigInt(struct BigInt *head) {
    struct BigInt *next = NULL;
    while (head != NULL) {
	next = head->next;
	free(head);
	head = next;
    }
}

//Function called to free our accumulator, starting from the end of the list
void freeAcc(struct BigInt *tail) {
    struct BigInt *next = NULL;
    while (tail != NULL) {
	next = tail->prev;
	free(tail);
	tail = next;
    }
}

    
/*Reads in number and adds it to our accumulator
 * Called when stdin in brought to the beginning of each number */
struct BigInt* addNum(struct BigInt *acc){
  ungetc(input, stdin);
  
  struct BigInt *oldNode = NULL; //previous node we read in
  struct BigInt *newNode = NULL; //node we are currently reading in
  	
  while (EOF != (input = getchar()) && !isspace(input)) {
    
    //return accumulator if number is not valid
    if (!isdigit(input)) {
	while (acc->prev != NULL) {
	    acc = acc->prev;
	}
	nextLine = 1;
	return acc;
    }
    
    //construct new node in linked list
    newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
	printf("%s\n", "Malloc Failed");
	exit(3);
    }
    newNode->digit = input - '0';
    newNode->prev = oldNode;
    newNode->next = NULL; 

    if (oldNode != NULL) oldNode->next = newNode;
    oldNode = newNode;
  }
  
  //signal that we have not moved to a new line
  if (input != '\n') {
    nextLine = 1;
  }
  
  int add1 = 0; //boolean value to test when we must carry a 1
  struct BigInt* result = NULL; //value we are returning
  struct BigInt* head = NULL; //stores the first node that we must free of the list we have just created

  while (acc != NULL || newNode != NULL) {
    //If acc is longer than our new number, append the appropriate digits from acc to our result
    if (newNode == NULL) {
	if (add1 == 1) {
	    acc->digit += 1;
	    if (acc->digit >= 10) {
		acc->digit -= 10;
	    }
	    else add1 = 0;
	}
	result = acc;
	acc = acc->prev;
    }
    //If our number is longer than acc, append the appropriate digits from our number to the result
    else if (acc == NULL) {
	result->prev = newNode;
	if (add1 == 1) {
	    if (result->prev != NULL) {
		result->prev->digit += 1;
		if (result->prev->digit >= 10) {
		    result->prev->digit -= 10;
		}
		else {
		    add1 = 0;
		}
	    }
	}
	if (result->prev != NULL){
	    result->prev->next = result;
	    result = result->prev;
	    newNode = newNode->prev;
	}
    }
    else {
	//Perform the addition operation
	acc->digit = newNode->digit + acc->digit;
	
	//Signal if we must add 1 and subtract 10 from digit, since each node only holds one digit
	if (add1 == 1) {
	    acc->digit += 1;
	    add1 = 0;
	}

	if (acc->digit >= 10) {
	    acc->digit -= 10;
	    add1 = 1;
	}
	
	result = acc;
	acc = acc->prev;
	head = newNode;
	newNode = newNode->prev;
    
    }

  }

  //free the list of the number we have just read in
  freeBigInt(head);

    
  //Create a new leading digit if we carry the 1 all the way to the end
  if (add1 == 1) {
    //prtinff("%s\n", "ds");
    struct BigInt *leading = malloc(sizeof(*leading));
    if (leading == NULL) {
	printf("%s\n", "Malloc failed.");
	exit(3);
    }
    leading->digit = 1;
    leading->next = result;
    result ->prev = leading;
    leading->prev = NULL;
    result = result->prev;
  } 
  
  
  return result;

}

//Bring stdin to the beginning of a number, after skipping leading whitespace and zeros
struct BigInt* readNum(struct BigInt *acc){
  //move to next line if we are not already there
  if (nextLine == 1) {
    while (EOF != (input = getchar()) && input != '\n') {
	//do nothing
    }

    nextLine = 0;
  }

  //skip leading whitespace and zeros
  while (EOF != (input = getchar()) && (isspace(input) || input == '0')) {
    //Do Nothing
  }
  
  if (input != EOF) {
    //start reading number if we have reached a potential number
    return addNum(acc);
  }
  else {
    //free our accumulator and return NULL if we reach EOF
    freeAcc(acc);
    return NULL;
  }
}

int main() {
  //construct our accumulator
  struct BigInt *accumulator = malloc(sizeof(struct BigInt));
  if (accumulator == NULL) {
    printf("%s\n","Malloc Failed");
  }   
  accumulator->digit = 0;
  accumulator->prev = NULL;
  accumulator->next = NULL;

  //continually read in numbers and add them to our accumulator, displaying the result
  while (EOF != input) {
        accumulator  = readNum(accumulator); // enter in end of accumulator, takes you to begginning
	if (accumulator != NULL) accumulator = printAcc(accumulator); // enter in beginning of accumulator, takes you to end of accumulator
  }
  
  return 0;
}

