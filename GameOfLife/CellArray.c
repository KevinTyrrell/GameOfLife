
#include "CellArray.h"

/* Used for the printing the CellArray. */
static const char DEAD = ' ', ALIVE = 254, WALL = '|', FLOOR = '-',
MAX_COLUMNS = 77, MAX_ROWS = 20;

/* Constructor function. */
struct CellArray *CellArray_new(size_t rows, size_t columns)
{
	struct Cell ***arr = malloc(rows * sizeof(struct Cell**));
	if (arr == NULL)
		ds_Error(DS_MSG_OUT_OF_MEM);
	
	for (size_t i = 0; i < rows; i++)
	{
		arr[i] = calloc(columns, sizeof(struct Cell*));
		if (arr[i] == NULL)
			ds_Error(DS_MSG_OUT_OF_MEM);
	}

	struct CellArray *area = malloc(sizeof(struct CellArray));
	if (area == NULL)
		ds_Error(DS_MSG_OUT_OF_MEM);
	area->arr = arr;
	area->rows = rows;
	area->columns = columns;
	area->population = 0;
	return area;
}

/* 
Counts the number of live cells around a given index. 

Count how many non-NULL Cells surround this index, inclduing diagonals.
Keep searching around this index until `stop` number of Cells are counted.
We end at `stop` number of cells so we do not do unneccesary searching.
*/
int CellArray_countNeighbors(struct CellArray *area, unsigned int x, unsigned int y, int stop)
{
	int count = 0;

	// Loop through a 3x3 grid over this cell, searching every neighbor.
	for (unsigned int i = (x == 0) ? 0 : x - 1; i < area->columns && i <= x + 1; i++)
		for (unsigned int h = (y == 0) ? 0 : y - 1; h < area->rows && h <= y + 1; h++)
		{
			/*
			If we're not over the source cell,
			and if the cell we're looking at is alive,
			AND if we've never been to this exact cell before
			increase the counter and check if it's redundant to keep counting further.
			*/
			if ((i != x || h != y) && area->arr[h][i] != NULL && 
				area->arr[h][i]->flag == false && ++count >= stop)
				return count;
		}

	return count;
}

/* Deconstructor function. */
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

/* 
Prints out the CellArray to the console window.

If the dimensions of the CellArray are too large,
then only the statistics will print and not the cells.
*/
void CellArray_print(struct CellArray *area)
{
	system("cls");
	// 77 x 20 is the max resolution that we can print nicely.
	if (area->columns <= MAX_COLUMNS && area->rows <= MAX_ROWS)
	{
		for (size_t i = 0; i < area->columns + 2; i++)
			printf_s("%c", FLOOR);
		printf_s("\n");

		for (size_t i = 0; i < area->rows; i++)
		{
			printf_s("%c", WALL);
			for (size_t h = 0; h < area->columns; h++)
				printf_s("%c", (area->arr[i][h] != NULL) ? ALIVE : DEAD);
			printf_s("%c\n", WALL);
		}

		for (size_t i = 0; i < area->columns + 2; i++)
			printf_s("%c", FLOOR);
	}
	else
		printf_s("\n%s", "Grid dimensions are too large. Cannot output to console window.");
	
	printf_s("\nGENERATION: %-25lluPOPULATION: %zu\n", generation, area->population);
}