#include "lists.h"
/**
 * add_alias - Add a node at the end of an alias_list if it does not exist
 * The value is replaced if name exists
 * @head: The alias_list
 * @name: Name of the alias
 * @value: Comnand separator between this and the next
 * Return: The address of the new element or (NULL)
 */
alias_list *add_alias(alias_list **head, char *name, char *value)
{
	alias_list *new;
	alias_list *temp;

	temp = find_alias(*head, name);
	if (temp)
	{
		free(temp->value);
		temp->value = strdup(value);
		return (temp);
	}

	new = malloc(sizeof(alias_list));
	temp = *head;

	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->name = strdup(name);
	new->value = strdup(value);

	if (head == NULL)
		return (new);
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
	return (new);
}

/**
 * find_alias - Finds a node containing the name of the alias specified
 * @head: Head of the alias list
 * @name: Name to find
 * Return: Pointer to the node containing the alias, or NULL
 */
alias_list *find_alias(alias_list *head, char *name)
{
	alias_list *temp = head;

	while (temp)
	{
		if (strcmp(name, temp->name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * free_alias_list - Frees all nodes in the alias_list
 * @head: The alias_list
 * Return: void
 */
void free_alias_list(alias_list *head)
{
	alias_list *temp;

	while (head != NULL)
	{
		temp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = temp;
	}
}
