#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STRING_LEN 256 // Defined in specs.

#include "queue.h"
#include "stack.h"
#include "postfix.h"
#include "computations.h"


// last update 6 / 17 / 24 



/*
 * main() is a driver program.
 * @return Program exit status.
 */
int main()
{
	// Initialize operator stack.
	StackNode *operatorHead;

	// Initialize output queue.
	QueueNode *outputHead;
	QueueNode *outputTail;

	// Store user input.
	char input[MAX_STRING_LEN];

	outputHead = NULL;
	outputTail = NULL;

	// User must type "QUIT" to exit the program.
	while (strcmp(input, "QUIT") != 0) {
		// Reset head pointer
		operatorHead = NULL;

		outputHead = NULL;
		outputTail = NULL;

		// Get user input.
		scanf("%s", input);

		if (strcmp(input, "QUIT") != 0) {
			// Call functions to convert from infix to postfix notation.
			infixToPostfix(input, &operatorHead, &outputHead, &outputTail);
			compute(outputHead);
			printQueue(outputHead);
		}
	}
	return 0;
}

