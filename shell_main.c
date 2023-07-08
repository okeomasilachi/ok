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

	p(STO, "\n===> ");
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
 * empty - checks if an address pointed to by a pointer is empty
 * @str: string to be checked
 *
 * Return: 0 if empty else 1
*/
int empty(const char *str)
{
	while (*str)
	{
		if (!isspace(*str))
			return 0;
		str++;
	}
	return 1;
}

/**
 * File - handles all file processing
 * @filename: name of the file to be processed
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void File(char* filename, okeoma *oki)
{
	size_t len;
	ssize_t read;
	FILE *file;
	int fd;

	oki->cmd = NULL;
	if (access(filename, F_OK) == 0)
		fd = open(filename, O_RDONLY);
	else
	{
		p(STE, "%s: %d: cannot open %s: No such file\n",
		oki->N, oki->c, filename);
		exit(2);
	}
	if (fd == -1)
		return;
	file = fdopen(fd, "r");
	if (file == NULL)
	{
		close(fd);
		return;
	}
	len = 0;
	oki->c++;
	oki->N = filename;
	while ((read = getline(&oki->cmd, &len, file)) != -1)
	{
		remov(oki->cmd);
		if (empty(oki->cmd))
		{
			oki->c++;
			continue;
		}
		B_exc(oki);
		oki->c++;
	}
	free(oki->cmd);
	fclose(file);
	close(fd);
	exit(0);
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

	_in(oki, argv);
	signal(SIGINT, sig);

	if (argc > 1)
		File(argv[1], oki);

	while (true)
	{
		oki->c++;
		if (!oki->it && argc == 1)
			p(STO, "===$> ");
		getline(&oki->cmd, &n, stdin);
		if (oki->cmd == NULL || *oki->cmd == '\0')
		{
			free(oki->cmd);
			continue;
		}
		B_exc(oki);
		
		if (oki->it)
			break;
		else
			continue;
	}

	return (0);
}
