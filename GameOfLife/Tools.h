#pragma once

#include "God.h"
#include "DataStructureTools.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "ctype.h"
#include <limits.h>

#define BUFFER_SIZE 80

/* Attempts to load the config file as values. */
void loadConfig();
/* Check that a given file exists in the file system. */
bool fileExists(const char *filename);
/* Listens for a specific hotkey and exits the program when that key is pressed. */
void listenForExit();