/*
 * priority() returns a priority value given a character mathematical operator.
 * In the Shunting Yard algorithm, operator priority is used to determine whether to
 * push an operator into a stack or into the output.
 * Constraints: Mode can only be 'c' or 's'.
 * @param operator: Mathematical operator.
 * @param mode: Changes return value based on whether operator to check is in-stack (s) or incoming (c).
 * @return Integer priority value.
 */
int priority(char operator, char mode)
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
			return 7;
		case '!':
			return 6;
		case '^':
			return 5;
		case '*':
		case '/':
			return 4;
		case '+':
		case '-':
			return 3;
		case '>':
		case '<':
			return 2;
		default:
			return -1;
		}
	} else if (mode == 's') {
		switch (operator)
		{
		case '(':
			return 8;
		case '!':
			return 7;
		case '^':
			return 6;
		case '*':
		case '/':
			return 4;
		case '+':
		case '-':
			return 3;
		case '>':
		case '<':
			return 2;
		default:
			return -1;
		}
	} else {
		return 0;
	}
}

/*
 * This function compares the priority of the operator from the input
 * to the priority of the operator in stack.
 * @param operator Incoming character.
 * @param **operatorHead Pointer to operator stack.
 */
void comparePriority(char incomingOperator, StackNode **operatorHead, QueueNode **outputHead, QueueNode **outputTail)
{
	StackNode *current;
	char inStackOperator;

	// Strings in C require a null character at the end to properly display without garbage values.
	char buffer[2];

	current = *operatorHead;

	if (stackEmpty(*operatorHead)) {
		return;
	} else {
		if (!stackEmpty(*operatorHead)) {
			inStackOperator = current->data;
		}

		if (incomingOperator == '(') {
			push(operatorHead, incomingOperator);
		} else if (incomingOperator == ')') {
			while (inStackOperator != '(' && current != NULL) {
				strncpy(buffer, &incomingOperator, 1);

				enqueue(outputHead, outputTail, buffer);
				pop(operatorHead);
				current = *operatorHead;

				strcpy(buffer, "\0");
			}

			pop(operatorHead);
		} else if (priority(incomingOperator, 'c') <= priority(inStackOperator, 's')) {
			while (!stackEmpty(*operatorHead) && priority((*operatorHead)->data, 's') >= priority(incomingOperator, 'c')) {
				strncpy(buffer, &inStackOperator, 1);
				enqueue(outputHead, outputTail, buffer);
				pop(operatorHead);

				strcpy(buffer, "\0");
			}
		}
	}
}

/*
 * infixToPostfix() takes an input string in infix notation, like: 1+2*3
 * and converts it to postfix notation, like so: 1 2 3 * +.
 * Constraints: Input string must be formatted correctly with no spaces or line breaks. Invalid operators are not allowed.
 * @param input[] Input string in infix form.
 * @param **operatorHead Pointer to head of operator stack.
 * @param **outputHead Pointer to head of output queue.
 * @param **outputTail Pointer ot tail of output queue.
 */
void infixToPostfix(char input[], StackNode **operatorHead, QueueNode **outputHead, QueueNode **outputTail)
{
	int i;
	int inputLength = strlen(input);

	// A buffer is used to keep operands of > 1 digit together, to be enqueued as one element.
	char buffer[MAX_STRING_LEN];

	// When using strcpy() to copy a single character over,
	// it will copy additional garbage data unless there is a
	// null terminator, so we need to put the char in a string before enqueueing.
	char enqueueBuffer[2];

	// Each character in the input string is called a "token".
	char token;

	// In the end, all operators remaining in stack will be popped from stack -> output queue.
	// To do this, we must iterate through each element, and this tracks which element we're on.
	StackNode *current;

	// While there are input tokens, read each individual token.
	for (i = 0; i < inputLength; i++) {
		token = input[i];

		// If the token is a number, add it to the buffer.
		if (isdigit(token)) {
			strncat(buffer, &token, 1);
		} else { // Otherwise, it's an operator.
			// Enqueue the element in the buffer into the output queue.
			enqueue(outputHead, outputTail, buffer);

			// Clear the buffer.
			strcpy(buffer, "\0");

			// Compare the priority of the incoming operator from the input and the in-stack operator.
			comparePriority(token, operatorHead, outputHead, outputTail);

			if (token != ')') {
				push(operatorHead, token);
			}
		}
	}

	// Enqueue last element in buffer to output queue, and clear the buffer.
	// We do this because the enqueue() function is only called when an operator is found after an operand.

	// Enqueue buffer contents into output queue and clear the buffer.
	if (strcmp(buffer, "\0") != 0) {
		enqueue(outputHead, outputTail, buffer);
		strcpy(buffer, "\0");
	}

	// Pop all remaining operators in stack to output queue.
	current = *operatorHead;
	while (current != NULL) {
		// Removing this buffer will result in garbage data being copied over,
		// alongside the operator.
		enqueueBuffer[0] = current->data;
		enqueue(outputHead, outputTail, enqueueBuffer);
		current = current->next;
	}
}