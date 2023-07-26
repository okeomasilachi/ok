#include "shell.h"

/**
 * sig - handler for the SIGINT signal
 * @num: signal to process
 *
 * Return: void
*/
void sig(int num)
{
	v num;

	p(STO, "\n$ ");
	fflush(stdout);
}

/**
 * _in - initialise members of struct of type okeoma
 * @oki: struct of type okeoma
 * @argv: argument vector
 * @env: environmental variable
 *
 * Return: Void
*/
void _in(okeoma *oki, char **argv, char **env)
{
	oki->mypid = getpid();
	oki->cmd = NULL;
	oki->av = NULL;
	oki->command = NULL;
	oki->tok = NULL;
	oki->tok2 = NULL;
	oki->n = 0;
	oki->it = !isatty(STDIN_FILENO);
	oki->N = argv[0];
	oki->c = 0;
	oki->i = 0;
	oki->head = list_from_env(env);
}

/**
 * remov - removes all occurance of "\n\t"" in a string
 * @str: string to be processed
 *
 * Return: Void
*/
void remov(char *str)
{
	int i, j;
	char *src, *dst;

	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if (str[i] != '\t' && str[i] != '\n')
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
	src = str;
	dst = str;
	while (*src)
	{
		if (*src != '"')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}

/**
 * line - funtions removes concurent white spaces from a string
 * @cmd: the string to be worked on
 *
 * Return: void
*/
void line(char *cmd)
{
	char *new;

	if (cmd == NULL || *cmd == '\0')
		return;

	new = cmd;
	while (*cmd != '\0')
	{
		if (*cmd == ' ')
		{
			while (*(cmd + 1) == ' ')
				cmd++;
		}
		*new = *cmd;
		cmd++;
		new++;
	}
	*new = '\0';
}

/**
 * main - entry point of the shell
 * @argc: argument count
 * @argv: argument vectors
 * @env: envronment variables
 *
 * Return: 0 on success
 * error: Non zero value is returned
*/
int main(int argc, char **argv, char **env)
{
	okeoma *oki = malloc(sizeof(okeoma));
	size_t n = 0;
	ssize_t byte_r = 1;
	char st = 0;
	FILE *fd;

	signal(SIGINT, sig);
	_in(oki, argv, env);
	fd = file_handle(oki, argc, argv);
	if (argc > 1)
		file_loop(oki, n, byte_r, st, fd);
	if (!isatty(STDIN_FILENO))
	{
		non_loop(oki, n, byte_r, st, fd);
		return (0);
	}
	if (isatty(STDIN_FILENO) && argc == 1 && !oki->it)
		_loop(argc, oki, n, byte_r, st, fd);

	fclose(fd);
	free_all(oki);
	return (0);
}
