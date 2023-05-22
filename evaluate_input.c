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

/**
 * eval_inbuilt_command - Checks if a command is an inbuilt command
 * and evaluate it
 * @command: The command
 * @argv: Arguments to command, starting with the command
 * @envp: Currentn execution envirionment
 * Return: 1 if true, (0) otherwise
 */
int eval_inbuilt_command(char *command, char** argv, char **envp)
{
	if (strcmp(command, "env") == 0)
	{
		print_env(envp);
		return (1);
	}
	if (strcmp(command, "exit") == 0)
	{
		_exit(0);
	}
	return (0);
}
