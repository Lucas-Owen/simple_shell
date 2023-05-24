#include "main.h"
/**
 * _strtok - works like strtok, tokenizes input according to delimeters
 * specified. Is destructive
 * @str: The string to tokenize
 * @delim: string of delimeters
 * Return: Pointer to a string or NULL
 */
char *_strtok(char *str, char *delim)
{
	static char *ptr;
	char *token = NULL;
	int offset = 0;

	if (delim == NULL)
		return (str);
	if (str != NULL)
		ptr = str;
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
	return (token[0] == '\0' ? NULL : token);
}
/**
 * tokenize_input - Breaks the input into a command followed by its arguments
 * @buffer: The input
 * @tokens: Where to store the tokens
 */
void tokenize_input(char *buffer, char **tokens)
{
	char *token;
	int i = 0;

	if (buffer == NULL)
		return;
	token = _strtok(buffer, " ");

	while (token != NULL && i < MAX_TOKENS)
	{
		tokens[i] = strdup(token);
		token = _strtok(NULL, " ");
		i++;
	}

	tokens[i] = NULL;
}
