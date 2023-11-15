#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/**
* push - Pushes an element onto the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void push(stack_t **stack, unsigned int line_number)
{
	if (!stack || !line_number)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (!stack_token[1] || (!isdigit(stack_token[1][0])
	&& stack_token[1][0] != '-'))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(new_node);
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(stack_token[1]);
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}


/**
* pall - Prints all the values on the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void pall(stack_t **stack, unsigned int line_number)
{
	/* Suppress unused parameter warning */
	(void)line_number;

	/* Print all elements on the stack */
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/* Other opcode implementations go here */

