#include "main.h"

/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * @buffer: The input
 * @tokens: Where to store the tokens
 */
void tokenize_input(char *buffer, char **tokens)
{
	/* Last character is a new line, don't copy*/
	strncpy(tokens[0], buffer, strlen(buffer) - 1);
	tokens[1] = NULL;
}
/**
 * evaluate_input - Evaluates input and calls appropriate functions
 * @argv: Like argv in main
 * @tokens: Tokenized input string from terminal
 * @env: The environment variables
 */
void evaluate_input(char **tokens, char **argv, char **env)
{
	if (tokens[0] == NULL)
		return;
	if (fork() == 0)
	{
		execve(tokens[0], tokens, env);
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}
