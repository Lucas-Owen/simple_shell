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
