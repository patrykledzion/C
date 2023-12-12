#include <stdio.h>
#include "Utils.h"
#include "Files.h"

int main()
{
	int err_code = 0;
	FILE* file = file_open("test.txt", &err_code);								// OPEN FILE
	int lines_count = 0;
	char** lines = file_readLines(file, &lines_count);							//READ FROM FILE TO 2D ARRAY
	if (err_code != 0)
	{
		return err_code;
	}
	char*** words = get_words_from_line(lines, lines_count, &err_code);			//DIVIDE LINES INTO SINGLE WORDS
	if (err_code != 0)
	{
		free_2d_array(lines, lines_count);
		return err_code;
	}

	words = change_words_in_3D_array(words, "symphony", "music", lines_count);	//CHANGE WORDS "symphony" TO "music"
	if (words == NULL)	
	{
		printf("WORDS NULL");
		return -1;
	}
	printf("Lines count: %d\n", lines_count);
 
	print_3D_array(words, lines_count);											//WRITE ALL LINES
	 

	//CLEANING MEMORY
	free_2d_array(lines, lines_count);
	for (int i = 0; i < lines_count; i++)
	{
		free_2d_array(words[i], -1);
	}
	free(words);
	fclose(file);
	//////////////////
	return err_code;
}