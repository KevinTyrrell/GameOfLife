
#pragma once

#include "LinkedList.h"
#include "CellArray.h"
#include "Tools.h"
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
// What generation we are currently in.
unsigned long long generation;

/* Ascends all eligilbe cells through to the next generation. */
void nextGeneration();
/* Populates the land with cells based on the config file. */
void populate();

/* Variables which dictate the structure for the simulation. */
unsigned int GENERATION_DELAY_MS, INIT_POPULATION, ROWS, COLUMNS, SEED;
