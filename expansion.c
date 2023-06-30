#include "shell.h"

/**
 * first - checks for variable expansion in the environ list
 * @head: pointer to the head of an environ list
 * @av: string to run comparism with
 *
 * Return: a pointer to the modified string
 * else retruns the original string 
*/
char *first(env_list *head, char *av)
{
	env_list *cur = head;
	char *tok = NULL, *rep = NULL, *rem = NULL, *va = NULL, *new;
	int len;
	size_t n_size;

	va = strdup(av);
	while (cur != NULL)
	{
		len = strlen(cur->NAME) + 2;
		tok = malloc(len);
		strcat(tok, "$");
		strcat(tok, cur->NAME);
		if ((rep = strstr(va, tok)) != NULL)
		{
			len = strlen(tok);
			if(strncmp(rep, tok, len) == 0)
			{
				rem = strdup(rep + len);
				n_size = strlen(cur->value) + strlen(rem) + 1;
				new = malloc(n_size);
				strcpy(new, cur->value);
				strcat(new, rem);
				memcpy(rep, new, n_size);
				free(rem), free(new), free(tok);
				return (va);
			}
		}
		cur = cur->next;
	}
	free(tok), free(va);
	return (av);
}

/**
 * second - checks for variable expansion from pre-defined variables
 * @oki: struct of type okeoma
 * @av: pointer to the string to compare
 *
 * Return: a pointer to the modified string
 * else retruns the original string
*/
char *second(okeoma *oki, char *av)
{
	char *val = NULL, *rem = NULL, *va = NULL, *new;
	char *expand[] = {"$$", "$?"}, *ex[2];
	int len, i = 0;
	size_t n_size;

	if (checker(av) == true)
	{
		va = strdup(av);
		val = strstr(va, "$");
		int_char(oki->mypid, oki->status, ex);
		while (expand[i] != NULL)
		{
			if ((val = strstr(va, expand[i])) != NULL)
			{
				len = strlen(expand[i]);
				if(strncmp(val, expand[i], len) == 0)
				{
					rem = strdup(val + len);
					n_size = strlen(ex[i]) + strlen(rem) + 1;
					new = malloc(n_size);
					strcpy(new, ex[i]);
					strcat(new, rem);
					memcpy(val, new, n_size);
					free(rem), free(new);
					return (va);
				}
			}
			i++;
		}
	}
	free(va);
	return (av);
}

/**
 * replace - carries out variable expantion procedures
 * @head: pointer to the head of an env list
 * @oki: struct of type okeoma
 * @value: pointer to a string to carry out variable exapansion
 *
 * Return: a pointer to the modified string
*/
char *replace(env_list *head, okeoma *oki, char *value)
{
	bool check;
	char *sec = strdup(value);
				
	check = checker(sec);
	while (check == true)
	{
		sec = first(head, sec);
		sec = second(oki, sec);
		
		check = checker(sec);
	}
	return (sec);
}
