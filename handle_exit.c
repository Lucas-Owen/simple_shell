#include "main.h"

/**
 * free_tokens - Frees dynamically allocated memory for tokens
 * and points the memory to NULL
 * @tokens: The pointer to tokens
 * Return: void
 */
void free_tokens(char **tokens)
{
	int i = 0;

	for (; i < MAX_TOKENS && tokens[i] != NULL; i++)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
}

/**
 * eval_exit - checks if an exit command was issued
 * exits the shell after freeing dynamically allocated memory
 * @argv: Like argv in main
 * @tokens: Pointer to strings storing sequence of commands
 * @line: Line number of command
 * @status: status of previous command
 * Return: void
 */
void eval_exit(char **argv, char **tokens, int line, int *status)
{
	char *endptr = NULL;
	int e_stat;

	if (tokens[1] != NULL)
	{
		e_stat = strtol(tokens[1], &endptr, 10);
		if (endptr && *endptr)
		{
			dprintf(STDERR_FILENO,
				"%s: %d: %s: Illegal number: %s\n",
				argv[0], 1, tokens[0], endptr);
			*status = (2 << 8);
			return;
		}
		if (e_stat < 0)
		{
			dprintf(STDERR_FILENO,
				"%s: %d: %s: Illegal number: %d\n",
				argv[0], line, tokens[0], e_stat);
			*status = (2 << 8);
			return;
		}
		*status = ((e_stat & 0xff) << 8);
	}
	free_tokens(tokens);
	exit(WEXITSTATUS(*status));
}
