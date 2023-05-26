#include "main.h"

/**
 * update_env - Update the PWD and OLDPWD environment variables
 * @envp: The environment variables
 * @status: Status of last command
 * Return: 0 on success, -1 on failure
 */
int update_env(char **envp, int *status)
{
	char *oldpwd = get_env("PWD", envp);
	char pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	if (setenv("PWD", pwd, 1) < 0)
	{
		perror("setenv");
		*status = (EXIT_FAILURE << 8);
		return (-1);
	}
	if (setenv("OLDPWD", oldpwd, 1) < 0)
	{
		perror("setenv");
		*status = (EXIT_FAILURE << 8);
		return (-1);
	}
	free(oldpwd);
	return (0);
}
/**
 * change_dir - Changes working directory of calling process
 * @tokens: The tokens with command and args
 * @argv: Like argv in main
 * @envp: Currentn execution envirionment
 * @status: Status of previously exec'd task
 * Return: void
 */
void change_dir(char **argv, char **tokens, char **envp, int *status)
{
	int res;

	if (tokens[2] != NULL)
	{
		dprintf(STDERR_FILENO,
			"%s: %s: too many arguments\n", argv[0], tokens[0]);
		*status = (EXIT_FAILURE << 8);
		return;
	}
	if (tokens[1] == NULL)
		tokens[1] = get_env("HOME", envp);
	else if (strcmp(tokens[1], "-") == 0)
	{
		free(tokens[1]);
		tokens[1] = get_env("OLDPWD", envp);
		if (tokens[1] == NULL)
			tokens[1] = get_env("PWD", envp);
		puts(tokens[1]);
	}
	res = chdir(tokens[1]);
	if (res < 0)
	{
		dprintf(STDERR_FILENO,
			"%s: %s: %s: No such file or directory\n",
			argv[0], tokens[0], tokens[1]);
		*status = (EXIT_FAILURE << 8);
		return;
	}
	if (update_env(envp, status) == 0)
		*status = (EXIT_SUCCESS << 8);
}
