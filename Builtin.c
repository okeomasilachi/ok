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
		oki->ok = oki_getenv("HOME");
		oki->old = oki_getenv("PWD");
		chdir(oki->ok);
		oki_setenv("OLDPWD", oki->old, 1);
		oki_setenv("PWD", oki->ok, 1);
		return;
	}
	if (strcmp(oki->av[1], "-") == 0)
	{
		oki->old = oki_getenv("OLDPwD");
		chdir(oki->old);
		p(STO, "%s\n", oki->old);
		return;
	}
	else 
	{
		if (chdir(oki->av[1]) == 0)
		{
			oki->ok = oki_getenv("PWD");
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
		oki_setenv(oki->av[1], oki->av[2], 1);
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
		if (oki_confirm_env(oki->av[1]) == true)
			oki_unsetenv(oki->av[1]);
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
	else if (oki_confirm_env(oki->av[1]) == true)
	{
		oki->ok = oki_getenv(oki->av[1]);
		p(STO, "%s\n", oki->ok);
		return;
	}
	else
	{
		p(STE, "%s: %d: %s: \"%s\" not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
	}
}