#include "monty.h"
/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return:
 *   EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main(int argc, char *argv[])
{
    instruction_t opcodes[] = {
	{"push", push},
	{"pall", pall},
	 {"pint", pint},
	 {"pop", pop},
	 {"swap", swap},
	 {"add", add},
	 {"nop", nop},
     {"sub", sub},
     {"div", div_op},
     {"mul", mul_operation},
     {"mod", modulo_op},
     {"pchar", pchar},
     {"pstr", pstr},
     {"rotl", rotl},
     {"rotr", rotr},
     {"stack", stack},
     {"queue", queue},
	{NULL, NULL}
};
	FILE *file;
	stack_t *stack = NULL;
	char *input_str = NULL;

	size_t len = 0;
	ssize_t read;
	int line_number = 0;
int mode_set = 0;

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


while ((read = getline(&input_str, &len, file)) != -1) {
    int token_count;

    line_number++;

    if (input_str[read - 1] == '\n')
        input_str[read - 1] = '\0';

    if (input_str[0] == '#' || input_str[0] == '\0')
        continue;

    token_count = tokenize(input_str, " \t\n", stack_token, MAX_TOKENS);

    if (token_count > 0) {
        int i;
        char *opcode;
        opcode = stack_token[0];

        if (!mode_set) {
            if (strcmp(opcode, "queue") == 0 || strcmp(opcode, "stack") == 0) {
                set_mode(opcode);
                mode_set = 1;
            }
        }

        for (i = 0; opcodes[i].opcode != NULL; i++) {
            if (strcmp(opcode, opcodes[i].opcode) == 0) {
                opcodes[i].f(&stack, line_number);
                break;
            }
        }

        if (opcodes[i].opcode == NULL) {
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