
#include "Tools.h"

/* INI file used for program setup. */
#define CONFIG_FILE_NAME "config.ini"

/* Expected config file lines. */
#define CONFIG_LINE1 "population="
#define CONFIG_LINE2 "rows="
#define CONFIG_LINE3 "columns="
#define CONFIG_LINE4 "seed="
#define CONFIG_LINE5 "print_ms="

#define CONFIG_LINES 5
#define LINE_BUFFER_SIZE 1024

#define CONFIG_MSG_MALFORM "Your config.ini file is malformed."
#define CONFIG_MSG_MISSING "Your config.ini file could not be found."

/* Helper function. */
static void helper_assignVar(FILE *f, const char *compare, int *assign);
/* Helper function. */
static unsigned int helper_parseLine(FILE *f, const char *compare);

/* Attempts to load the config file as values. */
void loadConfig() 
{
	/* Attempt to read the user's config file. */
	FILE *f;
	errno_t err = fopen_s(&f, CONFIG_FILE_NAME, "r+");
	if (err)
		ds_Error(CONFIG_MSG_MISSING);

	helper_assignVar(f, CONFIG_LINE1, &INIT_POPULATION);
	helper_assignVar(f, CONFIG_LINE2, &ROWS);
	helper_assignVar(f, CONFIG_LINE3, &COLUMNS);
	helper_assignVar(f, CONFIG_LINE4, &SEED);
	helper_assignVar(f, CONFIG_LINE5, &GENERATION_DELAY_MS);

	fclose(f);
}

/* Helper function to determine if we need to end the program from bad input. */
void helper_assignVar(FILE *f, const char *compare, int *assign)
{
	int input = helper_parseLine(f, compare);
	if (input == UINT_MAX)
		ds_Error(CONFIG_MSG_MALFORM);
	*assign = input;
}

/*
Helper function to parse the config file.

Check the next line of the file.
If there is nothing more to read in the file,
or if the data the user put in doesn't match what we expect,
return UINT_MAX meaning that the config file is malformed.
Otherwise, return the parsed integer value of the line.
*/
unsigned int helper_parseLine(FILE *f, const char *compare)
{
	char buffer[LINE_BUFFER_SIZE];
	// Check if file read was successful and that there is enough characters on the line.
	if (fscanf_s(f, " %1023s", buffer) == 1 && strlen(buffer) > strlen(compare))
	{
		size_t counter = 0;
		// Make sure the compare variable matches what's in our file.		
		for (; counter < strlen(compare); counter++)
			if (buffer[counter] != compare[counter])
				return UINT_MAX;

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
		unsigned int value = 0;
		for (int i = (int)strlen(valueBuffer) - 1, h = 1; i >= 0; i--, h *= 10)
			if (isdigit(valueBuffer[i]))
				value += (valueBuffer[i] - '0') * (unsigned int)h;
			else
				return UINT_MAX;
	
		return value;
	}
	
	return UINT_MAX;
}

/* Check that a given file exists in the file system. */
bool fileExists(const char *filename) 
{
	struct stat st;
	int result = stat(filename, &st);
	return result == 0;
}