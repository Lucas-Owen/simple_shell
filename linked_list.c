#include "lists.h"
/**
 * add_node_end - Add a node at the end of a linked list
 * @head: The list_t
 * @tokens: Malloced list of commands
 * @sep: Comnand separator between this and the next
 * Return: The address of the new element or (NULL)
 */
list_t *add_node_end(list_t **head, char **tokens, char *sep)
{
	list_t *new = malloc(sizeof(list_t));
	list_t *temp = *head;

	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->tokens = tokens;
	new->sep = sep;

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
 * free_tokens - Frees dynamically allocated memory for tokens
 * and points the memory to NULL
 * @tokens: The pointer to tokens
 * Return: void
 */
void free_tokens(char **tokens)
{
	int i = 0;

	for (; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
}

/**
 * free_list - Frees all nodes in the list_t
 * @head: The list_t
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *temp;

	while (head != NULL)
	{
		temp = head->next;
		free_tokens(head->tokens);
		free(head->tokens);
		free(head->sep);
		free(head);
		head = temp;
	}
}
