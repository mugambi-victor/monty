#include "monty.h"
/**
* push - pushes an element to the stack
* @stack: double pointer to the head of the stack
* @line_number: line number in the Monty byte code file
*/

void push(stack_t **stack, unsigned int line_number)
{
	int value;

	stack_t *new_node;

	if (stack_token[1] == NULL || !is_numeric(stack_token[1]))
	{
		free_stack(*stack);
		 fprintf(stderr, "L%d: usage: push integer\n", line_number);
		 exit(EXIT_FAILURE);
	}

	value = atoi(stack_token[1]);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		 free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

