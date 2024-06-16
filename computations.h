void computation(QueueNode outputHead){

	
	int operand1;// = (int) ;
	int operand2;// = (int) ;
    char cOperator; // how tf did u do this wo c infront it


    switch (cOperator)
		{
		case '^':
			pow(operand1, operand2);
			break;
		case '*':
			operand1 * operand2;
			break;
		case '/':
			operand1 / operand2;
			break;
		case '+':
			operand1 + operand2;
			break;
            
		case '-':
			operand1 - operand2;
            break;
		case '>':
			if(operand1 > operand2)
				//1
			//else	//0;
			break;
		case '<':
			if(operand1 < operand2)
				//1
			//else	//0;
			break;

		case '!':
			if(operand1 < 1)
				//0;
			break;

		default:
		}
	

}

