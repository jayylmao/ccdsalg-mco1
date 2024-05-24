/*
 * operatorPriority() returns a priority value given a character mathematical operator.
 * In the Shunting Yard algorithm, operator priority is used to determine whether to
 * push an operator into a stack or into the output.
 * @param char operator: Mathematical operator.
 * @return Integer priority value.
 */
int operatorPriority(char operator)
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
	switch (operator)
	{
	case '(':
	case ')':
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
}

/*
 * infixToPostfix() converts a given string of math operations in infix notation to postfix notation.
 * Constraints: Correct formatting is assumed.
 * @param char input[]: Infix notation string.
 * @param int n: Length of input.
 * @param char output[]: Output postfix notation string.
 * @param Node **operatorHead: Pointer to operator linked list head.
 */
void infixToPostfix(char input[], int n, char postfixStr[], Node **operatorHead)
{
	int i;

	// How many elements are in postfixStr[]?
	int elemCount = 0;

	bool isInParenthesis = false;

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
			postfixStr[elemCount] = input[i];
			elemCount++;
		} else if (input[i] == '(' || input[i] == ')') {
			isInParenthesis = !isInParenthesis;
		} else if (!isdigit(input[i]) && isInParenthesis) {
			postfixStr[elemCount] = input[i];
			elemCount++;
		} else if (!isdigit(input[i])) {
			if (i == 0) {
				initializeList(operatorHead, input[i]);
			} else {
				push(operatorHead, input[i]);
			}
		}
	}
}

void displayPostfix(char *postfixStr, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%c ", postfixStr[i]);
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
		printf("%c ", current->data);
		current = current->next;
	}

	printf("\n");
}