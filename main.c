#include "main.h"


/**
 * main - Simple unix shell
 * @argc: Length of argv
 * @argv: Arguments array
 * @env: Environment variables
 * Return: (0) or exits with a status != 0
 */
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	ssize_t res;
	int line = 0;
	int status = 0;
	char buffer[BUFSIZ];
	char *tokens[MAX_TOKENS];

	/*
	 * Useful later, don't delete yet
	 * struct sigaction eof_act;
	 * struct sigaction int_act;
	*/
	if (!isatty(STDIN_FILENO))
	{
		while (_getline(buffer, stdin) >= 0)
		{
			tokenize_input(buffer, tokens);
			evaluate_input(tokens, argv, env, 0, ++line, &status);
			free_tokens(tokens);
		}
		eval_exit(argv, tokens, line, &status);
	}
	/*
	* Found these useful for handling signals later, don't delete yet
	* int_act.sa_handler = sigint_handler;
	* int_act.sa_flags = SA_RESTART;
	* eof_act.sa_handler = sigquit_handler;
	* sigaction(SIGINT, &int_act, NULL);
	* sigaction(SIGQUIT, &eof_act, NULL);
	*/
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		res = _getline(buffer, stdin);
		if (res < 0)
			clearerr(stdin);
		tokenize_input(buffer, tokens);
		evaluate_input(tokens, argv, env, 1, line, &status);
		free_tokens(tokens);
	}
	return (0);
}

