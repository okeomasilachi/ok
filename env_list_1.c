#include "shell.h"

/**
 * set_env_value - sets the value of a NAME in the
 *			env_list if it exist to the specified value
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

	if (current->next == NULL)
		return (NULL);
	else if (strcmp(current->NAME, NAME) == 0)
		return (current->value);
	else
		return (get_env(current->next, NAME));
}

