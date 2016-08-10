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

/* INI file used for program setup. */
const char *CONFIG_FILE_NAME = "..\\config.ini";
/* Expected config file lines. */
const char *CONFIG_LINE_1 = "population=", *CONFIG_LINE_2 = "rows=",
*CONFIG_LINE_3 = "columns=", *CONFIG_LINE_4 = "seed=", *CONFIG_LINE_5 = "print_ms=";

/* Attempts to load the config file as values. */
void loadConfig(FILE *f);
/* Helper function. */
void helper_assignVar(FILE *f, char *compare, int *assign);
/* Helper function. */
int helper_parseLine(FILE *f, char *compare);
/* Check that a given file exists in the file system. */
bool fileExists(const char *filename);
/* Exits the program and provides the user with a message. */
void endProgram(int code, char *message);
/* Listens for a specific hotkey and exits the program when that key is pressed. */
void listenForExit();