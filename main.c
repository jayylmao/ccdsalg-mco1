#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "queue.h"
#include "postfix.h"

#define MAX_STRING_LEN 256

/*
 * displayResult() prints the final output from the given input operations.
 */
void displayResult(Node *head)
{
	int i;

	Node *current = head;

	while (current->next != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
}

void displayPostfix(char *output, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%c ", output[i]);
	}
}

/*
 * main() is a driver program.
 * @return Program exit status.
 */
int main()
{
	// Initialize linked list for operators.
	Node *operatorHead = NULL;

	// Get user input.
	char input[MAX_STRING_LEN];
	char output[MAX_STRING_LEN];
	scanf("%s", input);

	// Call functions to convert from infix to postfix notation.
	infixToPostfix(input, strlen(input), output, &operatorHead);
	displayPostfix(output, strlen(input));

	printList(operatorHead);

	printf("\nlength: %d\n", length(operatorHead));
	printf("isEmpty: %d\n", isEmpty(operatorHead));
	printf("isFull: %d\n", isFull(operatorHead));
	return 0;
}