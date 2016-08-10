
#include "Cell.h"

// Constructor function.
// X and Y coordinates need to be set before use.
struct Cell *Cell_new(unsigned int x, unsigned int y)
{
	struct Cell *born = malloc(sizeof(struct Cell));
	if (born == NULL)
		return NULL;
	born->x = x;
	born->y = y;
	born->flag = false;
	return born;
}

// Deconstructor function.
// When called, use Cell_destroy(&cell);
void Cell_destroy(struct Cell **cell)
{
	free(*cell);
	*cell = NULL;
}