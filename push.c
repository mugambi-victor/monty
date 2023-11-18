#include "monty.h"

int queue_mode = 0; 


void set_mode(char *first_token)
{
    queue_mode = (strcmp(first_token, "queue") == 0);
}

void push(stack_t **stack, unsigned int line_number)
{
    stack_t *new_node;
    int value;


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
    new_node->next = NULL;

    if (*stack == NULL)
    {
        *stack = new_node;
    }
    else
    {
        if (queue_mode) {
            stack_t *temp = *stack;


            while (temp->next != NULL)
                temp = temp->next;

            temp->next = new_node;
            new_node->prev = temp;
        } else {
            new_node->next = *stack;
            (*stack)->prev = new_node;
            *stack = new_node;
        }
    }
}


void pop(stack_t **stack, unsigned int line_number)
{
   stack_t *temp;
    (void)line_number;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pop an empty data structure\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = *stack;

    if (queue_mode) {
        *stack = (*stack)->next;
        if (*stack != NULL)
            (*stack)->prev = NULL;
    } else {
        *stack = (*stack)->next;
        if (*stack != NULL)
            (*stack)->prev = NULL;
    }

    free(temp);
}
