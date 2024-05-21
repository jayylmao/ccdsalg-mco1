
/*
 * infixToPostfix() converts a given string of math operations in infix notation to postfix notation.
 * Constraints: Correct formatting is assumed.
 * @param char input[]: Infix notation string.
 * @param int n: Length of input.
 * @param char output[]: Output postfix notation string.
 * @param Node **operatorHead: Pointer to operator linked list head.
 */
void infixToPostfix(char input[], int n, char output[], Node **operatorHead)
{
	int i;
	Node *current = *operatorHead;

	// How many elements are in output[]?
	int outputN = 0;

	for (i = 0; i < n; i++) {
		if (isdigit(input[i])) {
			output[outputN] = input[i];
			outputN++;
		} else {
			if (i == 0) {
				initializeList(operatorHead, input[i]);
			} else {
				push(operatorHead, input[i]);
			}
		}
	}
}

/*
 * printList() prints the contents of a given linked list.
 * @param Node *head: First element of a linked list.
 */
void printList(Node *head)
{
	Node *current = head;
	int i;

	while (current != NULL) {
		printf("%c ", current->data);
		current = current->next;
	}
}