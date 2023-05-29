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
	int line = 0;
	int istty = isatty(STDIN_FILENO);
	int status = 0;
	char buffer[BUFSIZ];
	char *tokens[MAX_TOKENS];
	FILE *stream;

	initialize_tokens(tokens);
	stream = argc == 2 ? fopen(argv[1], "r") : stdin;
	if (stream == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: Can't open %s\n",
			argv[0], line, argv[1]);
		exit(127);
	}
	if (istty)
		dprintf(STDOUT_FILENO, "($) ");
	while (_getline(buffer, stream) >= 0)
	{
		tokenize_input(buffer, tokens, environ, &status);
		run_line_of_command(tokens, argv, environ, istty, ++line, &status);
		if (istty)
			dprintf(STDOUT_FILENO, "($) ");
	}
	if (istty)
		dprintf(STDOUT_FILENO, "\n");
	fclose(stream);
	exit(WEXITSTATUS(status));
}

