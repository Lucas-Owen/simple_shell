#include "main.h"

/**
 * evaluate_input - Evaluates input and calls appropriate functions
 * @argv: Like argv in main
 * @tokens: Tokenized input string from terminal
 * @env: The environment variables
 * @istty: Whether input is from terminal or not, 1 or 0 resp
 * @line: line number
 * @status: Status of previously exec'd task
 */
void evaluate_input(char **tokens, char **argv, char **env,
	int istty, int line, int *status)
{
	char *temp = NULL;
	int childpid = 0;

	if (tokens[0] == NULL)
		return;
	if (eval_inbuilt_command(tokens, argv, env, line, status))
		return;

	temp = eval_path(tokens[0], env);
	if (temp == NULL)
	{
		if (istty)
			dprintf(STDERR_FILENO, "%s: command not found\n",
				tokens[0]);
		else
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
				argv[0], line, tokens[0]);
		*status = 127;
		return;
	}
	if (tokens[0] != temp)
	{
		free(tokens[0]);
		tokens[0] = temp;
	}
	childpid = fork();
	if (childpid == 0)
	{
		execve(tokens[0], tokens, env);
		perror(argv[0]);
		_exit(EXIT_FAILURE);
	}
	else
		wait(status);
	free_tokens(tokens);
	/* WEXITSTATUS(status); does nothing at the moment */
}

/**
 * eval_inbuilt_command - Checks if a command is an inbuilt command
 * and evaluate it
 * @tokens: The tokens with command and args
 * @argv: Like argv in main
 * @envp: Currentn execution envirionment
 * @line: line number
 * @status: Status of previously exec'd task
 * Return: 1 if true, (0) otherwise
 */
int eval_inbuilt_command(char **tokens, char **argv, char **envp,
	int line, int *status)
{
	(void) argv;
	if (tokens[0] == NULL)
		return (0);
	if (strcmp(tokens[0], "env") == 0)
	{
		if (fork() == 0)
		{
			print_env(envp);
			_exit(EXIT_SUCCESS);
		}
		wait(status);
		return (1);
	}
	/* TODO: Transfer handling of exit to this place*/
	if (strcmp(tokens[0], "exit") == 0)
	{
		eval_exit(argv, tokens, line, status);
		return (1);
	}

	return (0);
}
