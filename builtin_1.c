#include "shell.h"

/**
 * get_cwd - get the current directory of the calling process
 *
 * Return: the abolute path of the directory
*/
char *get_cwd(void)
{
	char path[MAX_PATH];
	char *pth = getcwd(path, sizeof(path));

	if (pth == NULL)
		return (NULL);
	else
		return (pth);
}

/**
 * alias_ - handles all alias arguments
 * @oki: structure of type okeoma
 *
 * Return: Void
*/
void alias_(okeoma *oki)
{
	char *value;
	int cnt;

	if (oki->av[1] == NULL)
		print_alias(oki->pos, oki);
	else
	{

		for (cnt = 1; oki->av[cnt] != NULL; cnt++)
		{
			if (strstr(oki->av[cnt], "=") != NULL)
			{
				value = get_value(oki->av[1]);
				find_char(oki->av[1], '=');
				oki->pos = insert(oki->pos, oki->av[1], rem(value));
			}
			else
			{
				if (check_NAME(oki->pos, oki->av[cnt]) == true)
					print_s_alias(oki->pos, oki->av[cnt], oki);
				else
				{
					p(STE, "%s: %d: %s: %s: not found\n",
					oki->N, oki->c, oki->av[0], oki->av[cnt]);
				}
			}
		}
		return;
	}
}
