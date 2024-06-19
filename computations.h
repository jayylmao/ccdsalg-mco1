void evaluate(char *operator, int operand1, int operand2, int *result, bool *divisionByZero)
{
	*divisionByZero = false;
	if(strcmp(operator,"^") == 0){
		*result = pow(operand1, operand2);
	} else if(strcmp(operator,"*") == 0){
		*result = operand1 * operand2;
	} else if(strcmp(operator,"/") == 0){
		if(operand2 == 0){
			printf("Division by zero error!");
			*divisionByZero = true;}
		else
			*result = operand1 / operand2;
	} else if(strcmp(operator,"+") == 0){
		*result = operand1 + operand2;
	} else if(strcmp(operator,"-") == 0){
		*result = operand1 - operand2;
	} else if(strcmp(operator,">") == 0){
		*result = operand1 > operand2;
	} else if(strcmp(operator,"<") == 0){
		*result = operand1 < operand2;
	} else if(strcmp(operator,">=")  == 0){
		*result = operand1 > operand2 || operand1 == operand2;
	} else if(strcmp(operator,"<=")== 0){
		*result = operand1 < operand2 || operand1 == operand2;
	} else if(strcmp(operator,"!=") == 0){
		*result = operand1 != operand2;
	} else if(strcmp(operator,"==") == 0){
		*result = operand1 == operand2;
	} else if(strcmp(operator, "&&")== 0){
		*result = operand1 && operand2;
	} else if(strcmp(operator,"||") == 0){
		*result = operand1 || operand2;
	} else if(strcmp(operator,"!") == 0){
		*result = !operand1;
	}
}

void evaluatePostfix(StackNode **operatorHead, QueueNode **outputHead, QueueNode **outputTail)
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
		// atoi() only returns 0 if the input is a letter.
		if (atoi(current->data) != 0 || strcmp(current->data, "0") == 0) {
			push(&operandStack, current->data);
		} else if (strcmp(current->data, "!") == 0){
			operands[0] = atoi(operandStack->data);
			pop(&operandStack);
			operands[1] = 1;

			evaluate(current->data, operands[0], operands[1], &result, &divisionByZero);
			sprintf(buffer, "%d", result);
			push(&operandStack, buffer);
			strcpy(buffer, "\0");
		} else {
			operands[1] = atoi(operandStack->data);
			pop(&operandStack);
			operands[0] = atoi(operandStack->data);
			pop(&operandStack);

			evaluate(current->data, operands[0], operands[1], &result, &divisionByZero);
			sprintf(buffer, "%d", result);
			push(&operandStack, buffer);
			strcpy(buffer, "\0");
		}

		current = current->next;
	}
if(!divisionByZero)
	printf("%d\n", result);
}
