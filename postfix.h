/*
 * operatorPriority() returns a priority value given a character mathematical operator.
 * In the Shunting Yard algorithm, operator priority is used to determine whether to
 * push an operator into a stack or into the output.
 * Constraints: Mode can only be 'c' or 's'.
 * @param char operator: Mathematical operator.
 * @param char mode: Changes return value based on whether operator to check is in-stack (s) or incoming (c).
 * @return Integer priority value.
 */
int operatorPriority(char operator, char mode)
{
	// TODO: Figure out logical and boolean operator priority level.
	// ICP = incoming priority, ISP = in-stack priority
	// OPERATOR | ICP | ISP
	//    (     |  6  |  0
	//    ^     |  5  |  4
	//    *     |  3  |  3
	//    /     |  3  |  3
	//    +     |  2  |  2
	//    -     |  2  |  2
	//    >     |  1  |  1
	//    <     |  1  |  1
	if (mode == 'c') {
		switch (operator)
		{
		case '(':
			return 0;
		case '^':
			return 4;
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		case '>':
		case '<':
			return 1;
		default:
			return 0;
		}
	} else if (mode == 's') {
		switch (operator)
		{
		case '(':
			return 6;
		case '^':
			return 5;
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		case '>':
		case '<':
			return 1;
		default:
			return 0;
		}
	} else {
		return 0;
	}
}

/*
 * printList() prints the contents of a given linked list.
 * @param Node *head: First element of a linked list.
 */
void printList(Node *head)
{
	Node *current = head;

	// Print data in each node until there is no next node.
	while (current != NULL) {
		printf("%s ", current->data);
		current = current->next;
	}

	printf("\n");
}

/*
 * infixToPostfix() converts a given string of math operations in infix notation to postfix notation.
 * Constraints: Correct formatting is assumed.
 * @param char input[]: Infix notation string.
 * @param int n: Length of input.
 * @param char output[]: Output postfix notation string.
 * @param Node **operatorHead: Pointer to operator linked list head.
 */
void infixToPostfix(char input[], int n, Node **operatorHead)
{
	int i;

	// How many elements are in postfixStr[]?
	// int elemCount = 0;

	// bool isInParenthesis = false;

	// Initialize empty buffer.
	// Buffer is used to store operands of > 1 length (21, 305, etc.).
	char buffer[MAX_STRING_LEN] = "\0";

	// Set in-stack priority to 0 because it's blank.
	int incomingPriority, inStackPriority = 0;

	// Current Node for iterating through each element in the linked list.
	Node *current;

	// TODO: Complete the logic for postfix conversion.
	// TODO: Determine if output should be a string/array or linked list.
	//
	// # String/array
	// Pros: easier access
	// Cons: can't easily set multi-digit numbers. Can't do integer array either because we need to represent operators in output as well.
	//
	// # Linked list
	// Pros: multi-digit numbers.
	// Cons: need to create another version of node/recreate node structure because it only accommodates one char in data.
	for (i = 0; i < n; i++) {
		// Check if input char is digit.
		if (isdigit(input[i])) {
			strncat(buffer, &input[i], 1);
		} else if (!isdigit(input[i]) && input[i] != ')') { // Second condition likely temporary.
			// If operator is found, print operand currently in the buffer.
			printf("%s ", buffer);

			// Clear buffer.
			strcpy(buffer, "");

			// Set incoming priority based on current character.
			incomingPriority = operatorPriority(input[i], 'c');

			// Set in-stack priority if stack is not empty.
			if (!isEmpty(*operatorHead)) {
				inStackPriority = operatorPriority((*operatorHead)->data[0], 's');
			} else {
				initializeList(operatorHead, &input[i]);
			}

			// If incoming priority is greater than in-stack priority, print to screen.
			if (incomingPriority > inStackPriority) {
				printf("%c ", input[i]);
			} else { // Otherwise, push to stack. Not sure where to pop().
				push(operatorHead, &input[i]);
			}
		}
	}

	// Print last character in buffer.
	printf("%s ", buffer);
	// Clear buffer.
	strcpy(buffer, "");

	// Print all remaining operators in stack when input is empty.
	current = *operatorHead;

	while (current != NULL) {
		printf("%s ", current->data);
		current = current->next;
	}

	printf("\n");
}