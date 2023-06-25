#include "main.h"

/*void find_char(const char *dest, int character)
{
	char *str_cpy = strchr(dest, character);

	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
	}
}
*/


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
	alias *current = head;

	while (current != NULL)
	{
		if (strcmp(current->NAME, NAME) == 0)
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

char *get_value(char *str)
{
	char *val = strdup(str);

	if (strstr(val, "=") != NULL)
	{
		val = (strstr(val, "=") + 1);
		return (val);
	}

	return (NULL);
}

void alias_(okeoma *oki)
{
	char *ch;

	if (oki->av[1] == NULL)
	{
		print_alias(oki->pos);
		return;
	}
	else if (oki->av[1] != NULL && check_NAME(oki->pos, oki->av[1]) != true && (ch = strstr(oki->av[1], "=")) != NULL)
	{
		char *value = strdup(oki->av[1]);
		
		value = get_value(value);
		find_char(oki->av[1], '=');
		oki->pos = insert(oki->pos, oki->av[1], value);
		return;
	}
	else
	{
		int i;
		for (i = 1; oki->av[i] != NULL; i++)
		{
			if (check_NAME(oki->pos, oki->av[i]) == true)
				print_s_alias(oki->pos, oki->av[i]);
			else
				p(STE, "%s: %ld: %s: %s: not found\n", oki->Name, oki->com_num, oki->av[0], oki->av[i]);
		}
		return;
	}
	
}

bool alias_checker(alias *head, char *arr)
{
	char *tok, *che = strdup(arr);
	alias *cur = head;

	if (head == NULL || arr == NULL) return false;

	tok = strtok(che, " \n");
	while (tok != NULL)
	{
		while (cur != NULL)
		{
			if (strcmp(tok, cur->NAME) == 0)
				return true;

			cur = cur->next;
		}
		cur = head;
		tok = strtok(NULL, " \n");
	}
	return (false);
}

char *command(alias *head, char *check)
{
	char *c1 = NULL, *tok, *che = strdup(check);
	int len = 0;
	alias *Alias = NULL, *cur = head;

	if (head == NULL)
		return (check);

	tok = strtok(che, " \n");
	while (tok != NULL)
	{
		while (cur != NULL)
		{
			if (strcmp(tok, cur->NAME) == 0)
			{
				tok = strdup(cur->value);
			}
			cur = cur->next;
		}
		len += strlen(tok) + 1;
		Alias = insert(Alias, tok, tok);
		cur = head;
		tok = strtok(NULL, " \n");
	}
	cur = Alias;
	c1 = malloc(sizeof(char) * len);
	c1[0] = '\0';
	while (cur != NULL)
	{
		strcat(c1, cur->value);
		strcat(c1, " ");

		cur = cur->next;
	}
	c1[strlen(c1) + 1] = '\0';
	return(c1);
}


/*int main()
{
	alias *head = insert(head, "okeoma", "ok");
	head = insert(head, "l", "ls");
	char *ch = malloc(sizeof(char) * 20);
	strcpy(ch, "l");

	printf("%s\n", ch);
	print_alias(head);

	ch = command(head, ch);

	if (ch != NULL)
		printf("%s\n", ch);
	else
		printf("ch is NULL");

	return 0;
}*/