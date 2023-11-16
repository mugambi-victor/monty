#include "monty.h"
/**
* mul_operation - Multiplies the
* second top element by the top element of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty byte code file.
*
* @param stack Double pointer to the head of the stack.
* @param line_number Line number in the Monty byte code file.
*/
void mul_operation(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n *= (*stack)->n;
	pop(stack, line_number);
}
