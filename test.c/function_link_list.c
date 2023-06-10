#include "../main.h"

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
 * is_member - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @f_value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_member(env_list *head, const char *f_value)
{
	if (head == NULL) return false;
	else if (strcmp(head->NAME, f_value) == 0) return true;
	else return is_member(head->next, f_value);
}

/**
 * free_list - free's memory allocated by list_from_env
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_list(env_list *head)
{
	env_list *current = head, *temp = NULL;
	
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
 * print_node - Prints the values of a linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void print_node(env_list *head)
{
	env_list *current;
	current = head;

	while (current != NULL)
	{
		printf("%s=%s\n", current->NAME, current->value);
		current = current->next;
	}
	
}

/**
 * insert_at_tail - Inserts a new env_list with a given value at the tail of a linked list
 * @head: The head of the linked list
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
env_list *insert_at_tail(env_list *head, char *NAME, char *value)
{
	env_list *new_node = NULL, *current = NULL;

	if (head == NULL)
		return (new_node);
	else if (is_member(head, NAME))
	{
		current = head;
		while (current->NAME != NAME)
			current = current->next;
		current->value = value;
		return (head);
	}
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
 * delete_first_match - Deletes the first env_list with a given value from a linked list
 * @head: The head of the linked list
 * @delete_value: The value to be deleted
 * @was_deleted: Pointer to the variable that indicates if a env_list was deleted
 *
 * Return: A pointer to the modified linked list
 */
env_list *delete_first_match(env_list *head, char *delete_value, bool *was_deleted)
{
	env_list *current = NULL, *prev = NULL, *temp = NULL;

	if (head == NULL)
	{
		*was_deleted = false;
		return (NULL);
	}
	if (head->NAME == delete_value)
	{
		temp = head->next;
		free(head);
		*was_deleted = (true);
		return (temp);
	}
	current = head->next;
	prev = head;
	while (current != NULL)
	{
		if (current->NAME == delete_value)
		{
			prev->next = current->next;
			free(current);
			*was_deleted = true;
			return (head);
		}
		prev = current;
		current = current->next;
	}
	*was_deleted = false;
	return (head);
}

char *get_env(env_list *env, const char *NAME)
{
	char *ret = NULL;
	bool ok = is_member(env, NAME);
	if (ok)
		puts("here1");
	if (env == NULL || NAME == NULL) return NULL;
	else
	{
		if (strcmp(env->NAME, NAME) == 0)
		{
			puts("here");
			ret = strdup(env->value);
			return (ret);
		}
		env = env->next;
	}
	puts("here2");
	return (ret);	
}



int main(void)
{
	env_list *me = list_from_env(environ);
	char *name = get_env(me, "PWD");

	printf("%s\n", name);

	return 0;
}

