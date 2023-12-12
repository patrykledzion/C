#pragma once
#pragma warning(disable : 4996)

#include <string.h>
#include <stdio.h>


void free_2d_array(void** arr, int size);		//free 2D array
char*** get_words_from_line(char** lines, int lines_count, int* err_code);
char** change_word_in_array(char** arr, char* word, int pos);
int find_word_in_array(char** arr, char* word);
char*** change_words_in_3D_array(char*** arr, char* word, char* new_word, int lines_count);
int count_words_in_array(char** arr);
char** copy_words_array(char** arr);
void print_3D_array(char*** arr, int lines_count);