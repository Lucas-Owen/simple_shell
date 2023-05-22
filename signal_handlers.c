#include "main.h"

/**
 * sigint_handler - signal handler that handles SIGINT
 * @signum: The signal number
 */
void sigint_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * sigquit_handler - signal handler that handles SIGQUIT
 * @signum: The signal number
 */
void sigquit_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "Quit\n", 5);
	_exit(0);
}
