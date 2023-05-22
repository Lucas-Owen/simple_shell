#include "main.h"

/**
 * file_in_dir - Checks if a file is in a pathname
 * @pathname: Full path to file
 * Return: 1 if file is present and is a regular file, 0 otherwise
 */
int file_in_dir(char *pathname)
{
	struct stat statbuf;

	if (stat(pathname, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode))
			return (1);
	}
	return (0);
}

/**
 * eval_path - Resolves the command from the PATH environment variable
 * @command: The command to resolve
 * @envp: The current environment variables
 * Return: pointer to a malloced string with full path to command or NULL
 */
char *eval_path(char *command, char **envp)
{
	char *paths, *path, resolved_path[PATH_MAX];

	/* Check if file is in current directory first */
	if (file_in_dir(command))
		return (command);

	/* First find the PATH variable */
	paths = get_env("PATH", envp);
	if (paths == NULL)
		return (NULL);

	path = strtok(paths, ":");
	while (path != NULL)
	{
		strcpy(resolved_path, path);
		strcat(resolved_path, "/");
		strcat(resolved_path, command);
		if (file_in_dir(resolved_path))
		{
			free(paths);
			return (strdup(resolved_path));
		}
		path = strtok(NULL, ":");
	}
	free(paths);
	return (NULL);
}
