#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void cd_command(okeoma *oki)
{
	if (!oki->av[1])
	{
		oki->ok = get_env(oki->env, "HOME");
		printf("%s\n", oki->ok);
		chdir(oki->ok);
		oki->env = list_from_env(environ);
		return;
	}
	if (strcmp(oki->av[1], "-") == 0)
	{
		oki->old = get_env(oki->env, "OLDPWD");
		chdir(oki->old);
		oki->env = list_from_env(environ);
		oki->new = get_env(oki->env, "PWD");
		p(STO, "%s\n", oki->new);
	}
	else
	{
		if (chdir(oki->av[1]) == 0)
		{
			oki->env = list_from_env(environ);
			oki->ok = get_env(oki->env, "PWD");
			p(STO, "%s\n", oki->ok);
		}
		else
			p(STE, "%s: %d: %s: can't cd to %s\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
	}
}

/**
 * exit_command - exits the program
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/

void exit_command(okeoma *oki)
{
	int i;
	int isNumber = 1;

	if (oki->av[1] == NULL)
	{
		free_list(oki->env);
		free_all(oki);
		exit(EXIT_SUCCESS);
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
			p(STE, "%s: %d: %s: Illegal number: %s\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
		else
		{
			free_list(oki->env);
			free_all(oki);
			exit(atoi(oki->av[1]));
		}
	}
}

/**
 * setenv_command - sets the specified environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void setenv_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] == NULL)
		p(STE, "%s: %d: %s: Usage: setenv NAME value\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		oki->env = insert_at_tail(oki->env, oki->av[1], oki->av[2]);
		return;
	}
}

/**
 * unsetenv_command - unsets an environmental variable
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void unsetenv_command(okeoma *oki)
{
	bool *i = false;

	if (oki->av[1] == NULL)
		p(STE, "%s: %d: %s: missing argument\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		if (get_env(oki->env, oki->av[1]) == NULL)
			p(STE, "%s: %d: %s: %s not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
		else
			oki->env = delete_first_match(oki->env, oki->av[1], i);
	}
}

/**
 * help_command - print help
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void env_command(okeoma *oki)
{
	print_node(oki->env);
}