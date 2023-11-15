#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

char *stack_token[MAX_TOKENS];

void tokenize(const char *instruction)
{
	char *token;

	int i = 0;

	char *instruction_copy = strdup(instruction);

	if (!instruction_copy)
	{
		fprintf(stderr, "Error: strdup failed\n");
		exit(EXIT_FAILURE);
	}

	size_t length = strlen(instruction_copy);

	if (instruction_copy[length - 1] == '\n')
	{
		instruction_copy[length - 1] = '\0';
	}

	for (int j = 0; j < MAX_TOKENS; j++)

	{
		stack_token[j] = NULL;
	}

	token = strtok(instruction_copy, " ");
	while (token != NULL && i < MAX_TOKENS)
	{
		stack_token[i++] = strdup(token);

		token = strtok(NULL, " ");
	}

	free(instruction_copy);
}
