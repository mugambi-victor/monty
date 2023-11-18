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
* queue - transforms the stack into a queue
* @stack: double pointer to the head of the stack
* @line_number: line number in the Monty byte code file
*/
void queue(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	temp = *stack;

	while (temp->next != NULL)
		temp = temp->next;

	temp->prev->next = NULL;
	temp->prev = NULL;
	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = temp;
}
