#include "main.h"

/**
 * main - Simple unix shell
 * @argc: Length of argv
 * @argv: Arguments array
 * @env: Environment variables
 * Return: (0) or exits with a status != 0
 */
int main(int argc, char **argv, char **env)
{
	size_t size = BUFSIZ;
	ssize_t res;
	char *buffer = NULL;
	char *tokens[100];
	/*
	 * Useful later, don't delete yet
	 * struct sigaction eof_act;
	 * struct sigaction int_act;
	*/

	if (!isatty(STDIN_FILENO))
	{
		getline(&buffer, &size, stdin);
		tokenize_input(buffer, tokens);
		execve(tokens[0], tokens, env);
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", argv[0], argc, tokens[0]);
		exit(EXIT_FAILURE);
	}
	/*
	* Found these useful for handling signals later, don't delete
	* int_act.sa_handler = sigint_handler;
	* int_act.sa_flags = SA_RESTART;

	* eof_act.sa_handler = sigquit_handler;

	* sigaction(SIGINT, &int_act, NULL);
	* sigaction(SIGQUIT, &eof_act, NULL);
	*/
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		res = getline(&buffer, &size, stdin);
		if (res < 0)
			clearerr(stdin);
		tokenize_input(buffer, tokens);
		evaluate_input(tokens, argv, env);
	}

	free(buffer);
	return (0);
}
