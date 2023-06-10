#include "main.h"

/**
 * list_from_env - Builds a linked list from the environmental variable
 * @env: pointer to the environmental list
 *
 * Return: Returns pointer to the linked list 
*/
env_list *list_from_env(char **env)
{
	env_list *head = NULL, *current = NULL, *new_node = NULL;
	char *variable, *separator, *name, *value;
	int i = 0, name_len;

	while (env[i] != NULL)
	{
		variable = env[i];
		separator = strchr(variable, '=');
		
		if (separator != NULL)
		{
			name_len = separator - variable;
			name = (char *)malloc((name_len + 1) * sizeof(char));
			strncpy(name, variable, name_len);
			name[name_len] = '\0';
			
			value = strdup(separator + 1);	/* Extract the variable value */
			/* Create a new env_list for the variable */
			new_node = (env_list *)malloc(sizeof(env_list));
			new_node->NAME = name;
			new_node->value = value;
			new_node->next = NULL;
			if (head == NULL) /* First env_list in the list */
			{
				head = new_node;
				current = new_node;
			}
			else /* Append the env_list to the end of the list */
			{
				current->next = new_node;
				current = new_node;
			}
		}
		i++;
	}
	return (head);
}

/**
 * is_value - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_value(env_list *head, const char *value)
{
	if (head == NULL) return false;
	else if (strcmp(head->NAME, value) == 0) return true;
	else return is_value(head->next, value);
}

/**
 * is_NAME - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @NAME: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_NAME(env_list *head, const char *NAME)
{
	if (head == NULL) return false;
	else if (strcmp(head->NAME, NAME) == 0) return true;
	else return is_NAME(head->next, NAME);
}

/**
 * free_list - free's memory allocated by list_from_env
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_list(env_list *head)
{
	if (head == NULL) return;

	free_list(head->next);
	free(head->NAME);
	free(head->value);
	free(head);
}


/**
 * print - Prints the values of a env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void print(env_list *head)
{
	env_list *current;
	current = head;

	while (current != NULL)
	{
		p(STO, "%s=%s\n", current->NAME, current->value);
		current = current->next;
	}
	
}

/**
 * insert_env - Inserts a new env_list with a given NAME and value at the tail of a linked list
 * @head: The head of the linked list
 * @NAME: name of variable
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
env_list *insert_env(env_list *head, char *NAME, char *value)
{
	env_list *new_node = NULL, *current = NULL;

	if (head == NULL)
		return (new_node);
	/*else if (is_NAME(head, NAME))
	{
		current = head;
		while (current->NAME != NAME)
			current = current->next;
		current->value = value;
		return (head);
	}*/
	else
	{
		new_node = malloc(sizeof(env_list));
		new_node->value = value;
		new_node->NAME = NAME;
		new_node->next = NULL;
		current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		return (head);
	}
}

/**
 * delete_match - Deletes the first env_list with a given NAME from a linked list
 * @head: The head of the linked list
 * @delete_value: The value to be deleted
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
 * set_env_value - sets the value of a NAME in the env_list if it exist
 * @env: the list to search
 * @NAME: the name to search for in the list
 * @value: value to be inserted
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
void set_env_value(env_list *env, const char *NAME, const char *value)
{
	env_list *current = env;
	
	if (current->next == NULL) return;
	else if (strcmp(current->NAME, NAME) == 0)
	{
		current->value = strdup(value);
		return;
	}
	else set_env_value(current->next, NAME, value);	
}

/**
 * delete_duplicate - Deletes duplicate nodes from an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void delete_duplicate(env_list *head)
{
	env_list *cur1 = NULL, *cur2 = NULL, *dup = NULL;

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
				cur2 = cur2->next;
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
