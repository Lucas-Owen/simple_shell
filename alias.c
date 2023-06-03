#include "main.h"

/**
 * create_alias - Updates an alias name to the alias list.
 * Creates new if it does not exist
 * @token: Current alias to add
 * @aliases: head of alias list
 * Return: void
 */
void create_alias(char *token, alias_list **aliases)
{
	char *str = strdup(token);
	char *temp = str;
	char *name, *value;

	name = _strtok(&temp, "=");
	if (name)
	{
		value = _strtok(&temp, "=");
		if (value)
			add_alias(aliases, name, value);
	}
	free(str);
}

/**
 * print_alias - Finds and prints the alias with its name
 * if it exists
 * @aliases: Head of alias list
 * @name: Name to find
 * @status: Status after command execution
 * Return: void
 */
void print_alias(alias_list *aliases, char *name, int *status)
{
	alias_list *temp = find_alias(aliases, name);

	if (temp)
	{
		printf("%s='%s'\n", temp->name, temp->value);
		status = (EXIT_SUCCESS << 8);
		return;
	}
	dprintf(STDERR_FILENO, "alias: %s not found\n", name);
	*status = (EXIT_FAILURE << 8);
}

/**
 * print_aliases - Prints all aliases
 * if it exists
 * @aliases: Head of alias list
 * Return: void
 */
void print_aliases(alias_list *aliases)
{
	while (aliases)
	{
		printf("%s='%s'\n", aliases->name, aliases->value);
		aliases = aliases->next;
	}
}

/**
 * alias - Evaluates the alias command
 * @tokens: List of command strings beginning with 'alias'
 * @status: Status of previous executed command
 * @aliases: List of aliases
 * Return: void
 */
void alias(char **tokens, int *status, alias_list **aliases)
{
	int i = 1;

	if (tokens[i] == NULL)
		print_aliases(*aliases);
	*status = (EXIT_SUCCESS << 8);
	while (tokens[i])
	{
		if (strchr(tokens[i], '='))
			create_alias(tokens[i], aliases);
		else
			print_alias(*aliases, tokens[i], status);
		i++;
	}
}

/**
 * eval_alias - Returns the final value of the alias name
 * Searches until value of an alias name is no longer in the list
 * DO NOT INCLUDE CYCLES IN ALIASES, this will result in infinite loop
 * @aliases: Head of list of aliases
 * @name: Name of alias to find
 * Return: pointer to a alias list or NULL
 */
alias_list *eval_alias(alias_list *aliases, char *name)
{
	alias_list *prev = find_alias(aliases, name);
	alias_list *result = NULL;

	while (prev)
	{
		result = prev;
		prev = find_alias(aliases, result->value);
	}
	return (result);
}
