#include "main.h"

/**
 * _getline - gets a line of input from the specified file
 * @buf: Buffer to store input, malloced if null. Always ends
 * with a new line if successful
 * @n: Size to read from input stream
 * @stream: File stream to read from
 * Return: The number of bytes read, or -1 on error
 */
int _getline(char **buf, size_t *n, FILE *stream)
{
	static char buffer[BUFSIZ];
	int f_no = fileno(stream);
	int res, oldsize = strlen(buffer);

	res = read(f_no, buffer, *n);
	if (res > 0)
	{
		if (*buf == NULL)
			*buf = malloc(sizeof(char) * (res + 1));
		else if (oldsize < res)
		{
			free(*buf);
			*buf = malloc(sizeof(char) * (res + 1));
		}
		if (*buf != NULL)
			strcpy(*buf, buffer);
	}
	return (res);
}
