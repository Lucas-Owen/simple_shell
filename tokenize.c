#include "main.h"
/**
 * _strtok - works like strtok, tokenizes input according to delimeters
 * specified. Is destructive
 * @str: The string to tokenize, pass this unmodified every time
 * @delim: string of delimeters
 * Return: Pointer to a string or NULL(also if length of string is 0)
 */
char *_strtok(char **str, char *delim)
{
	char *ptr;
	char *token;
	int offset = 0;

	if (delim == NULL)
		return (*str);
	if (str != NULL && *str != NULL)
		ptr = *str;
	else
		return (NULL);
	token = ptr;
	offset = strspn(ptr, delim);
	token += offset;
	ptr = token;
	offset = strcspn(ptr, delim);
	if (offset > 0)
	{
		ptr += offset;
		if (*ptr)
		{
			*ptr = '\0';
			++ptr;
		}
	}
	*str = ptr;
	return (token[0] == '\0' ? NULL : token);
}
/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * @buffer: The input
 * @tokens: Where to store the tokens
 * @envp: The environment variables
 * @status: Status of previously exec'd task
 */
void tokenize_input(char *buffer, char **tokens, char **envp, int *status)
{
	char *token;
	int i = 0;

	if (buffer == NULL)
		return;
	token = _strtok(&buffer, " ");

	while (token != NULL && i < MAX_TOKENS)
	{
		/* Expand variables */
		tokens[i] = eval_variable(token, envp, status);
		/* Remove comments */
		if (tokens[i][0] == '#')
		{
			free(tokens[i]);
			tokens[i] = NULL;
			break;
		}
		token = _strtok(&buffer, " ");
		i++;
	}
}
