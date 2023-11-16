#include "monty.h"

/**
* stack - Sets the format of the data to a stack (LIFO).
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty byte code file.
*/
void stack(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	(void)stack;
	/* Do nothing, already in stack mode (LIFO) */
}

/**
* queue - Sets the format of the data to a queue (FIFO).
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty byte code file.
*/
void queue(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;

	if (*stack != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;

		if (temp->prev != NULL)
			temp->prev->next = NULL;

		temp->prev = NULL;
		temp->next = *stack;
		(*stack)->prev = temp;
		*stack = temp;
	}
}
