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
