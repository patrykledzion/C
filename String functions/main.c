#include <stdio.h>
#include "String.h"

#define STRING_SIZE 12

int main()
{
	char* src = "test string";
	char dest[STRING_SIZE];

	String_copy(dest, src, STRING_SIZE);
	printf("Destination string: %s\n", dest);

	int len = String_strlen(dest);
	printf("Len: %d\n", len);

	int cmp1 = String_compare(src, dest);
	int cmp2 = String_compare(src, "test strind");
	printf("Compare: %d %d\n", cmp1, cmp2);

	String_copy(dest, "Tes7 5tr1N_", STRING_SIZE);
	String_toUpper(dest);
	printf("Upper: %s\n", dest);
	String_toLower(dest);
	printf("Lower: %s\n", dest);

	int atoi1 = String_stringToInt("-49");
	int atoi2 = String_stringToInt("37");
	int atoi3 = String_stringToInt("21a5");
	printf("atoi: %d %d %d\n", atoi1, atoi2, atoi3);
	char* itoa = String_IntToString(-48987);
	if (itoa != NULL)
	{
		printf("itoa: %s\n", itoa);
		free(itoa);
		itoa = NULL;
	}


	/*
	OUTPUT:
		Destination string: test string
		Len: 11
		Compare: 1 0
		Upper: TES7 5TR1N_
		Lower: tes7 5tr1n_
		atoi: -49 37 21
		itoa: -48987
	*/
	return 0;
}