#include "lists.h"
/**
 * add_token - Add a node at the end of a linked list
 * @head: The token_list
 * @tokens: Malloced list of commands
 * @sep: Comnand separator between this and the next
 * Return: The address of the new element or (NULL)
 */
token_list *add_token(token_list **head, char **tokens, char *sep)
{
	token_list *new = malloc(sizeof(token_list));
	token_list *temp = *head;

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
 * free_token_list - Frees all nodes in the token_list
 * @head: The token_list
 * Return: void
 */
void free_token_list(token_list *head)
{
	token_list *temp;

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
