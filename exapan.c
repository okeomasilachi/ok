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
		printf("%s\n", oki->av[1]);
	else
		return (-1);
}