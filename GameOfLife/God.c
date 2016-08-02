
#include "CellArray.h"
#include "LinkedList.h"
#include <windows.h>
#include <time.h>
#include <conio.h>

/*
Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by over-population.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

// Area which houses the cells.
struct CellArray *area;
// Second data structure to track only the living cells.
struct LinkedList *livingCells;
// Boolean variable of whether or not the user wishes to end the program.
bool FLAG_EXIT_PROGRAM = false;

// What generation we are currently in.
unsigned long long generation = 0;

void update();
void populate();
void listenForExit();

int main()
{
	populate();
	HANDLE exitThread = CreateThread(NULL, 0, listenForExit, NULL, 0, NULL);
	Sleep(5000);
	while (!FLAG_EXIT_PROGRAM)
	{
		CellArray_print(area, generation);
		update();
		Sleep(250);
	}

	CellArray_destroy(area);
	ll_destroy(livingCells);
	return 0;
}

/*
Ascend into the next generation by following the rules below:

Any live cell with fewer than two live neighbours dies, as if caused by under-population. < 2
Any live cell with two or three live neighbours lives on to the next generation. >= 2 && <= 3
Any live cell with more than three live neighbours dies, as if by over-population. > 3
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void update()
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
	HANDLE thread1 = CreateThread(NULL, 0, ll_destroy, livingCells, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, CellArray_destroy, area, 0, NULL);

	// Set the future generation as the current one.
	area = future;
	livingCells = list;
}

// Initializes the area with randomly generated cells.
void populate()
{
	unsigned int initPopulation = 150,
		columns = 60, rows = 20;
	time_t seed = 5000; // time(NULL)

	// Initialize the land for the cells to live on.
	area = CellArray_new(rows, columns);
	livingCells = LinkedList_new();

	// Get a random seed based on the clock.
	// Rand a few times to cycle out bad outputs.
	srand((unsigned int)seed);
	rand();
	rand();

	if (initPopulation > columns * rows)
	{
		fprintf(stderr, "%s%s\n",
			"Error: Your population cannot fit within the amount of rows & columns provided.",
			" Resetting the population.");
		system("pause");
		initPopulation = (unsigned int)(columns * rows * 0.9);
	}

	time_t now = time(NULL);
	// Attempt to place the entire population in the 2D array.
	while (area->population < initPopulation)
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
		int x = rand() % columns;
		int y = rand() % rows;

		if (area->arr[y][x] == NULL)
		{
			struct Cell *born = Cell_new(x, y);
			area->arr[y][x] = born;
			area->population++;
			ll_add(livingCells, born);
		}
	}
}

// Listen a spacebar press indicating the user wants to quit.
void listenForExit()
{
	const DWORD BUFFER_TIME_MS = 30;

	while (true)
	{
		if (_kbhit() && _getch() == ' ')
		{
			FLAG_EXIT_PROGRAM = true;
			return;
		}
		Sleep(BUFFER_TIME_MS);
	}
}