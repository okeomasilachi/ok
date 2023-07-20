#include "shell.h"

/**
 * is_value - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_value(env_list *head, const char *value)
{
	if (head == NULL)
		return (false);
	else if (_strcmp(head->NAME, value) == 0)
		return (true);
	else
		return (is_value(head->next, value));
}

/**
 * is_NAME - Checks if a NAME is present in a linked list
 * @head: The head of the linked list
 * @NAME: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_NAME(env_list *head, const char *NAME)
{
	if (head == NULL)
		return (false);
	else if (_strcmp(head->NAME, NAME) == 0)
		return (true);
	else
		return (is_NAME(head->next, NAME));
}

/**
 * print - Prints the values of an env_linked list
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
		printf("%s=%s\n", current->NAME, current->value);
		current = current->next;
	}
}

/**
 * list_len - gets the lenght of a linked list
 * @head: pointer to the head of the list
 *
 * Return: the lenght of the list
 * error: -1 if head is NULL
*/
size_t list_len(env_list *head)
{
	size_t len = 0;
	env_list *current = head;

	if (head == NULL)
		return (len - 1);
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}

/**
 * strbind - concatinates the string value to name with and "=" in-between
 * @name: pointer to the first parameter
 * @value: parameter to the concatinated to name
 *
 * Return: a pointer to the concatinated string
*/
char *strbind(const char *name, const char *value)
{
	char *take;
	size_t len;

	if (name == NULL || value == NULL)
		return (NULL);

	len = (_strlen(name) + _strlen(value));
	take = malloc(sizeof(char) * (len + 2));

	if (take == NULL)
		return (NULL);

	_strcpy(take, name);
	_strcat(take, "=");
	_strcat(take, value);
	take[len + 2] = '\0';

	return (take);
}
