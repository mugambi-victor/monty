#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stack_token[MAX_TOKENS];

char *my_strdup(const char *str)
{
	size_t len = strlen(str) + 1;
	char *new_str = malloc(len);

	if (new_str == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	strcpy(new_str, str);
	return (new_str);
}

void tokenize(const char *instruction)
{
	char *token;
int j;
	int i = 0;

	char *instruction_copy = my_strdup(instruction);

	size_t length = strlen(instruction_copy);

	if (length > 0 && instruction_copy[length - 1] == '\n')
	{
		instruction_copy[length - 1] = '\0';
	}

	for (j = 0; j < MAX_TOKENS; j++)
	{
		stack_token[j] = NULL;
	}

	token = strtok(instruction_copy, " ");
	while (token != NULL && i < MAX_TOKENS)
	{
		stack_token[i++] = my_strdup(token);

		token = strtok(NULL, " ");
	}

	free(instruction_copy);
}

