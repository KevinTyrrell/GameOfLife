
#include "God.h"

/*
Ascends all eligilbe cells through to the next generation.
Every cell must abide by the four rules below:

Any live cell with fewer than two live neighbours dies, as if caused by under-population. < 2
Any live cell with two or three live neighbours lives on to the next generation. >= 2 && <= 3
Any live cell with more than three live neighbours dies, as if by over-population. > 3
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void nextGeneration()
{
	// Create a new CellArray for cells to be placed onto.
	struct CellArray *future = CellArray_new(area->rows, area->columns);
	// LinkedList for new living residents.
	struct LinkedList *list = LinkedList_new();

	struct ll_Node *iter = livingCells->root;
	while (iter != NULL)
	{
		struct Cell *index = ((struct Cell*) iter->data);

		// Determine if this Cell will survive to the next generation or not.
		char neighbors = CellArray_countN(area, index->x, index->y, 4);
		if (neighbors == 2 || neighbors == 3)
		{
			struct Cell *born = Cell_new(index->x, index->y);
			future->arr[index->y][index->x] = born;
			ll_add(list, born);
		}
		
		/*
		Look at the dead neighbors around this cell.
		For each one of them, determine if there is the neccesary 
		conditions for them to be born into the next generation.
		*/
		for (unsigned int i = (index->x == 0) ? 0 : index->x - 1; i < area->columns && i <= index->x + 1; i++)
			for (unsigned int h = (index->y == 0) ? 0 : index->y - 1; h < area->rows && h <= index->y + 1; h++)
			{
				// Ignore the cell that we are currently over.
				if (i == index->x && h == index->y)
					continue;
				// Located a dead Cell neighbor.
				if (area->arr[h][i] == NULL)
				{
					neighbors = CellArray_countN(area, i, h, 3);
					// Check if this cell can be birthed.
					if (neighbors == 3)
					{
						struct Cell *born = Cell_new(i, h);
						future->arr[h][i] = born;
						ll_add(list, born);
					}
					
					// Set this dead Cell to alive in the CURRENT generation.
					// This way, it tells our program that we have already checked it.
					struct Cell *checked = Cell_new(i, h);
					checked->flag = true;
					area->arr[h][i] = checked;
				}
			}

		iter = iter->next;
	}

	// Increment the generation counter and set the new population total.
	generation++;
	future->population = (unsigned int)list->_size;

	// In threads, handle the cleanup of memory in old generations.
	HANDLE listCleaner = CreateThread(NULL, 0, ll_destroy, livingCells, 0, NULL);
	HANDLE cellCleaner = CreateThread(NULL, 0, CellArray_destroy, area, 0, NULL);

	// Set the future generation as the current one.
	area = future;
	livingCells = list;
}

/* 
Populates the grid with cells based on the config file. 
*/
void populate()
{
	// If config provides 0, make the seed random.
	time_t seed = SEED == 0 ? time(NULL) : SEED;

	// Initialize the land for the cells to live on.
	area = CellArray_new(ROWS, COLUMNS);
	livingCells = LinkedList_new();

	// Get a random seed based on the clock.
	// Rand a few times to cycle out bad outputs.
	srand((unsigned int)seed);
	rand();
	rand();

	if (INIT_POPULATION > ROWS * COLUMNS)
		endProgram(1, "Error: Your population cannot fit within the amount of rows & columns provided.");		

	time_t now = time(NULL);
	// Attempt to place the entire population in the 2D array.
	while (area->population < (unsigned int)INIT_POPULATION)
	{
		// Timeout if it takes too long.
		if ((long)time(NULL) - (long)now > 10)
		{
			fprintf(stderr, "%s\n",
				"Error: Timed out while populating the area of cells. Aborting.");
			system("pause");
			break;
		}

		// Randomly place this Node in the 2D array.
		int x = rand() % COLUMNS;
		int y = rand() % ROWS;

		if (area->arr[y][x] == NULL)
		{
			struct Cell *born = Cell_new(x, y);
			area->arr[y][x] = born;
			area->population++;
			ll_add(livingCells, born);
		}
	}
}