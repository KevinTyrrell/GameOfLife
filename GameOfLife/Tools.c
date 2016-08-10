
#include "Tools.h"

/* Attempts to load the config file as values. */
void loadConfig(FILE *f) 
{
	helper_assignVar(f, CONFIG_LINE_1, &INIT_POPULATION);
	helper_assignVar(f, CONFIG_LINE_2, &ROWS);
	helper_assignVar(f, CONFIG_LINE_3, &COLUMNS);
	helper_assignVar(f, CONFIG_LINE_4, &SEED);
	helper_assignVar(f, CONFIG_LINE_5, &GENERATION_DELAY_MS);
}

/* Helper function to determine if we need to end the program from bad input. */
void helper_assignVar(FILE *f, char *compare, int *assign)
{
	int input = helper_parseLine(f, compare);
	if (input == -1)
		endProgram(1, CONFIG_ERROR_MESSAGE);
	
	*assign = input;
}

/*
Helper function to parse the config file.

Check the next line of the file.
If there is nothing more to read in the file,
or if the data the user put in doesn't match what we expect,
return -1 meaning that the INI file is malformed.
*/
int helper_parseLine(FILE *f, char *compare)
{
	char buffer[LINE_BUFFER_SIZE];
	if (fscanf(f, " %1023s", buffer) == 1 && strlen(buffer) > strlen(compare))
	{
		size_t counter = 0;
		// Make sure the compare variable matches what's in our file.		
		for (; counter < strlen(compare); counter++)
			if (buffer[counter] != compare[counter])
				return -1;

		// Add the rest of the line into a buffer.
		char valueBuffer[LINE_BUFFER_SIZE];
		int buffIndex = 0;
		for (; counter < strlen(buffer); counter++, buffIndex++)
			valueBuffer[buffIndex] = buffer[counter];
		// End this buffer.
		valueBuffer[buffIndex] = '\0';

		/*
		We have now verified that the first half is correct.
		Now we must parse through whatever the user put on the
		opposite side of the equals sign.
		*/
		size_t value = 0;
		for (int i = (int)strlen(valueBuffer) - 1, h = 1; i >= 0; i--, h *= 10)
		{
			if (isdigit(valueBuffer[i]))
			{
				//char x = valueBuffer[i];
				//char y = x - '0';
				//char z = y * h;
				value += (valueBuffer[i] - '0') * h;
			}
			else
				return -1;
		}
	
		return value;
	}
	
	return -1;
}

/* Check that a given file exists in the file system. */
bool fileExists(const char *filename) 
{
	struct stat st;
	int result = stat(filename, &st);
	return result == 0;
}

/* Exits the program and provides the user with a message. */
void endProgram(int code, char *message)
{
	if (message != NULL)
		fprintf(stderr, "%s%s\n", message, " Exiting program runtime.");
	exit(code);
}

/*
Listens for a specific hotkey and exits the program when that key is pressed.

This method must be called in a thread.
*/
void listenForExit()
{
	while (true)
	{
		// Code 27 is ESC Key.
		if (_kbhit() && _getch() == 27)
			endProgram(0, "Exit keybind pressed.");
		Sleep(30);
	}
}