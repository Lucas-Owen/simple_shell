#include "main.h"
/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * @buffer: The input
 * @tokens: Where to store the tokens
 */
void tokenize_input(char *buffer, char **tokens)
{
	char *token;
	int i = 0;

	if (buffer == NULL)
		return;
	token = strtok(buffer, " \n");

	while (token != NULL && i < MAX_TOKENS)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, " \n");
		i++;
	}

	tokens[i] = NULL;
}

/**
 * evaluate_input - Evaluates input and calls appropriate functions
 * @argv: Like argv in main
 * @tokens: Tokenized input string from terminal
 * @istty: Whether input is from terminal or not, 1 or 0 resp
 * @env: The environment variables
 */
void evaluate_input(char **tokens, char **argv, char **env, int istty)
{
	char *temp = NULL;
	int status, childpid = 0;

	if (tokens[0] == NULL)
		return;
	status = eval_inbuilt_command(tokens[0], argv, env);
	if (status)
		return;

	temp = eval_path(tokens[0], env);
	if (temp == NULL)
	{
		if (istty)
			dprintf(STDERR_FILENO, "%s: command not found\n",
				tokens[0]);
		else
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
				argv[0], 1, tokens[0]);
		return;
	}
	if (tokens[0] != temp)
	{
		free(tokens[0]);
		tokens[0] = temp;
	}
	if (istty)
	{
		childpid = fork();
		if (childpid == 0)
		{
			execve(tokens[0], tokens, env);
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		return;
	}
	execve(tokens[0], tokens, env);
	/* WEXITSTATUS(status); does nothing at the moment */
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
	/* TODO: Transfer handling of exit to this place*/
	if (strcmp(command, "exit") == 0)
	{
		return (1);
	}

	return (0);
}
