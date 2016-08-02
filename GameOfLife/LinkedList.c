
#include "LinkedList.h"

// Constructor for the LinkedList.
struct LinkedList* LinkedList_new()
{
	struct LinkedList *temp = malloc(sizeof(struct LinkedList));
	temp->root = NULL;
	temp->tail = NULL;
	temp->_size = 0;
	return temp;
}

// Constructor for the ll_Node.
static struct ll_Node* ll_Node_new(void *data)
{
	struct ll_Node *temp = malloc(sizeof(struct ll_Node));
	temp->data = data;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

// Locates a ll_Node within the LinkedList based on the index.
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

// Inserts a ll_Node at the front of the LinkedList.
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

// Inserts a ll_Node at a given index inside the LinkedList.
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

// Inserts a ll_Node at the end of the LinkedList.
// O(1) complexity.
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

// Remove's a ll_Node at a given index.
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

// Remove's the first ll_Node whose data matches the parameter, if it exists.
bool ll_remove(struct LinkedList *list, void *data)
{
	struct ll_Node *temp = list->root;
	while (temp != NULL)
	{
		if (temp->data == data)
		{
			if (list->_size == 1)
				ll_clear(list);
			else if (temp->prev == NULL)
				ll_removeFirst(list);
			else if (temp->next == NULL)
				ll_removeLast(list);
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
				list->_size--;
			}
			
			return true;
		}
		temp = temp->next;
	}

	return false;
}

// Remove's the first ll_Node in the LinkedList.
// O(1) complexity.
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

// Remove's the last ll_Node in the LinkedList.
// O(1) complexity.
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

// Clear the LinkedList of ll_Nodes.
// O(n) complexity.
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

// Copies a given LinkedList and returns the cloned version.
// O(n) complexity.
struct LinkedList* ll_clone(const struct LinkedList *list)
{
	if (list == NULL)
		return NULL;

	struct LinkedList *copy = LinkedList_new();
	struct ll_Node *root = list->root;
	while (root != NULL)
	{
		ll_addLast(copy, root->data);
		root = root->next;
	}

	return copy;
}

// Deconstructor.
// O(n) complexity.
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

// Prints out the LinkedList to the terminal window.
// O(n) complexity.
void ll_print(struct LinkedList *list)
{
	printf("%c", '{');

	struct ll_Node *temp = list->root;
	while (temp != NULL)
	{
		printf(" %s", (char*)temp->data);
		if (temp->next != NULL)
			printf("%c", ',');
		temp = temp->next;
	}

	printf(" }\n");
}