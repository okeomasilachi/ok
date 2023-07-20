#include "shell.h"

/**
 * _isdigit - Checks if variable is a digit.
 * @c: The parameter to be checked.
 *
 * Return: 1 c is a number, 0 otherwise.
 */
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * _strlen - gets the length of a string
 * @str: The parameter to be checked.
 *
 * Return: the length of the string;
 */
size_t _strlen(const char *str)
{
	size_t length;

	if (str == NULL)
		return (0);
	length = 0;
	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicate
*/
char *_strdup(const char *str)
{
	size_t length;
	char *duplicate = NULL;

	if (str == NULL)
		return (NULL);
	length = _strlen(str);
	duplicate = (char *) malloc((length + 1) * sizeof(char));
	if (duplicate != NULL)
		_strcpy(duplicate, str);

	return (duplicate);
}

/**
 * _strncmp - compears n bytes of a sring
 * @s1: string to match
 * @s2: string to compare with
 * @n: number of bytes
 *
 * Return: the point where the match case is found
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

		i++;
	}
	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}

/**
 * _strcspn - returns of initail segments in bytes in s
 * @str: parameter to run calculation on
 * @reject: segments of bytes
 *
 * Return: the segmenth in bytes
*/
size_t _strcspn(const char *str, const char *reject)
{
	size_t length;

	if (str == NULL || reject == NULL)
		return (0);
	length = 0;
	while (str[length] != '\0')
	{
		if (_strchr(reject, str[length]) != NULL)
			break;

		length++;
	}
	return (length);
}
