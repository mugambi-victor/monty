#include "monty.h"
#include <unistd.h>

char *stack_token[MAX_TOKENS];


/**
* tokenize - Tokenizes a string based on a delimiter.
* @input_str: String to be tokenized.
* @delimiter: Delimiter used for tokenization.
* @stack_tokens: Array to store the resulting tokens.
* @max_tokens: Maximum number of tokens to store.
* @return The number of tokens generated.
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

	if (token_count >= 1 && strcmp(stack_tokens[0], "queue") == 0 && token_count >= 2)
	{
		return (0);
	}

	return (token_count);
}
