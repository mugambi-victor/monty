#include "monty.h"
#include <unistd.h>
/**
* pall - prints all the values on the stack
* @stack: double pointer to the head of the stack
* @line_number: line number in the Monty byte code file
*/

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void) line_number;

	current = *stack;

	while (current != NULL)
	{
		printeger(current->n);
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
}