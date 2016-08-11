#pragma once

#include "God.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "ctype.h"

#define BUFFER_SIZE 80
#define LINE_BUFFER_SIZE 1024
#define CONFIG_LINES 5
#define CONFIG_ERROR_MESSAGE "Error: Your config.ini file is malformed."

/* Attempts to load the config file as values. */
void loadConfig();
/* Check that a given file exists in the file system. */
bool fileExists(const char *filename);
/* Exits the program and provides the user with a message. */
void endProgram(const int code, const char *message);
/* Listens for a specific hotkey and exits the program when that key is pressed. */
void listenForExit();