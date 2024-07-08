#include "array.h"


void Array_sort(double* array, int size)
{
	if (array == NULL)return;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (array[i] < array[j])
			{
				double temp = array[i];
				array[i] = array[j];
				array[j] = temp;

			}
			
		}
	}
}

void Array_print(double* array, int size)
{
	if (array == NULL)return;
	for (int i = 0; i < size; i++)
	{
		printf("%lf\n", array[i]);
	}
}
