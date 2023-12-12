#include "Files.h"
#include "Utils.h"
 
FILE* file_open(char* filename, int* err_code)
{
	if (err_code)*err_code = 0;
	if (filename == NULL)
	{
		if (err_code)*err_code = -1;
		return NULL;
	}

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		if (err_code)*err_code = -2;
		return NULL;
	}

	return file;
}

char** file_readLines(FILE* file, int* linesCount)
{
	//treat linesCount as error code
	if (linesCount)*linesCount = 0;
	if (file == NULL)
	{
		if (linesCount)*linesCount = -1;
		return NULL;
	}

	char** lines = (char **)malloc(sizeof(char*));		//alloc memory for first line (0 chars)
	if (lines == NULL)
	{
		if (linesCount)*linesCount = -2;
		return NULL;
	}

	*lines = (char*)malloc(1);							//alloc memory for one char in first line
	if (*lines == NULL)
	{
		if (linesCount)*linesCount = -3;
		free(lines);
		return NULL;
	}

	char c = getc(file);

	int line_counter = 0;								//	Counters for lines and characters in line 
	int char_counter = 0;								//


	while (!feof(file))
	{
		if (c == '\n')									// NEW LINE IN FILE
		{
			lines[line_counter][char_counter] = '\x0';										// Set last char of the line as \x0
			line_counter++;
			char_counter = 0;												
			char** new_lines = (char**)realloc(lines, sizeof(char*) * (line_counter + 1));	//realloc lines array (add space for another line)
			if (new_lines == NULL)
			{
				if (linesCount)*linesCount = -4;
				free_2d_array((void**)lines, line_counter - 1);
				return NULL;
			}
			lines = new_lines;

			lines[line_counter] = (char*)malloc(1);											//alloc memory for first char in the line 
			if (lines[line_counter] == NULL)
			{
				if (linesCount)*linesCount = -5;
				free_2d_array((void**)lines, line_counter - 1);
				return NULL;
			}
		}
		else {
			lines[line_counter][char_counter] = c;
			char_counter++;
			lines[line_counter] = (char*)realloc(lines[line_counter], char_counter + 1); //realloc line array (add space for another char in line)
			if (lines[line_counter] == NULL)
			{
				if (linesCount)*linesCount = -6;
				free_2d_array((void**)lines, line_counter - 1);
				return NULL;
			}
			
		}
		c = getc(file);
	}

	if(linesCount)*linesCount = line_counter;
	return lines;
}
