#include <stdlib.h>
#include "Utils.h"

void free_2d_array(void** arr, int size)
{
	if (arr != NULL && size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i] != NULL)
			{
				free(arr[i]);
			}
		}
		free(arr);
	}
	else if (size == -1)
	{
		int i = 0;
		do {
			free(arr[i]);
			i++;
		}while (arr[i] != NULL);
		free(arr);
	}
}

char*** get_words_from_line(char** lines, int lines_count, int* err_code)
{
	if (err_code)*err_code = 0;
	if (lines == NULL)
	{
		if (err_code)*err_code = -1;
		return NULL;
	}

	char*** words = (char***)malloc(sizeof(char**) * 70);				//Alloc memory for all lines (0 words)
	if (words == NULL)
	{
		if (err_code)*err_code = -2;
		return NULL;
	}

	words[0] = (char**)malloc(sizeof(char*));						//Alloc memory for first word in line (0 chars)
	if (words[0] == NULL)
	{
		if (err_code)*err_code = -3;
		return NULL;
	}

	words[0][0] = (char*)malloc(1);						//Alloc memory for first char in word
	if (words[0][0] == NULL)
	{
		if (err_code)*err_code = -4;
		return NULL;
	}

	for (int line_counter = 0; line_counter < lines_count; line_counter++)
	{
		char c = lines[line_counter][0];
		int word_counter = 0;
		int char_counter = 0;
		int line_pos = 0;
		do {
			c = lines[line_counter][line_pos++];
			if (c==' ' || c == '\x0')
			{
				
				words[line_counter][word_counter][char_counter] = '\x0';
				char_counter = 0;
				word_counter++;
							
				char ***new_words = realloc(words[line_counter], sizeof(char*) * (word_counter + 1));				//realloc for new word
				if (new_words == NULL)
				{
					if (err_code)*err_code = -6;
					for (int i = 0; i < line_counter; i++)
					{
						free_2d_array(words[i], -1);
					}
					free(words);
					return NULL;
				}
				words[line_counter] = new_words;/***/
				words[line_counter][word_counter] = malloc(1);														//alloc memory for first char in the line
				if (words[line_counter][word_counter] == NULL)
				{
					if (err_code)*err_code = -7;
					for (int i = 0; i < line_counter; i++)
					{
						free_2d_array(words[i], -1);
					}
					free(words);
					return NULL;
				}

				if (c == '\x0')
				{
					words[line_counter][word_counter] = NULL;
				}
			} else {
				words[line_counter][word_counter][char_counter] = c;
				char_counter++;
				words[line_counter][word_counter] = realloc(words[line_counter][word_counter], char_counter + 1);	//realloc for another char
				if (words[line_counter][word_counter] == NULL)
				{
					if (err_code)*err_code = -5;
					for (int i = 0; i < line_counter; i++)
					{
						free_2d_array(words[i], -1);
					}
					free(words);
					return NULL;
				}
			}
			 
		} while (c != '\x0');
		
		words[line_counter + 1] = (char**)malloc(sizeof(char*));						//Alloc memory for first word in line (0 chars)
		if (words[line_counter + 1] == NULL)
		{
			if (err_code)*err_code = -3;
			return NULL;
		}

		words[line_counter + 1][0] = (char*)malloc(1);									//Alloc memory for first char in word
		if (words[line_counter + 1][0] == NULL)
		{
			if (err_code)*err_code = -4;
			return NULL;
		}
		word_counter = 0;
		char_counter = 0;
		line_pos = 0;
		 
	}

	return words;
}

int _strlen(char* str)
{
	if (str == NULL)return -1;
	int i = 0;
	while (str[i++] != '\x0');
	return i+1;
}

int count_words_in_array(char** arr)
{
	if (arr == NULL)return -1;
	int word_counter = 0;
	while (arr[++word_counter] != NULL);
	return word_counter;
}

char** copy_words_array(char** arr)
{
	if (arr == NULL)return NULL;
	int word_counter = count_words_in_array(arr);
	char** new_arr = malloc(sizeof(char*) * (word_counter + 1));
	if (new_arr == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < word_counter; i++)
	{
		 
		new_arr[i] = malloc(strlen(arr[i]) + 1);
		if (new_arr[i] == NULL)
		{
			free_2d_array(new_arr, i - 1);
			return NULL;
		}
		strncpy(new_arr[i], arr[i], strlen(arr[i]));
		new_arr[i][strlen(arr[i])] = '\x0';
		 
	}

	new_arr[word_counter] = NULL;
	free_2d_array(arr, word_counter);

	return new_arr;

}

void print_3D_array(char*** words, int lines_count)
{
	if (words == NULL)return;

	for (int i = 0; i < lines_count; i++)
	{
		if (words[i] == NULL)
		{
			printf("NULL ERROR");
			return NULL;
		}
		int j = 0;
		while (words[i][j] != NULL)
		{
			printf("%s ", words[i][j]);
			j++;
		}
		printf("\n");
	}
}

char** change_word_in_array(char** arr, char* word, int pos)
{
	if (arr == NULL || word == NULL || pos < 0)
	{
		return NULL;
	}

	//FIND ARRAY SIZE
	int word_counter = count_words_in_array(arr);
	 
	char** new_arr = malloc(sizeof(char*) * (word_counter + 1));
	if (new_arr == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < word_counter; i++)
	{
		if (i == pos)
		{
			new_arr[i] = malloc(strlen(word) + 1);
			if (new_arr[i] == NULL)
			{
				free_2d_array(new_arr, i - 1);
				return NULL;
			}
			strncpy(new_arr[i], word, strlen(word));
			new_arr[i][strlen(word)] = '\x0';
		}
		else {
			new_arr[i] = malloc(strlen(arr[i]) + 1);
			if (new_arr[i] == NULL)
			{
				free_2d_array(new_arr, i - 1);
				return NULL;
			}
			strncpy(new_arr[i], arr[i], strlen(arr[i]));
			new_arr[i][strlen(arr[i])] = '\x0';
		}
	}

	new_arr[word_counter] = NULL;

	free_2d_array(arr, word_counter);

	return new_arr;
}

int find_word_in_array(char** arr, char* word)
{
	if (arr == NULL || word == NULL)
	{
		return -1;
	}

	int word_counter = 0;
	while (arr[word_counter] != NULL)
	{
		int cmp = strcmp(arr[word_counter], word);

		if (cmp== 0)
		{
			//printf("COMPARE: %s==%s > %d\n", arr[word_counter], word, word_counter);
			return word_counter;
		}
		word_counter++;
	}

	return -1;
}

char*** change_words_in_3D_array(char*** arr, char* word, char* new_word,  int lines_count)
{
	if (arr == NULL || word == NULL || new_word==NULL)return NULL;
	char*** new_arr = malloc(sizeof(char**) * lines_count);
	if (new_arr == NULL)
	{
		return NULL;
	}
	//printf("CHANGE WORDS IN 3D ARR: \n");
	for (int i = 0; i < lines_count; i++)
	{ 
		//printf(" - %s\n", word);
		int to_change = find_word_in_array(arr[i], word);
		if (to_change >= 0)
		{
			new_arr[i] = change_word_in_array(arr[i], new_word, to_change);
		}
		else {
			new_arr[i] = copy_words_array(arr[i]);
		}
			

		if (new_arr[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free_2d_array(new_arr[j], i - 1);
			}
			free(new_arr);
		}
	}

	 

	free(arr);

	return new_arr;

	
}

