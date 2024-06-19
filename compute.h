void evaluate(QueueNode *outputHead, QueueNode *outputTail)
{
	StackNode *evaluate = NULL;
	QueueNode *current = outputHead;
	// int operands[2];

	while (current != NULL) {
		if (atoi(current->data) != 0) {
			push(&evaluate, current->data);
		} else {

		}
		push(&evaluate, evaluate->data);
	}
}