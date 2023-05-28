#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void cd_command(okeoma *info)
{
	if (!info->av[1])
	{
		info->ok = getenv("HOME");
		chdir(info->ok);
		return;
	}
	if (strcmp(info->av[1], "-") == 0)
	{
		info->old = getenv("OLDPWD");
		chdir(info->old);
		info->new = getenv("PWD");
		dprintf(STDOUT_FILENO, "%s\n", info->new);
	}
	else
	{
		info->ok = getenv("PWD");
		if (chdir(info->av[1]) == 0)
		{
			info->ok = getenv("PWD");
			dprintf(STDOUT_FILENO, "%s\n", info->ok);
		}
		else
			dprintf(2, "%s: %ld: %s: can't cd to %s\n", info->Name, info->com_num, info->av[0], info->av[1]);
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

void exit_command(okeoma *info)
{
	int i;
	int isNumber = 1;

	if (info->av[1] == NULL)
	{
		/*free_all(n), free_all(n1), _free(1, cmd);*/
		exit(EXIT_SUCCESS);
	}
	else if (info->av[1] != NULL)
	{
		for (i = 0; info->av[1][i] != '\0'; i++)
		{
			if (!isdigit(info->av[1][i]))
			{
				isNumber = 0;
				break;
			}
		}
		if (!isNumber)
			dprintf(2, "%s: %ld: %s: Illegal number: %s\n", info->Name, info->com_num, info->av[0], info->av[1]);
		else
		{
			/*free_all(n), free_all(n1), _free(1, cmd);*/
			exit(atoi(info->av[1]));
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
void setenv_command(okeoma *info)
{
	int i = 0;
	if (info->av[1] == NULL || info->av[2] == NULL)
		dprintf(2, "%s: %ld: %s: Usage: setenv NAME value\n", info->Name, info->com_num, info->av[0]);
	else
	{
		setenv(info->av[1], info->av[2], 1);
		while (info->arr[i] != NULL)
				i++;

		info->arr[i] = malloc(sizeof(char *));
		info->arr[i] = env_pos(info);  /* set the position of the arr tp point to the env */
		for (info->i = 0; info->arr[info->i] != NULL; info->i++)
			printf("%s\n", info->arr[info->i]);
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
void unsetenv_command(okeoma *info)
{
	if (info->av[1] == NULL)
		dprintf(STDERR_FILENO, "%s: %ld: %s: missing argument\n", info->Name, info->com_num, info->av[0]);
	else
	{
		if (!getenv(info->av[1]))
			dprintf(STDERR_FILENO, "%s: %ld: %s: %s not set\n", info->Name, info->com_num, info->av[0], info->av[1]);
		if (unsetenv(info->av[1]) != 0)
			perror("unsetenv");
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
void help_command(okeoma *info)
{
	if (info->av[1] == NULL)
	{
		dprintf(STDOUT_FILENO, "	This is a simple shell program\n");
		dprintf(STDOUT_FILENO, "\nAuthors: Ebiri ThankGod, Onyedibia Okeomasilachi.\n");
	}
}
