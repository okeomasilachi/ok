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
 *
 * Return: Void
*/
void _in(okeoma *oki, char **argv)
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
	oki->head = list_from_env(environ);
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
 * main - entry point of the shell
 * @argc: argument count
 * @argv: argument vectors
 *
 * Return: 0 on success
 * error: Non zero value is returned
*/
int main(int argc, char **argv)
{
	okeoma *oki = malloc(sizeof(okeoma));
	size_t n = 0;
	ssize_t byte_r = 1;
	char st = 0;
	FILE *fd;

	signal(SIGINT, sig);
	_in(oki, argv);
	fd = file_handle(oki, argc, argv);
	while (1 && (!st || byte_r != 0))
	{
		if (!st && !oki->it)
			oki->c++;
		st = !isatty(STDIN_FILENO);
		if (argc == 1 && !st && !oki->it)
			p(STO, "$ ");
		byte_r = getline(&oki->cmd, &n, fd);
		if (byte_r == -1)
			break;
		B_exc(oki);
		if (!oki->it && !st)
			continue;
		if (oki->it && st)
			break;

		oki->c++;
	}
	free_all(oki);
	return (0);
}
