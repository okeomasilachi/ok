#include "shell.h"

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

			value = strdup(separator + 1);
			new_node = (env_list *)malloc(sizeof(env_list));
			new_node->NAME = name;
			new_node->value = value;
			new_node->next = NULL;
			if (head == NULL)
			{
				head = new_node;
				current = new_node;
			}
			else
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
 * env_from_list - get an environ from a linked list
 * @head: a pointer to the head of the list
 *
 * Return: a NULL terminated pointer to the array of environ list
*/
char **env_from_list(env_list *head)
{
	env_list *cur = head, *later = cur;
	size_t len, cnt = 0, lu = -1;
	char **envi;

	if (cur == NULL)
		return (NULL);
	len = list_len(cur);
	if (len == lu)
		return (NULL);
	envi = malloc(sizeof(char *) * (len + 1));

	if (envi == NULL)
		return (NULL);

	while (later != NULL)
	{
		envi[cnt] = strbind(later->NAME, later->value);
		cnt++;
		later = later->next;
	}
	envi[cnt] = NULL;

	return (envi);

}

/**
 * insert_env - Inserts a new env_list with a
 *		given NAME and value at the tail of a linked list
 * @head: The head of the linked list
 * @NAME: name of variable
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
env_list *insert_env(env_list *head, const char *NAME, const char *value)
{
	env_list *new_node = NULL, *current = head;

	new_node = malloc(sizeof(env_list));
	new_node->value = strdup(value);
	new_node->NAME = strdup(NAME);
	new_node->next = NULL;

	if (head == NULL)
		return (new_node);
	else if (is_NAME(current, NAME) == true)
	{
		while (current != NULL)
		{
			if (strcmp(current->NAME, NAME) == 0)
			{
				free(current->value);
				current->value = strdup(value);
				fr__(3, new_node->value, new_node->NAME, new_node);
				break;
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
 * delete_match - Deletes the first matching node
 *			from an env_list with a given NAME
 * @head: The head of the linked list
 * @delete_NAME: The NAME of list to be deleted
 *
 * Return: A pointer to the modified linked list
 */
env_list *delete_match(env_list *head, char *delete_NAME)
{
	env_list *temp = NULL;

	if (head == NULL)
		return (NULL);
	if (head->next != NULL && _strcmp(head->next->NAME, delete_NAME) == 0)
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
