int assignValue (char buffer[]){
	int num=0;
	for(int i=0; i<strlen(buffer); i++){
		num = num * 10 + ( buffer[i] - '0' );
	}
	return num;
}


void computation(StackNode **operatorHead, QueueNode **outputHead, QueueNode **outputTail){
	QueueNode *current = *outputHead;
	char buffer[MAX_STRING_LEN];
	strcpy(buffer, "\0");
	float temp=0;
	int operand1, operand2;
	
	strcat(buffer, current->data);
	if(isdigit(buffer[0])){ 
		operand1 = assignValue(buffer);
		strcpy(buffer, "\0");
	}
	
	
	current = current->next;
	strcat(buffer, current->data);

	if(isdigit(buffer[0])){ 
		operand2 = assignValue(buffer);
		strcpy(buffer, "\0");
	}

	// can delete in later stages
	printf("operand1: %d\n", operand1);
	printf("operand2: %d\n", operand2);

	current = current->next;

	
	char tempoperator = current;
	char operator[2]; 
	strcpy(operator,"\0");
	strncpy(operator, &tempoperator, 1);
	
	


	printf("%s", operator);

	if(strcmp(operator,"^")==0){
		temp = pow(operand1, operand2);
	}
	
	else if(strcmp(operator,"*")==0){
		temp = operand1 * operand2;
	}

	else if(strcmp(operator,"/")==0){
		if(operand2 == 0)
			printf("Division by zero error!");
		else
			temp = operand1 / operand2;
	}

	else if(strcmp(operator,"+")==0){
		temp = operand1 + operand2;
	}

	else if(strcmp(operator,"-")==0){
		temp = operand1 - operand2;
	}

	else if(strcmp(operator,">")==0){
		temp = operand1 > operand2;
	}

	else if(strcmp(operator,"<")==0){
		temp = operand1 < operand2;
	}

	else if(strcmp(operator,">=")==0){
		temp = operand1 > operand2 || operand1 == operand2;
	 	
	}			
	else if(strcmp(operator,"<=")==0){
		temp = operand1 < operand2 || operand1 == operand2;
	}
	else if(strcmp(operator,"!=")==0){
		temp = operand1 != operand2;
	}

	else if(strcmp(operator,"==")==0){
		temp = operand1 == operand2;
	}	

	else if(strcmp(operator, "&&")==0){
		temp = operand1 && operand2;
	}

	else if(strcmp(operator,"||")==0){
		temp = operand1 || operand2;
	}

	else if(strcmp(operator,"!")==0){
		temp = !operand1;
	}
	


		dequeue(outputHead, outputTail);
		printf("new queue: ");
		printQueue(*outputHead);

		current = current->next;
		strcat(buffer, current->data);
		if(isdigit(buffer[0]))
			printf("%s", buffer);



	
	
	printf("temp = %f\n", temp);
	
	temp = 0;

}

// switch (operator)
	// 	{
	// 	case '^':
	// 		temp = pow(operand1, operand2);
	// 		break;

	// 	case '*':
	// 		temp = operand1 * operand2;
	// 		break;

	// 	case '/':
	// 		temp = operand1 / (float) operand2;
	// 		break;

	// 	case '+':
	// 		temp = operand1 + operand2;
	// 		break;
            
	// 	case '-':
	// 		temp = operand1 - operand2;
    //         break;

	// 	case '>':
	// 		if(operand1 > operand2)
	// 			temp = 1;
	// 		else
	// 			temp = 0;
	// 		break;

	// 	case '<':
	// 		if(operand1 < operand2)
	// 			//1
	// 		//else	//0;
	// 		break;

	// 	case '!':
	// 		if(operand1 < 1)
	// 			temp = 0;
	// 		break;

	// 	default: