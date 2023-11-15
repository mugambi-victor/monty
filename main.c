#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
#include <stddef.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <monty_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    stack_t *stack = NULL;  // Initialize an empty stack

    unsigned int line_number = 0;
 while ((read = getline(&line, &len, file)) != -1)
    {
        
        line_number++; 
        tokenize(line);
        interpret_opcode(&stack, line_number);

        // Clean up memory allocated for tokens
        for (int i = 0; i < MAX_TOKENS; i++)
        {
            free(stack_token[i]);
            stack_token[i] = NULL;
        }
    }
    stack_t *current = stack;
    while (current)
    {
        printf("%d", current->n);
        current = current->next;
        if (current != NULL) {
            printf("\n");  // Add a newline if there's another element in the stack
        }
    }
    printf("\n");

    // Clean up memory allocated for the line
    free(line);
    fclose(file);

    // Clean up any remaining elements in the stack
    while (stack != NULL)
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }


    return EXIT_SUCCESS;
}

void interpret_opcode(stack_t **stack, unsigned int line_number)
{
    if (stack_token[0] == NULL)
    {
        // No opcode present, ignore the line
        return;
    }

    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        // Add other opcodes and corresponding functions here
        {NULL, NULL} // Null terminator for the array
    };

    int i = 0;
    while (instructions[i].opcode != NULL)
    {
        if (strcmp(stack_token[0], instructions[i].opcode) == 0)
        {
            // Found a matching opcode, call the corresponding function
            instructions[i].f(stack, line_number);
            return;
        }
        i++;
    }

    // If the opcode is not found, print an error message
    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, stack_token[0]);
    exit(EXIT_FAILURE);
}
