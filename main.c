#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "postfix.h"

#define MAX_STRING_LEN 256 // Defined in specs.

/*
 * main() is a driver program.
 * @return Program exit status.
 */
int main()
{
	// Initialize linked list for operators.
	Node *operatorHead;

	// Store user input.
	char input[MAX_STRING_LEN];

	// Store postfix output.
	char postfixOutput[MAX_STRING_LEN];

	while (strcmp(input, "QUIT") != 0) {
		// Reset head pointer and input/output strings.
		operatorHead = NULL;
		input[0] = '\0';
		postfixOutput[0] = '\0';

		// Get user input.
		scanf("%s", input);

		if (strcmp(input, "QUIT") != 0) {
			// Call functions to convert from infix to postfix notation.
			infixToPostfix(input, strlen(input), postfixOutput, &operatorHead);
			displayPostfix(postfixOutput, strlen(input));

			printList(operatorHead);
			clearList(&operatorHead);
		}
	}
	return 0;
}