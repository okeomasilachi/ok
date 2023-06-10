#include "main.h"


void sig(int signum)
{
	(void)signum;
	p(STO, "\n===> ");
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
		non_interactive(oki);

	return 0;
}
