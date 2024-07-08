#include <stdio.h>
#include "array.h"

#define ARRAY_SIZE 10

int main()
{
	double array[ARRAY_SIZE] = { 4,1,3,7,5,9,4.78,2,0,4 };
	printf("Original: \n");
	Array_print(array, ARRAY_SIZE);

	printf("Sorted: \n");
	Array_sort(array, ARRAY_SIZE);
	Array_print(array, ARRAY_SIZE);
	return 0;
}