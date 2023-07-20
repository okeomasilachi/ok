#include "shell.h"

/**
 * find_char - searches for a chracter in string and return's
 * all characters before the speacified character
 * @dest: the string to be searched
 * @character: character to search for
 *
 * Return: Void
*/
void find_char(const char *dest, int character)
{
	char *str_cpy = _strchr(dest, character);

	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
	}
}

/**
 * find_set - searches for "&& or ||" in a string
 * @str: the string to be searched
 *
 * Return: returns 1 if && is found
 * 2 is || is found, 0 if no match is found
*/
int find_set(char *str)
{
	static char *currentPosition;
	static int setValue;
	char *result1, *result2;

	if (str != NULL)
	{
		currentPosition = str;
		setValue = 0;
	}
	if (currentPosition == NULL)
		return (-1);

	result1 = "&&" != NULL ? strstr(currentPosition, "&&") : NULL;
	result2 = "||" != NULL ? strstr(currentPosition, "||") : NULL;
	if (result1 == NULL && result2 == NULL)
		return (-1);

	if (result1 == NULL || (result2 != NULL && result2 < result1))
	{
		currentPosition = result2 + _strlen("||");
		setValue = 2;
	}
	else
	{
		currentPosition = result1 + _strlen("&&");
		setValue = 1;
	}
	return (setValue);
}

/**
 * empty - checks if an address pointed to by a pointer is empty
 * @str: string to be checked
 *
 * Return: 0 if empty else 1
*/
int empty(const char *str)
{
	while (*str)
	{
		if (!isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
