#pragma once

#include <stdio.h>
#include <stdlib.h>

struct stack_t {
	void*** elements;
	int size;
	int current;
}; typedef struct stack_t Stack;

Stack* Stack_create();
int Stack_push(Stack* stack, void** element);
void** Stack_pop(Stack* stack);