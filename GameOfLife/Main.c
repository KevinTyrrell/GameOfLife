
#include "God.h"

int main()
{
	/* Color the output window green. */
	system("color 0A");
	
	/* Load the config file. */
	loadConfig();

	/* Intialize the grid with cells, dictated by the config file. */
	populate();

	/* 
	Primary loop of the program. 
	
	Erase the screen, print the grid.
	Ascend to the next generation of cells.
	Wait a delay specified by the config file.
	*/
	while (generation < ULLONG_MAX)
	{
		CellArray_print(area);
		nextGeneration();
		Sleep(GENERATION_DELAY_MS);
	}

	/* Cleanup. */
	CellArray_destroy(area);
	ll_destroy(livingCells);

	return 0;
}