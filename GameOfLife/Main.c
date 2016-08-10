
#include "God.h"

int main()
{
	/* Attempt to read the user's config file. */
	FILE *f;
	errno_t err = fopen_s(&f, CONFIG_FILE_NAME, "r+");
	if (!err)
		loadConfig(f);
	else
		endProgram(1, "Error: Your INI file could not be found.");
	fclose(f);

	/* Intialize the grid with cells, dictated by the config file. */
	populate();
	
	/* Allow the user to exit the program at any time by pressing a certain key. */
	HANDLE exit = CreateThread(NULL, 0, listenForExit, NULL, 0, NULL);

	/* 
	Primary loop of the program. 
	
	Erase the screen, print the grid.
	Ascend to the next generation of cells.
	Wait a delay specified by the config file.
	*/
	while (generation < ULLONG_MAX)
	{
		CellArray_print(area, generation);
		nextGeneration();
		Sleep(GENERATION_DELAY_MS);
	}

	CellArray_destroy(area);
	ll_destroy(livingCells);

	return 0;
}