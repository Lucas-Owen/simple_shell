#include "main.h"
/**
 * initialize_tokens - initializes tokens array to NULL
 * @tokens: The tokens array
 */
void initialize_tokens(char **tokens)
{
	int i;

	for (i = 0; i < MAX_TOKENS; i++)
		tokens[i] = NULL;
}
/**
 * main - Simple unix shell
 * @argc: Length of argv
 * @argv: Arguments array
 * @env: Environment variables
 * Return: (0) or exits with a status != 0
 */
int main(int argc, char **argv,
	__attribute__((unused)) char **env)
{
	ssize_t res;
	int line = 0;
	int status = 0;
	char buffer[BUFSIZ];
	char *tokens[MAX_TOKENS];
	FILE *stream;

	initialize_tokens(tokens);
	if (!isatty(STDIN_FILENO) || argc == 2)
	{
		stream = argc == 2 ? fopen(argv[1], "r") : stdin;
		if (stream == NULL)
		{
			dprintf(STDERR_FILENO, "%s: %d: Can't open %s\n",
				argv[0], line, argv[1]);
			exit(127);
		}
		while (_getline(buffer, stream) >= 0)
		{
			tokenize_input(buffer, tokens, environ, &status);
			evaluate_input(tokens, argv, environ, 0, ++line, &status);
			free_tokens(tokens);
		}
		fclose(stream);
		eval_exit(argv, tokens, line, &status);
	}
	while (1)
	{
		dprintf(STDOUT_FILENO, "($) ");
		res = _getline(buffer, stdin);
		if (res < 0)
			clearerr(stdin);
		tokenize_input(buffer, tokens, environ, &status);
		evaluate_input(tokens, argv, environ, 1, line, &status);
		free_tokens(tokens);
	}
	return (0);
}

