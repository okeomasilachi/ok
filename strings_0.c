#include "shell.h"

/**
 * _strcat - concatinates two strings
 * @dest: appended
 * @src: souce string
 *
 * Return: success
 */

char *_strcat(char *dest, const char *src)
{
	int i, ld = _strlen(dest), ls = _strlen(src);

	for (i = 0; i <= ls; i++)
		dest[ld + i] = src[i];

	return (dest);
}

/**
 * _strchr - entry point
 * @s: string
 * @c: pointer to c
 *
 * Return: success (s)
 */

char *_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);

	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return ((*s == (char)c) ? (char *)s : NULL);
}

/**
 * _strncpy - copy a string
 * @dest: input value
 * @src: input value
 * @n: input value
 *
 * Return: dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int index = 0, src_len = 0;

	while (src[index++])
		src_len++;

	for (index = 0; src[index] && index < n; index++)
		dest[index] = src[index];

	for (index = src_len; index < n; index++)
		dest[index] = '\0';

	return (dest);
}

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 *
 * Return: 0 on success
 */
int _strcmp(char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

		i++;
	}
	return (0);
}

/**
 * _strstr - entry point
 * @haystack: viriable 1
 * @needle: veriable 2
 *
 * Return: success
 */

char *_strstr(char *haystack, const char *needle)
{
	int i;

	if (*needle == 0)
		return (haystack);

	while (*haystack)
	{
		i = 0;

		if  (haystack[i] == needle[i])
		{
			do {
				if (needle[i + 1] == '\0')
					return ((char *)haystack);
				i++;

			} while (haystack[i] == needle[i]);
		}
		haystack++;
	}
	return ('\0');
}
