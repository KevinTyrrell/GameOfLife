
#include "LinkedList.h"

/* Constructor function. */
static struct ll_Node* ll_Node_new(void *data);
/* Helper function. Locates a Node by index in the LinkedList. */
static struct ll_Node* ll_find(struct LinkedList *list, unsigned int index);

/* Constructor function. */
struct LinkedList* LinkedList_new()
{
	struct LinkedList *temp = malloc(sizeof(struct LinkedList));
	temp->root = NULL;
	temp->tail = NULL;
	temp->_size = 0;
	return temp;
}

/* Constructor function. */
static struct ll_Node* ll_Node_new(void *data)
{
	struct ll_Node *temp = malloc(sizeof(struct ll_Node));
	temp->data = data;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

/* 
Helper function. Locates a Node by index in the LinkedList. 

O(log n) complexity.
Prints an error if the index was out of bounds.
Returns NULL if the Node cannot be located.
*/
static struct ll_Node* ll_find(struct LinkedList *list, unsigned int index)
{
	if (index > list->_size)
		fprintf(stderr, "%s%u%s%zu%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
	else if (list->_size > 0)
		if (index == 0)
			return list->root;
		else if (index == list->_size - 1)
			return list->tail;
		else
		{
			struct ll_Node *temp;

			if ((double)index / list->_size > 0.5)
			{
				// Seek from the tail.
				temp = list->tail;
				for (size_t i = list->_size - 1; i > index; i--)
					temp = temp->prev;
			}
			else
			{
				// Seek from the root.
				temp = list->root;
				for (unsigned int i = 0; i < index; i++)
					temp = temp->next;
			}

			return temp;
		}

	return NULL;
}

/* 
Adds data at the front of the LinkedList.

O(1) complexity.
*/
void ll_add(struct LinkedList *list, void *data)
{
	struct ll_Node *inserted = ll_Node_new(data);

	if (list->_size == 0)
	{
		list->root = inserted;
		list->root->next = NULL;
		list->root->prev = NULL;
		list->tail = list->root;
	}
	else
	{
		inserted->next = list->root;
		list->root->prev = inserted;
		list->root = inserted;
	}

	list->_size++;
}

/*
Adds data at the given index in the LinkedList.

O(log n) complexity (worst case).
Prints an error if the index is out of bounds.
*/
void ll_addAt(struct LinkedList *list, unsigned int index, void *data)
{
	if (index > list->_size)
	{
		fprintf(stderr, "%s%u%s%zu%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
		return;
	}
	else if (index == 0)
		ll_add(list, data);
	else if (index == list->_size)
		ll_addLast(list, data);
	else
	{
		struct ll_Node *temp = ll_find(list, index),
			*added = ll_Node_new(data);
		added->prev = temp->prev;
		added->next = temp;
		temp->prev->next = added;
		temp->prev = added;
		list->_size++;
	}
}

/*
Adds data to the end of the LinkedList.

O(1) complexity.
*/
void ll_addLast(struct LinkedList *list, void *data)
{
	if (list->_size == 0)
		ll_add(list, data);
	else
	{
		struct ll_Node *added = ll_Node_new(data);
		added->prev = list->tail;
		list->tail->next = added;
		list->tail = added;
		list->_size++;
	}
}

/*
Removes a Node at the given index.

O(log n) complexity (worst case).
Prints an error if the index is out of bounds.
*/
void ll_removeAt(struct LinkedList *list, unsigned int index)
{
	if (index >= list->_size)
	{
		fprintf(stderr, "%s%u%s%zu%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
		return;
	}
	else if (index == 0)
		ll_removeFirst(list);
	else if (index == list->_size - 1)
		ll_removeLast(list);
	else
	{
		struct ll_Node *temp = ll_find(list, index);
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);
		list->_size--;
	}
}

/* 
Attempts to remove a Node with matching data, if it exists. 

O(log n) complexity (worst case).
Returns false if it could not locate a matching Node.
*/
bool ll_remove(struct LinkedList *list, void *data)
{
	struct ll_Node *seek = list->root;
	while (seek != NULL)
	{
		if (seek->data == data)
		{
			if (list->_size == 1)
				ll_clear(list);
			else if (seek->prev == NULL)
				ll_removeFirst(list);
			else if (seek->next == NULL)
				ll_removeLast(list);
			else
			{
				seek->prev->next = seek->next;
				seek->next->prev = seek->prev;
				free(seek);
				list->_size--;
			}
			
			return true;
		}
		seek = seek->next;
	}

	return false;
}

/*
Removes the first Node of the LinkedList.

O(1) complexity.
*/
void ll_removeFirst(struct LinkedList *list)
{
	if (list->_size > 0)
	{
		if (list->_size == 1)
			ll_clear(list);
		else
		{
			list->root = list->root->next;
			free(list->root->prev);
			list->root->prev = NULL;
			list->_size--;
		}
	}
}

/* 
Removes the last Node of the LinkedList.

O(1) complexity.
*/
void ll_removeLast(struct LinkedList *list)
{
	if (list->_size > 0)
		if (list->_size == 1)
			ll_clear(list);
		else
		{
			list->tail = list->tail->prev;
			free(list->tail->next);
			list->tail->next = NULL;
			list->_size--;
		}
}

/* 
Destroys every Node of the LinkedList. 

O(n) complexity.
*/
void ll_clear(struct LinkedList *list)
{
	struct ll_Node *garbageTruck = list->root;
	while (garbageTruck != NULL)
	{
		struct ll_Node *temp = garbageTruck;
		free(garbageTruck);
		garbageTruck = temp;
	}

	list->root = NULL;
	list->tail = NULL;
	list->_size = 0;
}

/* 
Returns a copy of the LinkedList.

O(n) complexity.
*/
struct LinkedList* ll_clone(const struct LinkedList *list)
{
	if (list == NULL)
		return NULL;

	struct LinkedList *copy = LinkedList_new();
	struct ll_Node *seek = list->root;
	while (seek != NULL)
	{
		ll_addLast(copy, seek->data);
		seek = seek->next;
	}

	return copy;
}

/* 
Deconstructor function. Call with &list.

O(n) complexity.
*/
void ll_destroy(struct LinkedList *list)
{
	struct ll_Node *garbageTruck = list->root;
	while (garbageTruck != NULL)
	{
		struct ll_Node *temp = garbageTruck;
		garbageTruck = garbageTruck->next;
		free(temp);
	}
	free(list);
}

/* 
Prints out the LinkedList to the console window. 

O(n) complexity.
Attempts to cast the void* data into char*.
*/
void ll_print(struct LinkedList *list)
{
	printf("%c", '{');

	struct ll_Node *seek = list->root;
	while (seek != NULL)
	{
		printf(" %s", (char*)seek->data);
		if (seek->next != NULL)
			printf("%c", ',');
		seek = seek->next;
	}

	printf(" }\n");
}