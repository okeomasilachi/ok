#include "main.h"


void sig(int signum)
{
	(void)signum;
	printf("\n===> ");
	fflush(stdout);
}

int main(int argc, char **argv)
{
	okeoma *oki = malloc(sizeof(okeoma));

	_in(oki, argv);
	signal(SIGINT, sig);
	if (oki->it && argc == 1)
		interactive(oki);
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
		non_interactive(oki);
	}
	return 0;
}
