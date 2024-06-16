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
			return 0;
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
		case '!':
			return 1;
		default:
			return 0;
		}
	} else if (mode == 's') {
		switch (operator)
		{
		case '(':
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
		case '!':
			return 1;
		default:
			return 0;
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
		inStackOperator = current->data;

		if (incomingOperator == '(') {
			push(operatorHead, incomingOperator);
		} else if (incomingOperator == ')') {
			while ((*operatorHead)->data != '(') {
				current = *operatorHead;
				inStackOperator = current->data;

				strncpy(buffer, &inStackOperator, 1);
				enqueue(outputHead, outputTail, buffer);
				pop(operatorHead);

				strcpy(buffer, "\0");
			}
		} else if (priority(incomingOperator, 'c') <= priority(inStackOperator, 's')) {
			while (!stackEmpty(*operatorHead)) {
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

			// Push the incoming operator into the stack.
			push(operatorHead, token);
		}
	}

	// Enqueue last element in buffer to output queue, and clear the buffer.
	// We do this because the enqueue() function is only called when an operator is found after an operand.

	// Let's trace an input!
	// Input: 1+22*3

	//                                                                    Input: 1+22*3
	//                                                                           ^
	// '1' is read and put into the buffer,                              Buffer: { 1 }
	//                                                           Operator Stack: { }
	//                                                             Output Queue: { }

	//                                                                    Input: 1+22*3
	//                                                                            ^
	// '+' is read, and because it's not a digit,                        Buffer: { 1 }
	//                                                           Operator Stack: { }
	//                                                             Output Queue: { }

	// buffer content is enqueued and buffer is cleared,                 Buffer: { }
	//                                                           Operator Stack: { }
	//                                                             Output Queue: { 1 }

	// '+' is compared against operator in stack (there is none)         Buffer: { }
	//                                                           Operator Stack: { }
	//                                                             Output Queue: { 1 }

	// so '+' is pushed to stack                                         Buffer: { }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1 }

	//                                                                    Input: 1+22*3
	//                                                                             ^
	// then, '2' is read and put into the buffer,                        Buffer: { 2 }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1 }

	//                                                                    Input: 1+22*3
	//                                                                              ^
	// then, the next '2' is read and put into the buffer,               Buffer: { 22 }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1 }

	//                                                                    Input: 1+22*3
	//                                                                               ^
	// '*' is read, and because it's not a digit,                        Buffer: { 22 }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1 }

	// buffer content is enqueued and buffer is cleared,                 Buffer: {  }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1, 22 }

	// '*' is compared against '+' in stack, but '+' has lower priority  Buffer: { }
	//                                                           Operator Stack: { + }
	//                                                             Output Queue: { 1, 22 }

	// so '*' is pushed to stack (remember pushing happens at head)      Buffer: { }
	//                                                           Operator Stack: { *, + }
	//                                                             Output Queue: { 1, 22 }

	//                                                                    Input: 1+22*3
	//                                                                                ^
	// then, '3' is read and put into the buffer,                        Buffer: { 3 }
	//                                                           Operator Stack: { *, + }
	//                                                             Output Queue: { 1, 22 }

	// then, there are no more elements left in input, so enqueue remaining buffer content into output queue.
	//                                                                   Buffer: { }
	//                                                           Operator Stack: { *, + }
	//                                                             Output Queue: { 1, 22, 3 }

	// lastly, pop all remaining elements from operator stack into output queue
	//                                                                   Buffer: { }
	//                                                           Operator Stack: { }
	//                                                             Output Queue: { 1, 22, 3, *, + }


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