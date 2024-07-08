#pragma once
#include <stdlib.h>
#include <math.h>

void String_copy(char* dest, char* src, int size);	//copy `size` number of characters from src to dest
int String_strlen(char* string);					//returns len of given string
int String_compare(char* str1, char* str2);			//returns 1 if given strings are the same, otherwise 0
void String_toUpper(char* str);						//changes lowercase letters of given string to uppercase
void String_toLower(char* str);						//changes upercase letters of given string to lowercase
int String_stringToInt(char* str);					//returns int value of given string (until non-digit sign)
char* String_IntToString(int num);					//returns string value (pointer to allocated memory) of given int number


