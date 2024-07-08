#pragma once

#include <stdlib.h>

struct sample_struct_t {
	int x;
	void* y;
}; typedef struct sample_struct_t SampleStruct;

SampleStruct* SampleStruct_create(int x, int y);

