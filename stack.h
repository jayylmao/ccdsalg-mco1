// Note that the terms "linked list" and "stack" are used somewhat interchangeably.
// However, linked list is the data structure in C we are using to represent the stack
// in the program.

// Node structure for each element in the stack/linked list.
struct Node {
	char data;
	struct Node* next;
};

typedef struct Node Node;

/*
 * length() returns the number of elements in the list.
 * @param Node* head: The first element of the linked list.
 * @return Integer corresponding to the number of elements in the linked list.
 */
int length(Node* head)
{
	Node *current = head;
	int length = 0;

	while (current != NULL) {
		length++;
		current = current->next;
	}

	return length;
}

/*
 * isEmpty() checks if the given list is empty.
 * @param Node* head: The first element of the linked list.
 * @return Boolean that states if the list is empty or not.
 */
bool isEmpty(Node* head)
{
	int listLength = length(head);

	if (listLength == 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * isFull() checks if the given list is empty.
 * @param Node* head: The first element of the linked list.
 * @return Boolean that states if the list is full or not.
 */
bool isFull(Node* head)
{
	Node *current = head;
	int listLength = length(head);

	if (listLength != 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * initializeList() adds the first element to the top of the stack.
 * @param Node** head: Pointer to first element of the linked list.
 * @param char data: Data to input into the stack.
 */
void initializeList(Node** headPtr, char data)
{
	// Allocate memory to a new Node.
	Node *newNode = (Node *) malloc(sizeof(Node));

	// Set data in new Node.
	newNode->data = data;

	// Set next Node to pointer to head of current list.
	newNode->next = NULL;

	// Set head to new Node.
	*headPtr = newNode;
}

/*
 * push() adds the element to the top of the stack.
 * @param Node** head: Pointer to first element of the linked list.
 * @param char data: Data to input into the stack.
 */
void push(Node** headPtr, char data)
{
	// Allocate memory to a new Node.
	Node *newNode = malloc(sizeof(Node));

	// Set data in new Node.
	newNode->data = data;

	// Set next Node to pointer to head of current list.
	newNode->next = *headPtr;

	// Set head to new Node.
	*headPtr = newNode;
}

/*
 * pop() removes the element at the top of the stack.
 * @param Node** head: Pointer to first element of the linked list.
 */
void pop(Node** headPtr)
{
	if (!isEmpty(*headPtr)) {
		Node *current = *headPtr;

	}
}

/*
 * top() returns the current node.
 * @param Node* head: The first element of the linked list.
 * @return The element on top of the stack.
 */
Node* top(Node* head)
{
	Node *current = head;

	while (current != NULL) {
		current = current->next;
	}

	return current;
}