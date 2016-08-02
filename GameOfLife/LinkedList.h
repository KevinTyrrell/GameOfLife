/*
Author: Kevin Tyrrell
Date: 7/21/2016
Version: 1.4
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Structures
struct ll_Node
{
	void *data;
	struct ll_Node *next, *prev;
};

struct LinkedList
{
	struct ll_Node *root, *tail;
	size_t _size;
};

// Constructors.
struct LinkedList* LinkedList_new();
static struct ll_Node* ll_Node_new(void *data);

// Functions.
static struct ll_Node* ll_find(struct LinkedList *list, unsigned int index);
void ll_add(struct LinkedList *list, void *data);
void ll_addAt(struct LinkedList *list, unsigned int index, void *data);
void ll_addLast(struct LinkedList *list, void *data);
void ll_removeAt(struct LinkedList *list, unsigned int index);
bool ll_remove(struct LinkedList *list, void *data);
void ll_removeFirst(struct LinkedList *list);
void ll_removeLast(struct LinkedList *list);
void ll_clear(struct LinkedList *list);
struct LinkedList* ll_clone(const struct LinkedList *list);
// Deconstructor. Call with &list.
void ll_destroy(struct LinkedList *list);
void ll_print(struct LinkedList *list);