#include "shell.h"

/**
 * free_recursive - free's memory allocated in the alias list recursively
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_recursive(alias *head)
{
	if (head == NULL)
		return;

	free_recursive(head->next);
	free(head->NAME);
	free(head->value);
	free(head);
}

/**
 * check_NAME - Checks if a NAME is present in a linked list
 * @head: The head of the linked list
 * @NAME: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool check_NAME(alias *head, const char *NAME)
{
	if (head == NULL)
		return (false);
	else if (strcmp(head->NAME, NAME) == 0)
		return (true);
	else
		return (check_NAME(head->next, NAME));
}

/**
 * print_alias - Prints the values of an alias list
 * @head: The head of the linked list
 * @oki: struct of type okeoma
 *
 * Return: void
 */
void print_alias(alias *head, okeoma *oki)
{
	alias *current = head;

	if (current == NULL)
	{
		p(STE, "%s: %d: %s: no defined alias\n",
		oki->N, oki->c, oki->av[0]);
	}
	while (current != NULL)
	{
		p(STO, "%s='%s'\n", current->NAME, current->value);
		current = current->next;
	}
}

/**
 * print_s_alias - Prints the values of a specific alias
 * @head: The head of the linked list
 * @NAME: Name of the alias to print
 * @oki: struct of type okeoma
 *
 * Return: void
 */
void print_s_alias(alias *head, const char *NAME, okeoma *oki)
{
	alias *current = head;

	if (current == NULL)
	{
		p(STE, "%s: %d: %s: no defined alias\n",
		oki->N, oki->c, oki->av[0]);
	}
	else
	{
		while (current != NULL)
		{
			if (strcmp(current->NAME, NAME) == 0)
				p(STO, "%s='%s'\n", current->NAME, current->value);

			current = current->next;
		}
	}
}

/**
 * insert - Inserts a new alias with a given NAME
 *		and value at the tail of a linked list
 * @head: The head of the linked list
 * @NAME: name of variable
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
alias *insert(alias *head, const char *NAME, const char *value)
{
	alias *new_node = NULL, *current = head;

	new_node = malloc(sizeof(alias));
	new_node->value = strdup(value);
	new_node->NAME = strdup(NAME);
	new_node->next = NULL;

	if (head == NULL)
		return (new_node);
	else if (check_NAME(current, NAME) == true)
	{
		while (current != NULL)
		{
			if (strcmp(current->NAME, NAME) == 0)
			{
				free(current->value);
				current->value = strdup(value);
			}
			current = current->next;
		}
		return (head);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		return (head);
	}
}
