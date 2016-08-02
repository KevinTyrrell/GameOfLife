
#include "CellArray.h"

// Constructor function.
struct CellArray *CellArray_new(size_t rows, size_t columns)
{
	struct Cell ***arr = malloc(rows * sizeof(struct Cell**));
	if (arr == NULL)
		return NULL;
	
	for (size_t i = 0; i < rows; i++)
	{
		arr[i] = calloc(columns, sizeof(struct Cell*));
		if (arr[i] == NULL)
			return NULL;
	}

	struct CellArray *area = malloc(sizeof(struct CellArray));
	area->arr = arr;
	area->rows = rows;
	area->columns = columns;
	area->population = 0;
	return area;
}

// Count how many non-NULL Cells surround this index, inclduing diagonals.
// Keep searching around this index until `stop` number of Cells are counted.
// Stop exists so we do not do unneccesary searching.
char CellArray_countN(struct CellArray *area, unsigned int x, unsigned int y, char stop)
{
	if (x >= area->columns || y >= area->rows)
	{
		fprintf(stderr, "%s%u,%u%s%zu%zu%s\n",
			"Error: Index Out of Bounds. Index was '(",
			x, y, ")' but array is [", area->columns, area->rows, "].");
		return -1;
	}
	
	char count = 0;
	for (unsigned int i = (x == 0) ? 0 : x - 1; i < area->columns && i <= x + 1; i++)
		for (unsigned int h = (y == 0) ? 0 : y - 1; h < area->rows && h <= y + 1; h++)
		{
			// Ignore the source Cell.
			if (i == x && h == y)
				continue;
			if (area->arr[h][i] != NULL && area->arr[h][i]->flag == false && ++count >= stop)
				return count;
		}

	return count;
}

// Deconstructor function.
void CellArray_destroy(struct CellArray *area)
{
	for (size_t i = 0; i < area->rows; i++)
	{
		for (size_t h = 0; h < area->columns; h++)
			if (area->arr[i][h] != NULL)
				Cell_destroy(&area->arr[i][h]);
		free(area->arr[i]);
	}
	free(area->arr);
	free(area);
}

void CellArray_print(struct CellArray *area, unsigned long long generation)
{
	const char DEAD = ' ', ALIVE = 254;

	system("cls");
	for (size_t i = 0; i < area->columns; i++)
		printf("%c", '-');
	printf("\n");

	for (size_t i = 0; i < area->rows; i++)
	{
		for (size_t h = 0; h < area->columns; h++)
			printf("%c", (area->arr[i][h] != NULL) ? ALIVE : DEAD);
		printf("\n");
	}

	for (size_t i = 0; i < area->columns; i++)
		printf("%c", '-');
	printf("\nGENERATION: %-25lluPOPULATION: %u\n", generation, area->population);
}