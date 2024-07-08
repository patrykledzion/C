#include "Stack.h"

Stack* Stack_create()
{
	Stack* stack = malloc(sizeof(Stack));
	if (stack == NULL)return NULL;
	stack->size = 8;
	stack->current = 0;
	stack->elements = malloc(sizeof(void**) * stack->size);
	if (stack->elements == NULL)
	{
		free(stack);
		return NULL;
	}
	return stack;
}

int Stack_push(Stack* stack, void** element)
{
	if (stack == NULL || stack->elements == NULL || element == NULL)return -1;
	
	if (stack->current + 1 > stack->size)
	{
		stack->size += 8;
		void*** elements = realloc(stack->elements, sizeof(void**) * stack->size);
		if (elements == NULL)return -2;
		stack->elements = elements;
	}

	stack->elements[stack->current++] = element;
}

void** Stack_pop(Stack* stack)
{
	if (stack == NULL || stack->elements == NULL && stack->current > 0)return NULL;
	return stack->elements[--stack->current];
}
