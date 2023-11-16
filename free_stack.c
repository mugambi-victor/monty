#include "monty.h"

/**
 * free_stack - Frees the memory allocated for a stack.
 *
 * This function iterates through the elements of a stack starting from the
 * given head and frees the memory allocated for each element.
 *
 * @stack: Pointer to the head of the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}