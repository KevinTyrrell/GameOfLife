#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
Cell which represents a real-world living cell.
Dead cells in this program will be repsented as a
NULL struct Cell, thus there is no need for flags
if a cell is alive or not.
*/
struct Cell
{
	// Locations of this Cell within the array.
	unsigned int x, y;
	bool flag;
};

// Constructor.
struct Cell *Cell_new(unsigned int x, unsigned int y);
// Deconstructor. Call with &cell.
void Cell_destroy(struct Cell **cell);