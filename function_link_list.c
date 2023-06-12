#include "main.h"


/**
 * is_value - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_value(alias *head, const char *value)
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
bool is_NAME(alias *head, const char *NAME)
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
void free_list(alias *head)
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
void print(alias *head)
{
	alias *current;
	current = head;

	while (current != NULL)
	{
		p(STO, "%s=\'%s\'\n", current->NAME, current->value);
		current = current->next;
	}

}

/**
 * insert_env - Inserts a new alias with a given NAME and value at the tail of a linked list
 * @head: The head of the linked list
 * @NAME: name of variable
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
alias *insert_env(alias *head, char *NAME, char *value)
{
	alias *new_node = NULL, *current = NULL;

	if (head == NULL)
		return (new_node);
	else if (is_NAME(head, NAME))
	{
		current = head;
		while (current->NAME != NAME)
			current = current->next;
		current->value = value;
		return (head);
	}
	else
	{
		new_node = malloc(sizeof(alias));
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
 * delete_match - Deletes the first alias with a given NAME from a linked list
 * @head: The head of the linked list
 * @delete_value: The value to be deleted
 *
 * Return: A pointer to the modified linked list
 */
alias *delete_match(alias *head, char *delete_NAME)
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
		head->next = delete_match(head->next, delete_NAME);
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
char *get_env(alias *env, const char *NAME)
{
	alias *current = env;

	if (current->next == NULL) return NULL;
	else if (strcmp(current->NAME, NAME) == 0) return (current->value);
	else return get_env(current->next, NAME);
}

/**
 * set_env_value - sets the value of a NAME in the alias if it exist
 * @env: the list to search
 * @NAME: the name to search for in the list
 * @value: value to be inserted
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
void set_env_value(alias *env, const char *NAME, const char *value)
{
	alias *current = env;

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
void delete_duplicate(alias *head)
{
	alias *cur1 = NULL, *cur2 = NULL, *dup = NULL;

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
alias *revers_list(alias *head)
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

/* Function to check if a string matches any alias and replace it with the corresponding value */
int replace_with_alias(alias *head, char *str)
{
	alias *current = head;
	
	while (current != NULL)
	{
		if (strcmp(str, current->NAME) == 0)
		{
			strcpy(str, current->value);
			return 1; /* Match found and replaced */
		}
		current = current->next;
	}
	return 0; /* No match found */
}

/* Function to process the array and replace aliases recursively */
void process_array(alias *head, char **array, int size)
{
	int i, found_match = 0;
	
	for (i = 0; i < size; i++)
	{
		if (replace_with_alias(head ,array[i]))
			found_match = 1;
	}
	if (found_match)
		process_array(array, size); /* Continue processing until no matches are found */
}

void print_aliases(alias *head, char **alias_names)
{
	alias *current = head;
	
	if (alias_names == NULL)
	{
		while (current != NULL)
		{
			printf("%s='%s'\n", current->NAME, current->value);
			current = current->next;
		}
	}
	else
	{
		int i = 0;
		
		while (alias_names[i] != NULL)
		{
			current = head;
			
			while (current != NULL)
			{
				if (strcmp(alias_names[i], current->NAME) == 0)
				{
					printf("%s='%s'\n", current->NAME, current->value);
					break;
				}
				current = current->next;
			}
			i++;
		}
	}
}

void define_alias(alias *head, char *name, char *value)
{
	alias *current = head;
	
	while (current != NULL)
	{
		if (strcmp(name, current->NAME) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return;
		}
		current = current->next;
	}
	add_alias(name, value);
}

void handle_alias_command(alias *head, char **args)
{
	if (args[1] == NULL)
	{
		/* No arguments provided, print all aliases */
		print_aliases(NULL);
	}
	else if (args[2] == NULL)
	{
		/* Print specific aliases */
		print_aliases(args + 1);
	}
	else
	{
		/* Define new aliases */
		int i = 1;
		while (args[i] != NULL)
		{
			char *name = args[i];
			char *value = strchr(name, '=');  /* Check for name=value format */
			
			if (value != NULL)
			{
				*value = '\0';  /* Separate name and value */
				value++;
				define_alias(head, name, value);
			}
			i++;
		}
	}
}
