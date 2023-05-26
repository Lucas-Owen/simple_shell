#include "main.h"
/**
 * eval_inbuilt_var - Checks string for $? and $$
 * @str: The string reference
 * @buf: Buffer to print the expansion
 * @status: Exit status of previous process
 * Return: 1 if evaluated as inbuilt, 0 otherwise
 */
int eval_inbuilt_var(char **str, char **buf, int *status)
{
	size_t offset;

	if (*(*str) == '$')
	{
		offset = sprintf((*buf), "%d", getpid());
		(*buf) += offset;
		++(*str);
		return (1);
	}
	else if (*(*str) == '?')
	{
		offset = sprintf((*buf), "%d", WEXITSTATUS(*status));
		(*buf) += offset;
		++(*str);
		return (1);
	}
	return (0);
}
/**
 * eval_path_var - Checks if string is a path variable
 * @str: The string reference
 * @buf: Buffer to print the expansion
 * @envp: The list of environment variables
 * Return: 1 if evaluated in path, 0 otherwise
 */
int eval_path_var(char **str, char **buf, char **envp)
{
	size_t offset;
	char *temp = get_env(*str, envp);

	if (temp != NULL)
	{
		offset = sprintf((*buf), "%s", temp);
		(*buf) += offset;
		free(temp);
		return (1);
	}
	return (0);
}

/**
 * eval_other_var - Checks if string is another variable
 * or just a string
 * @str: The string reference
 * @buf: Buffer to print the expansion
 * @envp: The list of environment variables
 * Return: void
 */
void eval_other_var(char **str, char **buf, char **envp)
{
	size_t offset;
	char *stop = strchr(*str, '$');

	if (stop != NULL)
		*stop = '\0';
	if (*(*str) == '\0')
	{
		offset = sprintf((*buf), "%c", '$');
		(*buf) += offset;
	}
	else
		eval_path_var(str, buf, envp);

	(*str) += strlen(*str);
	if (stop != NULL)
		*stop = '$';
}
/**
 * eval_variable - Resolves the value of the variable passed
 * @variable: The variable, containing $ or not
 * @envp: The list of environment variables
 * @status: Exit status of previous process
 * Return: A malloced string containing the evaluation or NULl
 * if malloc fails
 */
char *eval_variable(char *variable, char **envp, int *status)
{
	char *start;
	char buffer[BUFSIZ], *buf = buffer;
	size_t offset;

	if (variable == NULL)
		return (NULL);
	start = strchr(variable, '$');
	if (!start)
		return (strdup(variable));
	buf[0] = '\0';
	offset = strcspn(variable, "$");
	strncat(buf, variable, offset);
	buf += offset;
	while (start != NULL)
	{
		++start;
		if (eval_inbuilt_var(&start, &buf, status))
			;
		else
			eval_other_var(&start, &buf, envp);
		offset = strcspn(start, "$");
		strncat(buf, start, offset);
		buf += offset;
		start = strchr(start, '$');
	}
	return (strdup(buffer));
}
