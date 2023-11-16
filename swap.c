#include "monty.h"

/**
* swap - swaps the top two elements of the stack
* @stack: double pointer to the head of the stack
* @line_number: line number in the Monty byte code file
*/
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;

	if (temp->next != NULL)
		temp->next->prev = *stack;

	(*stack)->next = temp->next;
	temp->prev = NULL;
	temp->next = *stack;
	(*stack)->prev = temp;

	*stack = temp;
}
