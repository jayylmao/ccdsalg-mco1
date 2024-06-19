// Note that the terms "linked list" and "stack" are used somewhat interchangeably.
// However, linked list is the data structure in C we are using to represent the stack
// in the program.

// StackNode structure for each element in the stack/linked list.
struct StackNode {
	char data[MAX_STRING_LEN];
	struct StackNode* next;
};

typedef struct StackNode StackNode;

/*
 * length() returns the number of elements in the list.
 * @param StackNode *head: The first element of the linked list.
 * @return Integer corresponding to the number of elements in the linked list.
 */
int length(StackNode *head)
{
	StackNode *current = head;
	int length = 0;

	while (current != NULL) {
		length++;
		current = current->next;
	}

	return length;
}

/*
 * stackEmpty() checks if the given list is empty.
 * @param StackNode *head: The first element of the linked list.
 * @return Boolean that states if the list is empty or not.
 */
bool stackEmpty(StackNode *head)
{
	if (head == NULL) {
		return true;
	} else {
		return false;
	}
}

/*
 * printStack() prints the contents of a given queue.
 * @param *head: First element of a queue.
 */
void printStack(StackNode *head)
{
	StackNode *current = head;

	// Print data in each node until there is no next node.
	while (current != NULL) {
		printf("%s ", current->data);
		current = current->next;
	}

	printf("\n");
}

/*
 * push() adds the element to the top of the stack.
 * @param StackNode **head: Pointer to first element of the linked list.
 * @param char data: Data to input into the stack.
 */
void push(StackNode **headPtr, char* data)
{
	// Allocate memory to a new StackNode.
	StackNode *newNode = malloc(sizeof(StackNode));

	// Set next StackNode to pointer to head of current list.
	if (headPtr == NULL) {
		newNode->next = NULL;
	} else {
		newNode->next = *headPtr;
	}

	// Set data in new StackNode.
	strcpy(newNode->data, data);

	// Set head to new StackNode.
	*headPtr = newNode;
}

/*
 * pop() removes the element at the top of the stack.
 * @param StackNode **head: Pointer to first element of the linked list.
 */
bool pop(StackNode **headPtr)
{
	StackNode *current = *headPtr;

	// Check for underflow.
	if (!stackEmpty(*headPtr)) {
		// Set pointer to head to pointer to next StackNode.
		*headPtr = current->next;

		// Free memory used by current StackNode.
		free(current);
		return false;
	}

	return true;
}

/*
 * top() returns the element at the top of the stack.
 * @param StackNode *head: The first element of the linked list.
 * @return The element on top of the stack.
 */
StackNode* top(StackNode *head)
{
	StackNode *current = head;

	// Last element in the stack has a NULL pointer to the next element because there is none.
	while (current != NULL) {
		current = current->next;
	}

	return current;
}

/*
 * clearStack() pops all elements from a given stack.
 * @param StackNode **headPtr
*/
void clearStack(StackNode **headPtr)
{
	StackNode *current = *headPtr;
	while (current != NULL) {
		pop(headPtr);
	}
}