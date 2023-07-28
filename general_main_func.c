#include "main.h"

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


/**
 * remov - removes all occurance of "\n\t"" in a string
 * @str: string to be processed
 *
 * Return: Void
*/
void remov(char *str)
{
	int i, j;
	char *src, *dst;

	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if (str[i] != '\t' && str[i] != '\n')
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
	src = str;
	dst = str;
	while (*src)
	{
		if (*src != '"')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}

/**
 * line - funtions removes concurent white spaces from a string
 * @cmd: the string to be worked on
 *
 * Return: void
*/
void line(char *cmd)
{
	char *new;

	if (cmd == NULL || *cmd == '\0')
		return;

	while (*cmd != '\0' && _strchr(" \t\n", *cmd) == NULL)
		cmd++;

	new = cmd;
	while (*cmd != '\0')
	{
		if (*cmd == ' ')
		{
			while (*(cmd + 1) == ' ')
				cmd++;
		}
		*new = *cmd;
		cmd++;
		new++;
	}
	*new = '\0';

}

/**
 * handel_comment - searches for a chracter in string and return's
 * all characters before the speacified character
 * @dest: the string to be searched
 *
 * Return: Void
*/
void handel_comment(const char *dest)
{
	char *str_cpy = _strchr(dest, '#');

	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
	}
}
