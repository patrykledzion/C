#pragma once
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable : 4996)

FILE* file_open(char* filename, int *err_code);		//opens file
char** file_readLines(FILE* file, int* err_code);	//read file and saves lines into 2D array (line by line)
