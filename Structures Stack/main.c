#include <stdio.h>

#include "Stack.h"
#include "SampleStruct.h"

int main()
{
	Stack* stack = Stack_create();
	SampleStruct* st1 = SampleStruct_create(49,58);
	SampleStruct* st2 = SampleStruct_create(25,17);

	Stack_push(stack, st1);
	Stack_push(stack, st2);

	SampleStruct* st2_ret = Stack_pop(stack);
	SampleStruct* st1_ret = Stack_pop(stack);
	int x = 00;
	


	return 0;
}