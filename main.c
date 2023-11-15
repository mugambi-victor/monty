#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
#include <stddef.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char *line;
    size_t len;
     ssize_t read;
     stack_t *stack;
     stack_t *current;
     unsigned int line_number;
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    line = NULL;
    len = 0;

    stack = NULL;

    line_number = 0;
 while ((read = getline(&line, &len, file)) != -1)
    {
        int i;
        line_number++; 
        tokenize(line);
        interpret_opcode(&stack, line_number);

        for (i = 0; i < MAX_TOKENS; i++)
        {
            free(stack_token[i]);
            stack_token[i] = NULL;
        }
    }
    current = stack;
    while (current)
    {
       
        current = current->next;
        if (current != NULL) {
           
        }
    }
    free(line);
    fclose(file);

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
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };
    int i ;
    if (stack_token[0] == NULL)
    {
        return;
    }

    

    i = 0;
    while (instructions[i].opcode != NULL)
    {
        if (strcmp(stack_token[0], instructions[i].opcode) == 0)
        {
            instructions[i].f(stack, line_number);
            return;
        }
        i++;
    }

    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, stack_token[0]);
    exit(EXIT_FAILURE);
}
