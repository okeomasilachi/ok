#include "main.h"


/*void sig_H(int sig)
{
	(void)sig;
	_put("\n===> ");
	fflush(stdout);
}*/

void signal_handler(int signum) {
	(void)signum;
    printf("\n===> ");
    fflush(stdout);
}

int main(int argc, char **argv)
{
	okeoma *oki = malloc(sizeof(okeoma));
	_in(oki, argv);

	signal(SIGINT, signal_handler);
	if (oki->it && argc == 1)
	{
		
		while (true)
		{
			oki->com_num++;
			printf("===> ");
			oki->cmd = p_Input();
			if (oki->cmd == NULL || *oki->cmd == '\0')
			{
				free(oki->cmd);
				continue;
			}
			B_exc(oki);
		}
	}
	else
	{
		if (access(argv[1], F_OK) == 0 && argc == 2)
		{
			oki->Name = argv[1];
			file(oki, argv[1]);
		}
		if (argv[1] != NULL)
		{
			dprintf(STDERR_FILENO, "%s: %ld: cannot open %s: No such file\n", oki->Name, oki->com_num, argv[1]);
			exit(EXIT_SUCCESS);
		}
		read_in(oki);
		if (oki->cmd == NULL || *oki->cmd == '\0')
			free(oki->cmd);

		B_exc(oki);
	}
	return 0;
}
