/*
 * This function evaluates the expression between two operands and the operator
 * @param operator The operation to be applied to the expression
 * @param operand1 First operand in the expression.
 * @param operand2 Second operand in the expression.
 * @param result Result of the expression after the operator has been applied
 * @param divisionByZero Variable to be used to check if an expression will be divided by zero
 */
void evaluate(char *operator, int operand1, int operand2, int *result, bool *divisionByZero)
{
	// Set the variable that will catch division by zero
	*divisionByZero = false;

	// If statements to look for which operation to be used based on the operator
	if(strcmp(operator,"^") == 0){				// exponential
		*result = pow(operand1, operand2);
	} else if(strcmp(operator,"*") == 0){		// multiplication
		*result = operand1 * operand2;
	} else if(strcmp(operator,"/") == 0){		// division
		if(operand2 == 0) {
			*result = 0;
			*divisionByZero = true;
		} else {
			*result = operand1 / operand2;
		}
	} else if(strcmp(operator,"%") == 0){		// division
		if(operand2 == 0) {
			*result = 0;
			*divisionByZero = true;
		} else {
			*result = operand1 % operand2;
		}
	} else if(strcmp(operator,"+") == 0){		// addition
		*result = operand1 + operand2;
	} else if(strcmp(operator,"-") == 0){		// subtraction
		*result = operand1 - operand2;
	} else if(strcmp(operator,">") == 0){		// less than
		*result = operand1 > operand2;
	} else if(strcmp(operator,"<") == 0){		// greater than
		*result = operand1 < operand2;
	} else if(strcmp(operator,">=")  == 0){		// less than or equal
		*result = operand1 > operand2 ||
				  operand1 == operand2;
	} else if(strcmp(operator,"<=")== 0){		// greater than or equal
		*result = operand1 < operand2 ||
				  operand1 == operand2;
	} else if(strcmp(operator,"!=") == 0){		// non-equality
		*result = operand1 != operand2;
	} else if(strcmp(operator,"==") == 0){		// equality
		*result = operand1 == operand2;
	} else if(strcmp(operator, "&&")== 0){		// logical AND
		*result = operand1 && operand2;
	} else if(strcmp(operator,"||") == 0){		// logical OR
		*result = operand1 || operand2;
	} else if(strcmp(operator,"!") == 0){		// logical NOT
		*result = !operand1;
	}
}

/*
 * evaluatePostfix() takes the queue that contains the postfix expression, like so: 1 2 3 * +
 * and evaluates it, like so: 6.
 * @param **outputHead Pointer to head of output queue.
 * @param **outputTail Pointer ot tail of output queue.
 */
void evaluatePostfix(QueueNode **outputHead, QueueNode **outputTail)
{
	// Create a stack of operands.
	StackNode *operandStack;

	// Set current to queue head.
	QueueNode *current = *outputHead;

	// When operands are popped, they go here.
	int operands[2];

	bool divisionByZero = false;
	int result;

	char buffer[MAX_STRING_LEN] = "/0";

	// Iterate through queue.
	while (current != NULL) {
		// atoi() only returns 0 if the input is not a number.
		// If the incoming data is a number, it pushes it to the stack of operands
		if (atoi(current->data) != 0 || strcmp(current->data, "0") == 0) {
			push(&operandStack, current->data);
		// If the incoming data is the operator, we assign the operands then evaluate the 2 operands with the operator
		} else {
			// If the operator is a logical NOT, the top operand in the stack is assigned to the first operand
			if (strcmp(current->data, "!") == 0){
				operands[0] = atoi(operandStack->data);
				pop(&operandStack);
			// Else the top operand in the stack is assigned to the 2nd operand and
			// the next operand is assigned to the 1st operand then evaluate using the operator
			} else {
				operands[1] = atoi(operandStack->data);
				pop(&operandStack);
				operands[0] = atoi(operandStack->data);
				pop(&operandStack);
			}

			evaluate(current->data, operands[0], operands[1], &result, &divisionByZero);

			if (!divisionByZero) {
				sprintf(buffer, "%d", result);
				push(&operandStack, buffer);
				strcpy(buffer, "\0");
			}

			dequeue(outputHead, outputTail);
		}
		current = current->next;
	}
	//print the result after the computation else print statement for division by zero
	if(!divisionByZero) {
		printf("%d\n", result);
	} else {
		printf("Division by zero error!\n");
	}
}
