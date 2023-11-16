#include "monty.h"

/**
* rotr - Rotates the stack to the bottom.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty byte code file.
*/
void rotr(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		stack_t *temp = *stack;

		while (temp->next != NULL)
			temp = temp->next;

		temp->next = *stack;
		(*stack)->prev = temp;
		*stack = temp;
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
}
