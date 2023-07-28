#include "main.h"

/**
 * string - Breaks a string into a sequence of zero or more nonempty tokens
 * @str: The string to be parsed
 * @del: Set of bytes that delimit the tokens in the parsed string
 *
 * Return: Pointer to the next token,
 *		or NULL if there are no more tokens.
*/
char *string(char *str, const char *del)
{
	char *tok_st = NULL, *tok_ed = NULL;
	static char *saved_str;

	if (str != NULL)
		saved_str = str;

	if (saved_str == NULL || *saved_str == '\0')
		return (NULL);

	tok_st = saved_str;

	while (*tok_st != '\0' && _strchr(del, *tok_st) != NULL)
		tok_st++;

	tok_ed = tok_st;

	while (*tok_ed != '\0' && _strchr(del, *tok_ed) == NULL)
		tok_ed++;

	if (*tok_ed != '\0')
	{
		*tok_ed = '\0';
		saved_str = tok_ed + 1;
	}
	else
	{
		saved_str = NULL;
	}

	return (tok_st);
}

/**
 * split_vector - parses input command to tokens
 * @cmd: string to tokenize
 * @dl: specify the delimiter to use
 *
 * Return: an array pointers to chracters
*/
char **split_vector(char *cmd, char *dl)
{
	char *com_cpy = NULL, *tok, **command;
	size_t count = 0, cnt = 0;

	if (cmd)
	{
		com_cpy = _strdup(cmd);
		tok = string(cmd, dl);
		while (tok)
		{
			cnt++;
			tok = string(NULL, dl);
		}
		cnt++;
		command = malloc(sizeof(char *) * (cnt + 1));
		tok = string(com_cpy, dl);
		while (tok)
		{
			command[count] = malloc(sizeof(char) * (_strlen(tok) + 1));
			_strcpy(command[count], tok);
			tok = string(NULL, dl);
			count++;
		}
		free(tok);
		command[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
		return (command);
	}
	else
		return (NULL);

}

/**
 * arg_free - free's char **
 * @av: char **
 * @colon: char **
 *
 * Return: void
*/
void arg_free(char **av, char **colon)
{
	int i, j;

	for (i = 0; av[i] != NULL; i++)
	{
		free(av[i]);
	}
	free(av);

	for (j = 0; colon[j] != NULL; j++)
	{
		free(colon[j]);
	}
	free(colon);
}
