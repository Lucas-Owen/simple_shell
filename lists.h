#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

/**
 * struct list_s - singly linked list of commands to run
 * @tokens: String array of commands
 * @sep: Command separator to the next
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char **tokens;
	char *sep;
	struct list_s *next;
} list_t;

list_t *add_node_end(list_t **head, char **tokens, char *sep);
void free_tokens(char **tokens);
void free_list(list_t *head);


#endif
