// Technically, this is the same as the StackNode. It's more so
// to prevent queue operations from being performed on a stack and vice versa.
struct QueueNode {
	char data[MAX_STRING_LEN];
	struct QueueNode *next;
};

typedef struct QueueNode QueueNode;

/*
 * queueEmpty() returns a boolean depending on whether the queue is empty or not.
 * @param **headPtr Pointer to the head of the queue.
 * @param **tailPtr Pointer to the tail of the queue.
 * @return Boolean depending on whether the queue is empty or not.
 */
bool queueEmpty(QueueNode **headPtr, QueueNode **tailPtr)
{
	if (headPtr == NULL || tailPtr == NULL) {
		return true;
	} else {
		return false;
	}
}

/*
 * enqueue() adds a node to the tail of the queue.
 * @param **headPtr Pointer to the head of the queue.
 * @param **tailPtr Pointer to hte tail of the queue.
 * @param data[] String data to add to the node.
 */
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, char *data)
{
	// Allocate memory to a new QueueNode.
	QueueNode *newNode = malloc(sizeof(QueueNode));

	// Set next QueueNode to NULL.
	newNode->next = NULL;

	// Set data in new QueueNode.
	strncpy(newNode->data, data, sizeof(newNode->data));
	newNode->data[sizeof(newNode->data) - 1] = '\0';

	if (*headPtr == NULL && *tailPtr == NULL) {
		*headPtr = *tailPtr = newNode;
	} else {
		// Set next pointer of current tail QueueNode to newly-created QueueNode.
		(*tailPtr)->next = newNode;

		// Set tail pointer to newly-created QueueNode.
		*tailPtr = newNode;
	}
}

/*
 * dequeue() removes a node from the head of the queue.
 * @param **headPtr Pointer to the head of the queue.
 * @param **tailPtr Pointer to the tail of the queue.
 */
bool dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	QueueNode *temp;

	if (queueEmpty(headPtr, tailPtr)) {
		return false;
	} else {
		temp = *headPtr;
		*headPtr = (*headPtr)->next;

		free(temp);
		return true;
	}
}