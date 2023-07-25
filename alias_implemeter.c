#include "shell.h"

/**
 * alias_checker - checks if string path is a defined alias
 * @head: the head of the linked list
 * @arr: the string to compare
 *
 * Return: true if a match is found else false is returned
*/
bool alias_checker(alias *head, char *arr)
{
	char *tok, *che = strdup(arr);
	alias *cur = head;

	if (head == NULL || arr == NULL)
		return (false);

	tok = strtok(che, " \n");
	while (tok != NULL)
	{
		while (cur != NULL)
		{
			if (_strcmp(tok, cur->NAME) == 0)
				return (true);

			cur = cur->next;
		}
		cur = head;
		tok = strtok(NULL, " \n");
	}
	return (false);
}

/**
 * command - replaces defined aliases with there
 *		corresponding values in a string
 * @head: pointer to the head of the linked list
 * @check: the string to be modified
 *
 * Return: the modified string if match's are found
 * else returns original string
*/
char *command(alias *head, char *check)
{
	char *c1 = NULL, *tok, *che = strdup(check);
	int len = 0;
	alias *Alias = NULL, *cur = head;

	if (head == NULL)
		return (check);

	tok = strtok(che, " \n");
	while (tok != NULL)
	{
		while (cur != NULL)
		{
			if (_strcmp(tok, cur->NAME) == 0)
				tok = strdup(cur->value);

			cur = cur->next;
		}
		len += _strlen(tok) + 1;
		Alias = insert(Alias, tok, tok);
		cur = head;
		tok = strtok(NULL, " \n");
	}
	cur = Alias;
	c1 = malloc(sizeof(char) * len);
	c1[0] = '\0';
	while (cur != NULL)
	{
		_strcat(c1, cur->value);
		_strcat(c1, " ");

		cur = cur->next;
	}
	c1[_strlen(c1) + 1] = '\0';
	return (c1);
}

/**
 * number - get the number of times a character occures in a string
 * @str: the string to be searched
 * @match: the string to search for
 *
 * Return: the number of times a character occoures in a string
*/
int number(char *str, char *match)
{
	int i = 0;

	while (*str != '\0')
	{
		if (*str == *match)
			i++;

		str++;
	}
	return (i);
}

/**
 * position - gets the location of the character srh in str
 * @str: the string to search
 * @srh: the match to look for
 *
 * Return: The (int) position of the character position
 * error: if the string is not present -1
*/
int position(char *str, char *srh)
{
	int i = 0, pos = -1;

	while (str[i] != '\0')
	{
		if (str[i] == *srh)
		{
			pos = i;
			break;
		}
		i++;
	}
	return (pos);

}

/**
 * rem - removes the " ' " character from a string
 * @str: the string to be worked on
 *
 * Return: pointer to the modified string
*/
char *rem(char *str)
{
	char *first, *sec, *str_cpy = strdup(str);
	int a, i;

	if (str == NULL)
		return (NULL);

	a = number(str_cpy, "'");
	i = _strlen(str_cpy) - a;
	first = malloc(i + 1);
	sec = strtok(str_cpy, "'");
	while (sec != NULL)
	{
		_strcat(first, sec);
		sec = strtok(NULL, "'");
	}
	return (first);
}
