#include "main.h"

/**
 * is_sep - Checks if an input token is a separator
 * separators include ";, &&, ||"
 * @input: The string to check
 * Return: 1 for true, 0 for false
 */
int is_sep(char *input)
{
	if (input == NULL
		|| strcmp(input, ";") == 0
		|| strcmp(input, "&&") == 0
		|| strcmp(input, "||") == 0)
		return (1);
	return (0);
}
/**
 * init_commands - breaks line of commands into a linked list
 * Each node contains a command and a separator - for the next command
 * separators include ';, &&, ||'
 * @tokens: Array of strings representing a signle line of command
 * Each token is set to NULL after this
 * Return: list_t* lilnked list
 */
list_t *init_commands(char **tokens)
{
	list_t *head = NULL;
	char **command = NULL;
	int i = 0, j = 0, k;

	while (1)
	{
		if (is_sep(tokens[i]))
		{
			command = malloc(sizeof(char *) * (i - j + 1));
			for (k = 0; j < i; j++, k++)
				command[k] = tokens[j];
			command[k] = NULL;
			add_node_end(&head, command, tokens[j]);
			if (tokens[i] != NULL)
			{
				++i;
				++j;
			}
		}
		if (tokens[i] == NULL)
			break;
		i++;
	}
	while (i > 0)
		tokens[i--] = NULL;
	return (head);
}

/**
 * evaluate_input - Evaluates input and calls appropriate functions
 * @argv: Like argv in main
 * @tokens: Tokenized input string from terminal
 * @env: The environment variables
 * @istty: Whether input is from terminal or not, 1 or 0 resp
 * @line: line number
 * @status: Status of previously exec'd task
 */
void evaluate_input(char **tokens, char **argv, char **env,
	int istty, int line, int *status)
{
	char *resolved_path = NULL;
	pid_t childpid = 0;

	if (tokens[0] == NULL)
		return;

	resolved_path = eval_path(tokens[0], env);
	if (resolved_path == NULL)
	{
		if (istty)
			dprintf(STDERR_FILENO, "%s: command not found\n",
				tokens[0]);
		else
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
				argv[0], line, tokens[0]);
		*status = (127 << 8);
		return;
	}
	free(tokens[0]);
	tokens[0] = resolved_path;
	childpid = fork();
	if (childpid == 0)
	{
		execve(tokens[0], tokens, env);
		perror(argv[0]);
		_exit(EXIT_FAILURE);
	}
	wait(status);
}

/**
 * eval_inbuilt_command - Checks if a command is an inbuilt command
 * and evaluate it
 * @tokens: The tokens with command and args
 * @argv: Like argv in main
 * @envp: Currentn execution envirionment
 * @line: line number
 * @status: Status of previously exec'd task
 * @head: Linked list of commands
 * Return: 1 if true, (0) otherwise
 */
int eval_inbuilt_command(char **tokens, char **argv, char **envp,
	int line, int *status, list_t *head)
{
	(void) argv;
	if (tokens[0] == NULL)
		return (0);
	if (strcmp(tokens[0], "env") == 0)
	{
		print_env(envp);
		*status = (EXIT_SUCCESS << 8);
		return (1);
	}
	if (strcmp(tokens[0], "exit") == 0)
	{
		eval_exit(argv, tokens, line, status, head);
		return (1);
	}
	if (strcmp(tokens[0], "cd") == 0)
	{
		change_dir(argv, tokens, envp, line, status);
		return (1);
	}
	if (strcmp(tokens[0], "setenv") == 0)
	{
		set_env(tokens, status);
		return (1);
	}
	if (strcmp(tokens[0], "unsetenv") == 0)
	{
		unset_env(tokens, status);
		return (1);
	}

	return (0);
}


/**
 * evaluate_input - Evaluates input and calls appropriate functions
 * @argv: Like argv in main
 * @tokens: Tokenized input string from terminal
 * @env: The environment variables
 * @istty: Whether input is from terminal or not, 1 or 0 resp
 * @line: line number
 * @status: Status of previously exec'd task
 */
void run_line_of_command(char **tokens, char **argv, char **env,
	int istty, int line, int *status)
{
	list_t *head = init_commands(tokens);
	list_t *temp;

	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (eval_inbuilt_command(temp->tokens, argv, env,
			line, status, head))
			continue;
		evaluate_input(temp->tokens, argv, env, istty, line, status);
		if (temp->sep == NULL)
			continue;
		if (strcmp("&&", temp->sep) == 0 && WEXITSTATUS(*status) != 0)
			break;
		if (strcmp("||", temp->sep) == 0 && WEXITSTATUS(*status) == 0)
			break;
	}
	free_list(head);
}
