#include "main.h"

/**
 * sigint_handler - signal handler that handles SIGINT
 * received
 */
void sigint_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * sigquit_handler - signal handler that handles SIGQUIT
 * received
 */
void sigquit_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "Quit\n", 5);
	_exit(0);
}
