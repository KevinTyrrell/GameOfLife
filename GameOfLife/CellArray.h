#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cell.h"

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

// Constructor.
struct CellArray *CellArray_new(size_t rows, size_t columns);
// Counts the number of live neighbors around a given index.
char CellArray_countN(struct CellArray *area, unsigned int x, unsigned int y, char stop);
// Deconstructor. Call with &area.
void CellArray_destroy(struct CellArray *area);
void CellArray_print(struct CellArray *area, unsigned long long generation);