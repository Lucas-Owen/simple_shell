#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include <string.h>

/**
 * struct list_t - singly linked list of commands to run
 * @tokens: String array of commands
 * @sep: Command separator to the next
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_t
{
	char **tokens;
	char *sep;
	struct list_t *next;
} token_list;

token_list *add_token(token_list **head, char **tokens, char *sep);
void free_tokens(char **tokens);
void free_token_list(token_list *head);

/**
 * struct list_a - singly linked list of aliases of commands
 * @name: String array of commands
 * @value: Command separator to the next
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_a
{
	char *name;
	char *value;
	struct list_a *next;
} alias_list;

alias_list *add_alias(alias_list **head, char *name, char *value);
void free_alias_list(alias_list *head);
alias_list *find_alias(alias_list *head, char *name);

#endif
