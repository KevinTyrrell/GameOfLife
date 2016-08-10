
#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cell.h"

/* Used for the printing the CellArray. */
static const char DEAD = ' ', ALIVE = 254, WALL = '|', FLOOR = '-',
MAX_COLUMNS = 77, MAX_ROWS = 20;

/*
2D Array of Cell which is the grid in which Cells live.
A new CellArray is constructed on every single generation.
The old CellArray is destroyed while the new one is repopulated.
*/
struct CellArray
{
	struct Cell ***arr;
	unsigned int population;
	size_t rows, columns;
};

/* Constructor function. */
struct CellArray *CellArray_new(size_t rows, size_t columns);
/* Counts the number of live cells around a given index. */
char CellArray_countN(struct CellArray *area, unsigned int x, unsigned int y, char stop);
/* Deconstructor function. Call with &area. */
void CellArray_destroy(struct CellArray *area);
/* Prints out the CellArray to the console window. */
void CellArray_print(struct CellArray *area, unsigned long long generation);