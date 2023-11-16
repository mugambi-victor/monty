#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#define MAX_TOKENS 100
char *stack_token[MAX_TOKENS];

instruction_t opcodes[] = {
	{"push", push},
	{"pall", pall},
	 {"pint", pint},
	{NULL, NULL}
};

void free_stack(stack_t *stack);

/**
* tokenize - tokenizes a string based on a delimiter
* @input_str: string to be tokenized
* @delimiter: delimiter used for tokenization
* @tokens: array to store the resulting tokens
* @max_tokens: maximum number of tokens to store
*
* Returns the number of tokens
*/

int tokenize(char *input_str, const char *delimiter, char *stack_tokens[], int max_tokens)
{
	char *token = strtok(input_str, delimiter);

	int token_count = 0;

	while (token != NULL && token_count < max_tokens)
	{
		stack_tokens[token_count++] = token;
		token = strtok(NULL, delimiter);
	}
	return (token_count);
}


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
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char *input_str = NULL;

	size_t len = 0;
	ssize_t read;
	int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}


	while ((read = getline(&input_str, &len, file)) != -1)
	{
		int token_count;

		line_number++;

		if (input_str[read - 1] == '\n')
			input_str[read - 1] = '\0';

		token_count = tokenize(input_str, " \t\n", stack_token, MAX_TOKENS);

		if (token_count > 0)
		{
			char *opcode = stack_token[0];

			int i;

			for (i = 0; opcodes[i].opcode != NULL; i++)
			{
				if (strcmp(opcode, opcodes[i].opcode) == 0)
				{
					opcodes[i].f(&stack, line_number);
					break;
				}
			}

			if (opcodes[i].opcode == NULL)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				free(input_str);
				fclose(file);
				free_stack(stack);
				exit(EXIT_FAILURE);
			}
		}
		if (read == EOF)
        break;
	}

	free(input_str);
	fclose(file);
	free_stack(stack);
	exit(EXIT_SUCCESS);
	
}

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
void printeger(int number)
{
	char buffer[20];
	int len = snprintf(buffer, sizeof(buffer), "%d", number);

	write(STDOUT_FILENO, buffer, len);
}

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
int is_numeric(const char *str)
{
    if (*str == '-' || *str == '+')
        str++; 

    while (*str)
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

