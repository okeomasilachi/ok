#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @av: argument varable
 * @argv: argument variable
 * @command_count: current argument number
 * @command: arguments
 * @colon: for the command separator
 *
 * Return: void
*/
void cd_command(char **av, char **argv, size_t command_count,
char *command, char **colon)
{
	int i;
	v command, v colon;

	if (av[1] == NULL)
	{
		i = chdir(getenv("HOME"));
		if (i == 0)
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", get_cwd(), 1);
		}
		return;
	}
	else if (strcmp(av[1], "-") == 0)
	{
		char *ok = getenv("OLDPWD");

		i = chdir(ok);
		if  (i == 0)
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", get_cwd(), 1);
			print(STO, "%s\n", getenv("PWD"));
		}
		return;
	}
	else
	{
		i = chdir(av[1]);
		if (i == 0)
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", get_cwd(), 1);
		}
		else
			print(STE, "%s: %d: %s: can't cd to %s\n",
			argv[0], command_count, av[0], av[1]);
	}
}

/**
 * exit_command - exits the program
 * @av: argument varable
 * @argv: argument variable
 * @command_count: current argument number
 * @command: arguments
 * @colon: for the command separator
 *
 * Return: void
*/
void exit_command(char **av, char **argv, size_t command_count,
char *command, char **colon)
{
	int i;
	int isNumber = 1;
	int satus;

	if (av[1] == NULL)
	{
		arg_free(av, colon);
		free(command);
		exit(EXIT_SUCCESS);
	}
	else if (av[1] != NULL)
	{
		for (i = 0; av[1][i] != '\0'; i++)
		{
			if (!isdigit(av[1][i]))
			{
				isNumber = 0;
				break;
			}
		}
		if (!isNumber)
			print(STE, "%s: %d: %s: Illegal number: %s\n",
			argv[0], command_count, av[0], av[1]);
		else
		{
			satus = atoi(av[1]);
			arg_free(av, colon);
			free(command);
			exit(satus);
		}
	}
}
