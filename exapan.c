#include "main.h"

char *value(char *str)
{
	char *val = strdup(str);

	if (strstr(val, "$") != NULL)
	{
		val = (strstr(val, "$") + 1);
		return (val);
	}

	return (NULL);
}

bool checker(char *arr)
{
	if (arr == NULL) return false;
	else if (strstr(arr, "$") != NULL) return true;
	else return false;
}

int change(env_list *head, char *av)
{
	env_list *cur = head;
	char *tok = NULL, *val = NULL;
	int len;


	v val, v len;
	val = strstr(av, "$");

	while (cur != NULL)
	{
		len = (strlen(cur->NAME) + 1);
		tok = malloc(sizeof(char *));
		tok = strcat("$", cur->NAME);
		printf("%s\n", tok);

		cur = cur->next;
	}
	return (0);
}

int modify(okeoma *oki)
{
	env_list *current = NULL;
	char *val = value(oki->av[1]);

	if (is_NAME(oki->head, val) == true)
	{
		current = oki->head;
		while (current != NULL)
		{
			if (strcmp(current->NAME, val) == 0)
			{
				printf("%s\n", current->value);
				return (0);
			}
			current = current->next;
		}
		return (-1);
	}
	else if (strcmp(val, "?") == 0)
	{
		printf("%d\n", oki->status);
		return (0);
	}
	else if (strcmp(val, "$") == 0)
	{
		printf("%d\n", oki->mypid);
		return (0);
	}
	else if (oki->av[1] != NULL)
	{
		printf("%s\n", oki->av[1]);
		return (0);
	}
	return (-1);
}

int main()
{
	env_list *env = list_from_env(environ);
	char arr[] = "process id = $HOME";

	if (checker(arr) == true)
	{
		change(env, arr);
		return (0);
	}
	else
		puts("no");


	return (-1);
}