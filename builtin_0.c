#include "shell.h"

/**
 * cd_command - changes directory to the specified path
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void cd_command(okeoma *oki)
{
	int i;

	if (oki->av[1] == NULL)
	{
		i = chdir(get_env(oki->head, "HOME"));
		if (i == 0)
		{
			set_env_value(oki->head, "OLDPWD", get_env(oki->head, "PWD"));
			set_env_value(oki->head, "PWD", get_cwd());
		}
		return;
	}
	else if (strcmp(oki->av[1], "-") == 0)
	{
		oki->ok = get_env(oki->head, "OLDPWD");
		i = chdir(oki->ok);
		if  (i == 0)
		{
			set_env_value(oki->head, "OLDPWD", get_env(oki->head, "PWD"));
			set_env_value(oki->head, "PWD", get_cwd());
			p(STO, "%s\n", get_env(oki->head, "PWD"));
		}
		return;
	}
	else
	{
		i = chdir(oki->av[1]);
		if (i == 0)
		{
			set_env_value(oki->head, "OLDPWD", get_env(oki->head, "PWD"));
			set_env_value(oki->head, "PWD", get_cwd());
		}
		else
			p(STE, "%s: %d: %s: can't cd to %s\n",
			oki->N, oki->c, oki->av[0], oki->av[1]);
	}
}

/**
 * exit_command - exits the program
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void exit_command(okeoma *oki)
{
	int i;
	int isNumber = 1;
	int satus;

	if (oki->av[1] == NULL)
	{
		free_all(oki);
		if (!oki->it)
			exit(EXIT_SUCCESS);
		else
			exit(oki->status);
	}
	else if (oki->av[1] != NULL)
	{
		for (i = 0; oki->av[1][i] != '\0'; i++)
		{
			if (!isdigit(oki->av[1][i]))
			{
				isNumber = 0;
				break;
			}
		}
		if (!isNumber)
			p(STE, "%s: %d: %s: Illegal number: %s\n",
			oki->N, oki->c, oki->av[0], oki->av[1]);
		else
		{
			satus = _atoi(oki->av[1]);
			free_all(oki);
			exit(satus);
		}
	}
}

/**
 * setenv_command - sets the specified environ
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void setenv_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] == NULL || oki->av[3] != NULL)
		p(STE, "%s: %d: %s: Usage: setenv NAME value\n",
		oki->N, oki->c, oki->av[0]);
	else
	{
		set_env_value(oki->head, oki->av[1], oki->av[2]);
		return;
	}
}

/**
 * unsetenv_command - unsets an environmental variable
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void unsetenv_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] != NULL)
		p(STE, "%s: %d: %s: Usage: unsetenv NAME\n", oki->N, oki->c, oki->av[0]);
	else
	{
		if (is_NAME(oki->head, oki->av[1]) == true)
			oki->head = delete_match(oki->head, oki->av[1]);
		else
			p(STE, "%s: %d: %s: \"%s\" not set\n",
			oki->N, oki->c, oki->av[0], oki->av[1]);
	}
}

/**
 * get_env_command - print a particular environ
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void get_env_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] != NULL)
	{
		p(STE, "%s: %d: %s: Usage: %s <NAME of environ>\n",
		oki->N, oki->c, oki->av[0], oki->av[0]);
	}
	else if (get_env(oki->head, oki->av[1]) != NULL)
	{
		oki->ok = get_env(oki->head, oki->av[1]);
		p(STO, "%s\n", oki->ok);
		free(oki->ok);
		return;
	}
	else
	{
		p(STE, "%s: %d: %s: \"%s\" not set\n",
		oki->N, oki->c, oki->av[0], oki->av[1]);
	}
}
