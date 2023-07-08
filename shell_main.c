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

FILE *stm(int argc, char **argv, okeoma *oki)
{
	FILE *fd = NULL;

	if (argc > 2)
		p(STE, "%s: %d: Usage: simple_shell [filename]\n", oki->N, oki->c);
	else if (argc == 1)
	{
		fd = stdin;
	}
	else
	{
		fd = fopen(argv[1], "r");
	}

	return (fd);
}

void readFromFile(const char* filename, okeoma *oki) {
    int i = 0, fd = open(filename, O_RDONLY);
    char buf[1024];
    ssize_t bytes, len = 0;
    v oki, v i;
    if (fd == -1) {
        printf("Failed to open the file.\n");
        return;
    }
    while ((bytes = read(fd, buf,sizeof(buf))) != 0)
    {
	len += strlen(buf) + 1;
	printf("%s ", buf);
	/* i++;
	printf("%d", i); */
    }
    printf("%lu\n", len);

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

	if (argc == 2)
		readFromFile(argv[1], oki);
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