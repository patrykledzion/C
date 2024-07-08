#include "String.h"

#define LOWERCASE_MIN (int)'a'
#define LOWERCASE_MAX (int)'z'
#define UPPERCASE_MIN (int)'A'
#define UPPERCASE_MAX (int)'Z'

void String_copy(char* dest, char* src, int size)
{
	if (dest == NULL || src == NULL || size <= 0)return;

	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
		if (src[i] == '\x0')break;
	}
}

int String_strlen(char* string)
{
	if (string == NULL)return 0;
	int i = 0;
	while (string[i+++1] != '\x0');
	return i;
}

int String_compare(char* str1, char* str2)
{
	int len1 = String_strlen(str1);
	if (len1 != String_strlen(str2))return 0;
	for (int i = 0; i < len1; i++)
	{
		if (str1[i] != str2[i])return 0;
	}
	return 1;
}

void String_toUpper(char* str)
{
	if (str == NULL)return;
	int diff = LOWERCASE_MIN - UPPERCASE_MIN;
	int i = 0;
	while (str[i] != '\x0')
	{
		if ((int)str[i] >= LOWERCASE_MIN && (int)str[i] <= LOWERCASE_MAX)str[i] -= diff;
		i++;
	}
}

void String_toLower(char* str)
{
	if (str == NULL)return;
	int diff = LOWERCASE_MIN - UPPERCASE_MIN;
	int i = 0;
	while (str[i] != '\x0')
	{
		if ((int)str[i] >= UPPERCASE_MIN && (int)str[i] <= UPPERCASE_MAX)str[i] += diff;
		i++;
	}
}

int String_stringToInt(char* str)
{
	if (str == NULL)return 0;
	
	int res = 0;
	int sign = 0;

	int i = 0;
	if (str[0] == '-')
	{
		sign = 1;
		i = 1;
	}

	int strlen = String_strlen(str);

	while (str[i] != '\x0' && ((int)str[i] >= (int)'0' && (int)str[i] <= (int)'9'))
	{
		res += ((int)str[i] - (int)'0') * pow(10, (strlen - sign) - (i - sign + 1));
		i++;
	}

	res /= pow(10, (strlen - sign) - (i - sign));

	if (sign)res *= -1;

	return res;
	
}

char* String_IntToString(int num)
{
	int sign = 0;
	int len = 0;
	char* res = NULL;
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	int cpy = num;

	while (cpy > 0)
	{
		cpy /= 10;
		len++;
	}

	if (len == 0)
	{
		res = malloc(2);
		if (res == NULL)return NULL;
		res[0] = '0';
		res[1] = '\x0';
	}else{
		res = malloc(len + sign + 1);
		if (res == NULL)return NULL;
		int i = 0;
		while (num > 0)
		{
			res[len + sign - i  - 1] = (num % 10)+'0';
			num /= 10;
			i++;
		}
		if(sign)res[0] = '-';
		res[len + sign] = '\x0';

	}
	if (res == NULL)return NULL;
	return res;
}
