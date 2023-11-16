#include "monty.h"
#include <unistd.h>

/**
 * printeger - Prints an integer to the standard output.
 *
 * This function converts the given integer to a string and prints it to the
 * standard output using the write system call.
 *
 * @number: Integer to be printed.
 */

void printeger(int number)
{
	char buffer[20];

	int len = snprintf(buffer, sizeof(buffer), "%d", number);

	write(STDOUT_FILENO, buffer, len);
}

/**
 * is_numeric - Checks if a string represents a numeric value.
 *
 * This function checks whether the given string is a valid numeric value.
 * It considers an optional sign (+ or -) at the beginning.
 *
 * @str: String to be checked.
 *
 * Return: 1 if the string is numeric, 0 otherwise.
 */
int is_numeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;

	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
