#include "main.h"

/**
 * print_env - print environment variables passed as argument
 * @envp: The environment variables
 * Return: void
 */
void print_env(char **envp)
{
	int i = 0;

	while (envp[i])
		puts(envp[i++]);
}

/**
 * get_env - Gets the name and value of the environment variable passed to it
 * @name: Name of the environment variable
 * @envp: The full list of environment variables
 * Return: Malloced (char *) or NULL
 */
char *get_env(char *name, char **envp)
{
	size_t i = 0, len = strlen(name);

	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], name, len) == 0
			&& envp[i][len] == '=')
			break;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	return (strdup(envp[i] + len + 1));
}

/**
 * set_env - updates or sets an environment variable
 * @tokens: Input containing 'setenv VARIABLE VALUE'
 * @status: Status of last executed command
 * Return: void
 */
void set_env(char **tokens, int *status)
{
	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] != NULL)
	{
		dprintf(STDERR_FILENO,
			"%s: Invalid number of arguments\n",
			tokens[0]);
		*status = (EXIT_FAILURE << 8);
		return;
	}
	if (setenv(tokens[1], tokens[2], 1) < 0)
	{
		perror("setenv");
		*status = (EXIT_FAILURE << 8);
		return;
	}
	*status = (EXIT_SUCCESS << 8);
}

/**
 * unset_env - deletes an environment variable
 * @tokens: Input containing 'unsetenv VARIABLE'
 * @status: Status of last executed command
 * Return: void
 */
void unset_env(char **tokens, int *status)
{
	if (tokens[1] == NULL || tokens[2] != NULL)
	{
		dprintf(STDERR_FILENO,
			"%s: Invalid number of arguments\n",
			tokens[0]);
		*status = (EXIT_FAILURE << 8);
		return;
	}
	if (unsetenv(tokens[1]) < 0)
	{
		perror("unsetenv");
		*status = (EXIT_FAILURE << 8);
		return;
	}
	*status = (EXIT_SUCCESS << 8);
}
