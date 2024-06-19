/*
 * priority() returns a priority value given a character mathematical operator.
 * In the Shunting Yard algorithm, operator priority is used to determine whether to
 * push an operator into a stack or into the output.
 * Constraints: Mode can only be 'c' or 's'.
 * @param operator: Mathematical operator.
 * @param mode: Changes return value based on whether operator to check is in-stack (s) or incoming (c).
 * @return Integer priority value.
 */
int priority(char* operator, char mode)
{
	if (mode == 's') {
		if (strcmp(operator, "!") == 0) {
			return 6;
		} else if (strcmp(operator, "^") == 0) {
			return 5;
		} else if (strcmp(operator, "*") == 0 ||
				   strcmp(operator, "/") == 0 ||
				   strcmp(operator, "\%") == 0) {
			return 4;
		} else if (strcmp(operator, "+") == 0 ||
				   strcmp(operator, "-") == 0) {
			return 3;
		} else if (strcmp(operator, ">") == 0 ||
				   strcmp(operator, "<") == 0 ||
				   strcmp(operator, "<=") == 0 ||
				   strcmp(operator, ">=") == 0 ||
				   strcmp(operator, "!=") == 0) {
			return 2;
		} else if (strcmp(operator, "&&") == 0 ||
				   strcmp(operator, "||") == 0) {
			return 1;
		} else if (strcmp(operator, "(") == 0) {
			return 0;
		} else {
			return -1;
		}
	} else if (mode == 'c') {
		if (strcmp(operator, "!") == 0) {
			return 8;
		} else if (strcmp(operator, "(") == 0) {
			return 7;
		} else if (strcmp(operator, "^") == 0) {
			return 5;
		} else if (strcmp(operator, "*") == 0 ||
				   strcmp(operator, "/") == 0 ||
				   strcmp(operator, "\%") == 0) {
			return 4;
		} else if (strcmp(operator, "+") == 0 ||
				   strcmp(operator, "-") == 0) {
			return 3;
		} else if (strcmp(operator, ">") == 0 ||
				   strcmp(operator, "<") == 0 ||
				   strcmp(operator, "<=") == 0 ||
				   strcmp(operator, ">=") == 0 ||
				   strcmp(operator, "!=") == 0) {
			return 2;
		} else if (strcmp(operator, "&&") == 0 ||
				   strcmp(operator, "||") == 0) {
			return 1;
		} else {
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
void comparePriority(char* incomingOperator, StackNode **operatorHead, QueueNode **outputHead, QueueNode **outputTail)
{
	StackNode *current;

	current = *operatorHead;

	if (stackEmpty(*operatorHead) && strcmp(incomingOperator, "!") != 0) {
		return;
	} else {
		if (strcmp(incomingOperator, ")") == 0) {
			// If a right parenthesis is found,
			// Pop all operators into the queue until a left parenthesis is found.
			while (strcmp((*operatorHead)->data, "(") != 0 && current != NULL) {
				enqueue(outputHead, outputTail, (*operatorHead)->data);
				pop(operatorHead);
			}

			pop(operatorHead);
		} else if (strcmp(incomingOperator, "!") == 0) {
			return;
		} else if ((priority((*operatorHead)->data, 's') >= (priority(incomingOperator, 'c')) &&
				   strcmp((*operatorHead)->data, "(") != 0)) {
			while (!stackEmpty(*operatorHead) && priority((*operatorHead)->data, 's') >= priority(incomingOperator, 'c')) {
				enqueue(outputHead, outputTail, (*operatorHead)->data);
				pop(operatorHead);
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
	char buffer[MAX_STRING_LEN] = "\0";
	char operatorBuffer[2];

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
		} else if ((token == '<' && input[i + 1] == '=') ||
				   (token == '>' && input[i + 1] == '=') ||
				   (token == '!' && input[i + 1] == '=') ||
				   (token == '=' && input[i + 1] == '=') ||
				   (token == '|' && input[i + 1] == '|') ||
				   (token == '&' && input[i + 1] == '&')) {
			// Enqueue the element in the buffer into the output queue as long as the buffer isn't empty.
			if (strcmp(buffer, "\0") != 0) {
				enqueue(outputHead, outputTail, buffer);
			}

			// Clear the buffer.
			strncpy(buffer, "\0", 1);

			// Since we want to add multiple tokens at once, we put them in a buffer, like with multi-digit
			sprintf(buffer, "%c%c", token, input[i + 1]);
			comparePriority(buffer, operatorHead, outputHead, outputTail);
			push(operatorHead, buffer);

			strncpy(buffer, "\0", 1);
			i++;
		} else { // Otherwise, it's an operator.
			// Enqueue the element in the buffer into the output queue as long as the buffer isn't empty.
			if (strcmp(buffer, "\0") != 0) {
				enqueue(outputHead, outputTail, buffer);
			}

			// Clear the buffer.
			strncpy(buffer, "\0", 1);

			// Compare the priority of the incoming operator from the input and the in-stack operator.
			comparePriority(&token, operatorHead, outputHead, outputTail);

			// Push operator to stack as long as it is not a parenthesis.
			if (token != ')') {
				strncpy(operatorBuffer, &token, 1);
				push(operatorHead, operatorBuffer);
				strncpy(operatorBuffer, "\0", 1);
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
		enqueue(outputHead, outputTail, current->data);
		pop(&current);
	}
}