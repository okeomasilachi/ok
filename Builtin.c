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
	if (oki->av[1] == NULL)
	{
		oki->ok = _getenv("HOME");
		chdir(oki->ok);
		return;
	}
	if (strcmp(oki->av[1], "-") == 0)
	{
		if (oki->old != NULL)
			free(oki->old);
		oki->old = _getenv("OLDPWD");
		chdir(oki->old);
		p(STO, "%s\n", oki->old);
		return;
	}
	else 
	{
		if (chdir(oki->av[1]) == 0)
		{
			if (oki->ok != NULL)
				free(oki->ok);
			oki->ok = _getenv("PWD");
			p(STO, "%s\n", oki->ok);
			return;
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
		my_clearenv();
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
			my_clearenv();
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
	if (oki->av[1] == NULL || oki->av[2] == NULL || oki->av[3] != NULL)
		p(STE, "%s: %d: %s: Usage: setenv NAME value\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		_setenv(oki->av[1], oki->av[2], 1);
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
	if (oki->av[1] == NULL || oki->av[2] != NULL)
		p(STE, "%s: %d: %s: Usage: unsetenv NAME\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		if ((oki->ok = _getenv(oki->av[1])) != NULL)
			_unsetenv(oki->av[1]);
		else
			p(STE, "%s: %d: %s: \"%s\" not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);			
	}
}

/**
 * get_env_command - print a particular environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void get_env_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] != NULL)
	{
		p(STE, "%s: %d: %s: Usage: %s <NAME of environ>\n", oki->Name, oki->com_num, oki->av[0], oki->av[0]);
	}
	else if ((oki->ok = _getenv(oki->av[1])) != NULL)
	{
		p(STO, "%s\n", oki->ok);
		return;
	}
	else
	{
		p(STE, "%s: %d: %s: \"%s\" not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
	}
}


void _alias(okeoma *oki)
{
	alias *head = NULL;

	if (oki->av[1] == NULL)
		print(head);
	else
		head = define_alias(head, oki->av[1]);
}
