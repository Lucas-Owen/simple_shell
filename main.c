#include "main.h"

void free_tokens(char **tokens);
void check_exit(char **argv, char *buffer, char **tokens);
void before_exit(char *buffer, char **tokens);

/**
 * main - Simple unix shell
 * @argc: Length of argv
 * @argv: Arguments array
 * @env: Environment variables
 * Return: (0) or exits with a status != 0
 */
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	size_t size = BUFSIZ;
	ssize_t res;
	char *buffer = NULL;
	char *tokens[MAX_TOKENS];

	/*
	 * Useful later, don't delete yet
	 * struct sigaction eof_act;
	 * struct sigaction int_act;
	*/
	if (!isatty(STDIN_FILENO))
	{
		_getline(&buffer, &size, stdin);
		tokenize_input(buffer, tokens);
		check_exit(argv, buffer, tokens);
		evaluate_input(tokens, argv, env, 0);
		before_exit(buffer, tokens);
		exit(EXIT_FAILURE);
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
		res = _getline(&buffer, &size, stdin);
		if (res < 0)
			clearerr(stdin);
		buffer[res] = 0;
		tokenize_input(buffer, tokens);
		check_exit(argv, buffer, tokens);
		evaluate_input(tokens, argv, env, 1);
		free_tokens(tokens);
	}
	return (0);
}

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
 * check_exit - checks if an exit command was issued
 * exits the shell after freeing dynamically allocated memory
 * @argv: Like argv in main
 * @buffer: The input buffer
 * @tokens: Pointer to strings storing sequence of commands
 * Return: void
 */
void check_exit(char **argv, char *buffer, char **tokens)
{
	int status;
	char *endptr = NULL;

	if (strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1] != NULL)
			status = strtol(tokens[1], &endptr, 10);
		if (endptr && *endptr)
		{
			dprintf(STDERR_FILENO,
				"%s: %d: %s: Illegal number: %s\n",
				argv[0], 1, tokens[0], endptr);
			return;
		}
		before_exit(buffer, tokens);
		exit(status);
	}
}

/**
 * before_exit - frees dynamically allocated memory
 * @buffer: Memory allocated to buffer
 * @tokens: Memory allocated to tokens
 * Return: void
 */
void before_exit(char *buffer, char **tokens)
{
	free(buffer);
	free_tokens(tokens);
}
