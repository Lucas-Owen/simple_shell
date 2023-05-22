#include "main.h"
#define MAX_TOKENS 100
/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * @buffer: The input
 * @tokens: Where to store the tokens
 */
void tokenize_input(char *buffer, char **tokens)
{
	char *token;
	int i = 0;

	token = strtok(buffer, " \n");

	while (token != NULL && i < MAX_TOKENS)
	{
		tokens[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}

	tokens[i] = NULL;
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
	if (eval_inbuilt_command(tokens[0], argv, env))
		return;

	tokens[0] = eval_path(tokens[0], env);
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
int eval_inbuilt_command(char *command, char **argv, char **envp)
{
	(void) argv;
	if (command == NULL)
		return (0);
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
