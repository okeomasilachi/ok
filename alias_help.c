#include "shell.h"

/**
 * null_check - checkes if the string pointed to by ok is NULL
 * @ok: the tring to be checked
 *
 * Return: True if NULL and Fales if not NULL
*/
bool null_check(char *ok)
{
	if (ok == NULL)
		return (true);
	else
		return (false);
}

/**
 * get_value - gets the value of a string after the "=" character
 * @str: the string tobe worked on
 *
 * Return: a pointer to the character of the "=" chracter in the string
 * error: NULL is returned if "=" is not found
*/
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
