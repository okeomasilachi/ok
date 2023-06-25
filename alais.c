#include "main.h"


/**
 * free_list - free's memory allocated by list_from_env
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_alias_list(alias *head)
{
	alias *current = head, *temp = NULL;
	
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->NAME);
		free(temp->value);
		free(temp);
	}
}

/**
 * free_list_recursive - free's memory allocated by list_from_env recursively
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_recursive(alias *head)
{
	if (head == NULL) return;

	free_recursive(head->next);
	free(head->NAME);
	free(head->value);
	free(head);
}

/**
 * is_value - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool check_value(alias *head, const char *value)
{
	if (head == NULL) return (false);
	else if (strcmp(head->NAME, value) == 0) return (true);
	else return (check_value(head->next, value));
}

/**
 * is_NAME - Checks if a NAME is present in a linked list
 * @head: The head of the linked list
 * @NAME: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool check_NAME(alias *head, const char *NAME)
{
	if (head == NULL) return (false);
	else if (strcmp(head->NAME, NAME) == 0) return (true);
	else return (check_NAME(head->next, NAME));
}

/**
 * print - Prints the values of an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void print_alias(alias *head)
{
	alias *current;
	current = head;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->NAME, current->value);
		current = current->next;
	}
	return;
	
}

/**
 * print - Prints the values of an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void print_s_alias(alias *head, const char *NAME)
{
	alias *current;
	current = head;

	while (current != NULL)
	{
		if (strcmp(NAME, current->NAME) == 0)
		{
			printf("%s='%s'\n", current->NAME, current->value);
		}

		current = current->next;
	}
	return;
	
}

/**
 * insert_env - Inserts a new alias with a given NAME and value at the tail of a linked list
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

/**
 * delete_match - Deletes the first matching node from an alias with a given NAME
 * @head: The head of the linked list
 * @delete_NAME: The NAME of list to be deleted
 *
 * Return: A pointer to the modified linked list
 */
alias *delete_alias_mth(alias *head, char *delete_NAME)
{
	alias *temp = NULL;

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
		head->next = delete_alias_mth(head->next, delete_NAME);
		return (head);
	}
}

/**
 * get_env - returns the value of a NAME in the alias if it exist
 * @env: the list to search
 * @NAME: the name to search for in the list
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
char *get_alias(alias *env, const char *NAME)
{
	alias *current = env;
	
	if (current->next == NULL) return NULL;
	else if (strcmp(current->NAME, NAME) == 0) return (current->value);
	else return get_alias(current->next, NAME);	
}

/**
 * revers_env_list - Reverses a linked list
 * @head: The head of the linked list
 *
 * Return: A pointer to the reversed linked list
 */
alias *revers(alias *head)
{
	alias *current = NULL, *next = NULL, *tmp = NULL; 
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

/**
 * delete_duplicate - Deletes duplicate nodes from an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void delete_dup(alias *head)
{
	alias *cur1, *cur2, *dup;

	if (head == NULL)
		return;

	head = revers(head);
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
	head = revers(head);
}



/**
 * set_env_value - sets the value of a NAME in the alias if it exist to the specified value
 * @env: the list to search
 * @NAME: the name to search for in the list
 * @value: value to be inserted
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
void set_alias(alias *env, const char *NAME, const char *value)
{
	env = insert(env, NAME, value);	
}


void alias_command(okeoma *oki)
{
	alias *cur = oki->head;

	while (cur != NULL)
	{
		printf("%s=%s\n", cur->NAME, cur->value);
		cur = cur->next;
	}
	return;
}


int main(void)
{
	char *check = malloc(10), *c1, *tok;
	strcpy(check, "okeoma l");
	int len = 0;
	alias *Alias, *cur;

	printf("%s\n", check);
	tok = strtok(check, " \n");

	while (tok != NULL)
	{
		if (strcmp(tok, "l") == 0)
		{
			tok = "onyedibia";
		}
		len += strlen(tok) + 1;
		Alias = insert(Alias, tok, tok);
		tok = strtok(NULL, " \n");
	}
	cur = Alias;
	c1 = malloc(sizeof(char) * len);
	if (c1 == NULL)
		puts("yes");
	c1[0] = '\0';
	while (cur != NULL)
	{
		strcat(c1, cur->value);
		strcat(c1, " ");

		cur = cur->next;
	}
	len = strlen(c1);
	c1[len + 1] = '\0';

	printf("%s\n", c1);

	return 0;
}