#include "main.h"

/**
 * _getline - gets a line of input from the specified file
 * @buf: Buffer to store input, ensure it has enough size to fit input
 * @stream: File stream to read from
 * Return: The number of bytes read, or -1 on error
 */
int _getline(char *buf, FILE *stream)
{
	static char buffer[BUFSIZ];
	static int start;
	static int end;
	int stop;
	int f_no = fileno(stream);
	int res;

	if (buf == NULL)
		return (-1);

	buf[0] = '\0';
	if (start >= end)
	{
		buffer[0] = '\0';
		res = read(f_no, buffer, BUFSIZ - 1);
		if (res <= 0)
			return (-1);
		start = 0;
		end = res;
	}
	for (stop = start; buffer[stop] && buffer[stop] != '\n'; ++stop)
		;
	res = stop - start;
	strncat(buf, buffer + start, res);
	start = stop + 1;
	return (res);
}
