#include "SampleStruct.h"

SampleStruct* SampleStruct_create(int x, int y)
{
	SampleStruct* sample = malloc(sizeof(SampleStruct));
	if (sample == NULL)return NULL;
	sample->x = x;
	sample->y = y;
	return sample;
}
