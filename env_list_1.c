#include "shell.h"

/**
 * set_env_value - sets the value of a NAME in the env_list if it exist to the specified value
 * @env: the list to search
 * @NAME: the name to search for in the list
 * @value: value to be inserted
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
void set_env_value(env_list *env, const char *NAME, const char *value)
{
	env = insert_env(env, NAME, value);	
}

/**
 * get_env - returns the value of a NAME in the env_list if it exist
 * @env: the list to search
 * @NAME: the name to search for in the list
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
char *get_env(env_list *env, const char *NAME)
{
	env_list *current = env;
	
	if (current->next == NULL) return NULL;
	else if (strcmp(current->NAME, NAME) == 0) return (current->value);
	else return get_env(current->next, NAME);	
}

/**
 * delete_match - Deletes the first matching node from an env_list with a given NAME
 * @head: The head of the linked list
 * @delete_NAME: The NAME of list to be deleted
 *
 * Return: A pointer to the modified linked list
 */
env_list *delete_match(env_list *head, char *delete_NAME)
{
	env_list *temp = NULL;

	if (head == NULL) return (NULL);
	else if (head->next != NULL && strcmp(head->next->NAME, delete_NAME) == 0)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
		return (head);
	}
	else
	{
		head->next = delete_match(head->next, delete_NAME);
		return (head);
	}
}

/**
 * delete_duplicate - Deletes duplicate nodes from an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void delete_duplicate(env_list *head)
{
	env_list *cur1, *cur2, *dup;

	if (head == NULL)
		return;

	head = revers_list(head);
	cur1 = head;

	while (cur1 != NULL && cur1->next != NULL)
	{
		cur2 = cur1;
		while (cur2->next != NULL)
		{
			if (strcmp(cur1->NAME, cur2->next->NAME) == 0)
			{
				dup = cur2->next;
				cur2->next = cur2->next->next;
				free(dup);
			}
			else
			{
				cur2 = cur2->next;
			}
		}
		cur1 = cur1->next;
	}
	head = revers_list(head);
}

/**
 * revers_list - Reverses a linked list
 * @head: The head of the linked list
 *
 * Return: A pointer to the reversed linked list
 */
env_list *revers_list(env_list *head)
{
	env_list *current = NULL, *next = NULL, *tmp = NULL; 
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	current = head;
	next = head->next;

	current->next = NULL;

	while (next != NULL)
	{
		tmp = next->next;
		next->next = current;
		current = next;
		next = tmp;
	}
	return (current);	
}
