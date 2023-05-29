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
 * space_out - Look for specified substring and pad with spaces
 * Replaces all occurrences
 * @buffer: The whole string
 * @str: Substring to look for in buffer and pad
 * Return: void
 */
void space_out(char *buffer, const char *str)
{
	char *buf;
	size_t len_buf = strlen(buffer);
	size_t len_str = strlen(str);
	size_t i;

	buf = strstr(buffer, str);
	for (; buf; buf = strstr(buf + len_str + 2, str))
	{
		memmove(buf + len_str + 2,
			buf + len_str,
			buffer + len_buf - buf + 1);
		*buf = ' ';
		for (i = 1; i <= len_str; i++)
			*(buf + i) = str[i - 1];
		*(buf + i) = ' ';
		len_buf = strlen(buffer);
	}
}
/**
 * add_spaces_to_separators - Adds spaces before and after separators like
 * ;, && and ||
 * @buffer: The buffer with possible unspaced separators
 * The buffer is assumed large enough to be expanded
 * Return: void
 */
void add_spaces_to_separators(char *buffer)
{

	if (buffer == NULL)
		return;

	space_out(buffer, ";");
	space_out(buffer, "&&");
	space_out(buffer, "||");
}
/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * Removes spaces
 * Takes into account special separators (;, ||, &&)
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
	add_spaces_to_separators(buffer);
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
